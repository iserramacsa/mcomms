#include "network/nodeobserver.h"
#include "network/networknode.h"
#include "gtest/gtest.h"
#include "server_moc.h"

using namespace Macsa::Network;
using ::testing::Return;

#define NODE_NAME		"root"
#define NODE_ADDR		"127.0.0.1"
#define TEST_PORT		8080

#define ECHO_MSG		"<ECHO>"
#define TEST_TIMEOUT	25	//25 ms

class MyObserver : public NodeObserver
{
	public:
		MyObserver(NetworkNode* node, std::function<void(const NetworkNode::NodeStatus_n&)>* onStatusChanged, std::function<void()>* onMessageTimedOut) :
			NodeObserver(node),
			_onStatusChanged(onStatusChanged),
			_onMessageTimedOut(onMessageTimedOut)
		{}

		virtual void nodeStatusChanged(const NetworkNode::NodeStatus_n& status) override
		{
			if (_onStatusChanged != nullptr) {
				(*_onStatusChanged)(status);
			}
		}
		virtual void nodeTimeout() override
		{
			if (_onMessageTimedOut != nullptr) {
				(*_onMessageTimedOut)();
			}
		}

	  private:
		const std::function<void(const NetworkNode::NodeStatus_n&)>* _onStatusChanged;
		const std::function<void()>* _onMessageTimedOut;
};

class MyNode : public NetworkNode
{
	public:
		MyNode() : NetworkNode(NODE_NAME, NODE_ADDR)
		{}

		unsigned long attachedObservers() {return _observers.size();}
		NodeObserver* observer(unsigned id) const
		{
			NodeObserver*  ob = nullptr;
			for (auto observer : _observers) {
				if (observer->id() == id) {
					ob = observer;
				}
			}
			return ob;
		}
};


class MNodeObserverUT: public ::testing::Test {
	public:
		MNodeObserverUT( ) {
			// initialization code here
			_observer = nullptr;
			_node = nullptr;
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
			_node = new MyNode();
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
			try {
				if(_observer != nullptr) {
					delete _observer;
				}
				if(_node != nullptr) {
					delete _node;
				}
			} catch (std::exception e) {
				std::cout << __PRETTY_FUNCTION__ << " exception: " << e.what() << std::endl;
			}
		}

		~MNodeObserverUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}
		// put in any custom data members that you need
	protected:
		MyObserver* _observer;
		MyNode* _node;
		ServerMockable _server;
};

///
/// \brief Simple setup teardown test to detect memory leaks on test class
///
TEST_F(MNodeObserverUT, setupTeardown)
{}

TEST_F(MNodeObserverUT, observerConstruct_attachesToNode)
{
	EXPECT_EQ(_node->attachedObservers(), 0);
	_observer = new MyObserver(_node, nullptr, nullptr);
	EXPECT_EQ(_node->attachedObservers(), 1);

}

TEST_F(MNodeObserverUT, observerDestructor_detachesFromNode)
{
	_observer = new MyObserver(_node, nullptr, nullptr);
	EXPECT_EQ(_node->attachedObservers(), 1);
	delete _observer; _observer = nullptr;
	EXPECT_EQ(_node->attachedObservers(), 0);
}

TEST_F(MNodeObserverUT, equalObservers_returnTrue)
{
	_observer = new MyObserver(_node, nullptr, nullptr);
	MyObserver* other = dynamic_cast<MyObserver*>(_node->observer(_observer->id()));
	EXPECT_EQ((*_observer), (*other));
}

TEST_F(MNodeObserverUT, nodeStatusChanged_returnConnected)
{
	bool connected = false;
	std::function<void(const NetworkNode::NodeStatus_n&)> onConnected = [&](const NetworkNode::NodeStatus_n& status) {
		connected = (status == NetworkNode::CONNECTED);
	};

	_observer = new MyObserver(_node, &onConnected, nullptr);
	_server.init(ISocket::TCP_SOCKET, TEST_PORT);
	_server.runTcpServer();

	EXPECT_FALSE(connected);
	EXPECT_TRUE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_TRUE(connected);
	_server.stop();
}

TEST_F(MNodeObserverUT, nodeStatusChanged_returnConnecting)
{
	bool connecting = false;
	std::function<void(const NetworkNode::NodeStatus_n&)> onConnected = [&](const NetworkNode::NodeStatus_n& status) {
		if (status == NetworkNode::CONNECTING){
			connecting = true;
		}
	};

	_observer = new MyObserver(_node, &onConnected, nullptr);
	_server.init(ISocket::TCP_SOCKET, TEST_PORT);
	_server.runTcpServer();

	EXPECT_FALSE(connecting);
	EXPECT_TRUE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_TRUE(connecting);
	_server.stop();
}

TEST_F(MNodeObserverUT, nodeStatusChanged_returnDisconnected)
{
	bool disconnected = false;
	std::function<void(const NetworkNode::NodeStatus_n&)> onConnected = [&](const NetworkNode::NodeStatus_n& status) {
		disconnected = (status == NetworkNode::DISCONNECTED);
	};

	_observer = new MyObserver(_node, &onConnected, nullptr);
	_server.init(ISocket::TCP_SOCKET, TEST_PORT);
	_server.runTcpServer();

	EXPECT_FALSE(disconnected);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_TRUE(_node->disconnect(TEST_PORT));
	EXPECT_TRUE(disconnected);
	_server.stop();
}

TEST_F(MNodeObserverUT, timeout)
{
	bool timedOut = false;
	std::function<void()> onNodeTimeout = [&](){ timedOut = true;};

	_observer = new MyObserver(_node, nullptr, &onNodeTimeout);
	_server.init(ISocket::TCP_SOCKET, TEST_PORT);
	_server.run([](AbstractSocket* client) {
		std::string rx = "";
		client->receive(rx, WAIT_FOREVER);
		EXPECT_STREQ(rx.c_str(), ECHO_MSG);
	});


	EXPECT_FALSE(timedOut);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->sendPacket(ECHO_MSG, TEST_PORT), ISocket::FRAME_SUCCESS);
	std::string rx = "";
	_node->receivePacket(rx, TEST_PORT, TEST_TIMEOUT);
	EXPECT_TRUE(timedOut);

	_server.stop();
}
