#include "network/networknode.h"
#include "gtest/gtest.h"
#include "socket_moc.h"

using namespace Macsa;
using ::testing::Return;

#define LOCAL_ID		"local"
#define DEFAULT_ADDRESS	"192.168.0.1"
#define TEST_PORT		8080

class MNetworkNodeUT: public ::testing::Test {
	public:
	   MNetworkNodeUT( ) {
		   // initialization code here
	   }

	   void SetUp( ) {
		   // code here will execute just before the test ensues
		   _node = nullptr;
	   }

	   void TearDown( ) {
		   // code here will be called just after the test completes
		   // ok to through exceptions from here if need be
		   try {
			   if(_node != nullptr) {
				   delete _node;
			   }
		   } catch (std::exception e) {
			   std::cout << __PRETTY_FUNCTION__ << " exception: " << e.what() << std::endl;
		   }
	   }

	   ~MNetworkNodeUT( )  {
		   // cleanup any pending stuff, but no exceptions allowed
	   }

	   // put in any custom data members that you need

	   SocketMockable * getNewSocket(const std::string expectedAddress, ISocket::SocketType_n type, uint16_t port, ISocket::SocketStatus_n expectedStatus) {
		   SocketMockable * sock = new SocketMockable(type, port);
		   EXPECT_CALL(*sock, address()).WillRepeatedly(Return(expectedAddress));
		   EXPECT_CALL(*sock, status()).WillRepeatedly(Return(expectedStatus));
		   return sock;
	   }

		protected:
	   NetworkNode* _node;
};

TEST_F(MNetworkNodeUT, setupTeardown)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
}

TEST_F(MNetworkNodeUT, addNewConnection_returnSuccess)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
}

TEST_F(MNetworkNodeUT, addDuplicatedConnection_returnFail)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_FALSE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
}

TEST_F(MNetworkNodeUT, addDuplicatedConnectionBySocket_returnFail)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN)));
	SocketMockable* sock = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN);
	EXPECT_FALSE(_node->addConnection(sock));
	delete sock;
}

TEST_F(MNetworkNodeUT, disconnectedSocket_returnDisconnected)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN)));
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);
}

TEST_F(MNetworkNodeUT, disconnectedAndConnectedSockets_returnConnected)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));

	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_TRUE(_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN)));
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
}

TEST_F(MNetworkNodeUT, addConnectionsInvalidAddress_returnFail)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	SocketMockable* sock = getNewSocket("192.168.0.2", ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::CONNECTED);
	EXPECT_FALSE(_node->addConnection(sock));
	delete sock;
}

TEST_F(MNetworkNodeUT, requestedSocket_ReturnNull)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	SocketMockable* sock = dynamic_cast<SocketMockable*>(_node->socket(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_TRUE(sock == nullptr);
}

TEST_F(MNetworkNodeUT, requestedSocket_ReturnValidSocket)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	SocketMockable* sock = dynamic_cast<SocketMockable*>(_node->socket(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_TRUE(sock != nullptr);
}

TEST_F(MNetworkNodeUT, requestedSocket_ReturnExpectedSocket)
{
	SocketMockable* local = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED);
	_node = new NetworkNode(LOCAL_ID, local);
	SocketMockable* sock = dynamic_cast<SocketMockable*>(_node->socket(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_TRUE(sock != nullptr);
	EXPECT_TRUE((local == sock));
}

TEST_F(MNetworkNodeUT, isSameSocket_returnTrue)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	NetworkNode * node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	bool sameSocket = (*_node == *node);
	EXPECT_TRUE(sameSocket);
	delete node;
}
