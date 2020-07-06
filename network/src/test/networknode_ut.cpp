#include "network/networknode.h"
#include "gtest/gtest.h"
#include "socket_moc.h"
#include "server_moc.h"

using namespace Macsa;
using ::testing::Return;

#define LOCAL_ID				"local"
#define REMOTE_ID				"Remote"
#define DEFAULT_ADDRESS			"192.168.0.1"
#define LOOP_BACK_ADDR			"127.0.0.1"
#define TEST_PORT				8080
#define ECHO_MSG				"<ECHO>"
#define TEST_TIMEOUT_MS			50

class ServerPublicNode : public NetworkNode
{
	public:
		ServerPublicNode (const std::string& id, const std::string& address = "") :
			NetworkNode(id, address)
		{}


		virtual bool initServer(ISocket::nSocketType type, uint16_t port)  override  {return NetworkNode::initServer(type, port);}
		virtual ISocket* accept(uint16_t port)								override  {return NetworkNode::accept(port);}
		virtual bool stopServer(ISocket::nSocketType type, uint16_t port)  override  {return NetworkNode::stopServer(type, port);}
};

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
			   std::cout << __FUNCTION__ << " exception: " << e.what() << std::endl;
		   }
	   }

	   ~MNetworkNodeUT( )  {
		   // cleanup any pending stuff, but no exceptions allowed
	   }

	   /**
		* @brief getNewSocket: Helper function that creates a mocked socket
		* @param expectedAddress: Address of the mocked socket
		* @param type: Type of the mocked socket
		* @param port: Port of the mocked socket
		* @param expectedStatus: Status of the socket
		* @return Mocked socket pointer
		*/
	   SocketMockable * getNewSocket(const std::string expectedAddress, ISocket::nSocketType type, uint16_t port, ISocket::nSocketStatus expectedStatus) {
		   SocketMockable * sock = new SocketMockable(type, port);
		   EXPECT_CALL(*sock, address()).WillRepeatedly(Return(expectedAddress));
		   EXPECT_CALL(*sock, status()).WillRepeatedly(Return(expectedStatus));
		   return sock;
	   }

		protected:
	   NetworkNode* _node;
};

/**
 * @brief Simple test to check memory leaks
 */
TEST_F(MNetworkNodeUT, setupTeardown)
{
	_node = new NetworkNode(LOCAL_ID);
}

/**
 * @brief Constructor by default address test
 */
TEST_F(MNetworkNodeUT, constructorByDefault_returnEmptyAddress)
{
	_node = new NetworkNode(LOCAL_ID);
	EXPECT_STREQ(_node->address().c_str(), "");
}

/**
 * @brief Constructor by default connections test
 */
TEST_F(MNetworkNodeUT, constructorByDefault_returnZeroConnections)
{
	_node = new NetworkNode(LOCAL_ID);
	EXPECT_EQ(_node->connections(), 0);
}

/**
 * @brief Adding connections test
 */
TEST_F(MNetworkNodeUT, addNewConnectionByParams_returnSuccess)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_EQ(_node->connections(), 0);
	EXPECT_TRUE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->connections(), 1);
}
/**
 * @brief Adding disconnected connections test
 */
TEST_F(MNetworkNodeUT, addNewConnectionByParams_returnDisconnected)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->status(ISocket::TCP_SOCKET, TEST_PORT), NetworkNode::DISCONNECTED);
}

/**
 * @brief Duplicated connection detection test
 */
TEST_F(MNetworkNodeUT, addDuplicatedConnectionByParams_returnFail)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_FALSE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
}

/**
 * @brief Duplicated connection detection test
 */
TEST_F(MNetworkNodeUT, addDuplicatedConnectionBySocket_returnFail)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	SocketMockable* sockA = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::UNKNOWN);
	EXPECT_TRUE(_node->addConnection(sockA));
	SocketMockable* sockB = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::UNKNOWN);
	EXPECT_FALSE(_node->addConnection(sockB));
	delete sockB;
}

/**
 * @brief TEST_F connect to a server implicitly adds a new connection
 */
TEST_F(MNetworkNodeUT, connectNonStoredConnection_implicitlyAddsNewConnection)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, LOOP_BACK_ADDR);
	EXPECT_EQ(_node->connections(), 0);
	EXPECT_TRUE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->connections(), 1);
	server.stop();
}

/**
 * @brief TEST_F connect to a server failure doesnt increment number of connections test
 */
TEST_F(MNetworkNodeUT, failedConnectionWithNonStoredConnection_doesntAddsNewConnection)
{
	_node = new NetworkNode(LOCAL_ID, LOOP_BACK_ADDR);
	EXPECT_EQ(_node->connections(), 0);
	EXPECT_FALSE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->connections(), 0);
}

/**
 * @brief TEST_F connect a stored disconnected connections does not adds a new connection
 */
TEST_F(MNetworkNodeUT, connectStoredDisconnectedConnection_doNotAddsNewConnection)
{
	SocketMockable* socket = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED);
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	_node->addConnection(socket);
	EXPECT_EQ(_node->connections(), 1);
	EXPECT_TRUE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->connections(), 1);
}

/**
 * @brief TEST_F Connect stored disconnected connection
 */
TEST_F(MNetworkNodeUT, connectStoredDisconnectedConnection_returnConnected)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);
	EXPECT_TRUE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	server.stop();
}

/**
 * @brief TEST_F connect a stored disconnected connections does not adds a new connection
 */
TEST_F(MNetworkNodeUT, connectStoredConnectedConnection_returnConnected)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::TCP_SOCKET, TEST_PORT);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_TRUE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);

	server.stop();
}

/**
 * @brief TEST_F disconnect a stored connected connections return disconnected node
 */
TEST_F(MNetworkNodeUT, reconnectAdisconnectedStoredConnectedConnection_returnConnected)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::TCP_SOCKET, TEST_PORT);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);

	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_TRUE(_node->disconnect(TEST_PORT));
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);
	EXPECT_TRUE(_node->connect(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_EQ(_node->connections(), 1);

	server.stop();
}

/**
 * @brief TEST_F disconnect a stored connected connections return disconnected node
 */
TEST_F(MNetworkNodeUT, disconnectStoredConnectedConnection_returnDisconnected)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::TCP_SOCKET, TEST_PORT);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_TRUE(_node->disconnect(TEST_PORT));
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);

	server.stop();
}

/**
 * @brief TEST_F disconnect a stored connected connections remove the stored connection
 */
TEST_F(MNetworkNodeUT, disconnectStoredConnection_returnNoConnections)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->connections(), 1);
	EXPECT_TRUE(_node->disconnect(TEST_PORT));
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);
	EXPECT_EQ(_node->connections(), 0);

	server.stop();
}

/**
 * @brief TEST_F Send packet without a connection
 */
TEST_F(MNetworkNodeUT, sendPacketWithNonConnection_returnError)
{
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	EXPECT_EQ(_node->connections(), 0);
	EXPECT_EQ(_node->sendPacket(ECHO_MSG, TEST_PORT), ISocket::FRAME_ERROR);
}

/**
 * @brief TEST_F Send packet with a valid disconnected connection
 */
TEST_F(MNetworkNodeUT, sendPacketWithDisconnectedStoredConnection_returnError)
{
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);
	EXPECT_EQ(_node->sendPacket(ECHO_MSG, TEST_PORT, NO_WAIT), ISocket::FRAME_ERROR);
}

/**
 * @brief TEST_F Send empty packet with a valid connected connection
 */
TEST_F(MNetworkNodeUT, sendEmptyPacketWithConnectedStoredConnection_returnError)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);

	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_EQ(_node->sendPacket("", TEST_PORT, NO_WAIT), ISocket::FRAME_ERROR);

	server.stop();
}

/**
 * @brief TEST_F Send packet with a valid connected connection
 */
TEST_F(MNetworkNodeUT, sendPacketWithConnectedStoredConnection_returnSuccess)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);

	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_EQ(_node->sendPacket(ECHO_MSG, TEST_PORT, NO_WAIT), ISocket::FRAME_SUCCESS);

	server.stop();
}

/**
 * @brief TEST_F Receive echo message.
 */
TEST_F(MNetworkNodeUT, receivePacketWithConnectedStoredConnection_returnEcho)
{
	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.runTcpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);

	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_EQ(_node->sendPacket(ECHO_MSG, TEST_PORT, NO_WAIT), ISocket::FRAME_SUCCESS);
	std::string rx = "";
	EXPECT_EQ(_node->receivePacket(rx, TEST_PORT), ISocket::FRAME_SUCCESS);
	EXPECT_STREQ(rx.c_str(), ECHO_MSG);

	server.stop();
}

/**
 * @brief TEST_F Receive packet with disconnected connection.
 */
TEST_F(MNetworkNodeUT, receivePacketWithDisconnectedConnection_returnError)
{
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::TCP_SOCKET, TEST_PORT);

	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);
	std::string rx = "";
	EXPECT_EQ(_node->receivePacket(rx, TEST_PORT, TEST_TIMEOUT_MS), ISocket::FRAME_ERROR);
}

/**
 * @brief TEST_F Timeout on reception.
 */
TEST_F(MNetworkNodeUT, receivePacketWithNoRespondingServer_returnTimeout)
{
	std::mutex mutex;
	std::condition_variable cv;

	ServerMockable server;
	server.init(ISocket::TCP_SOCKET, TEST_PORT);
	server.run([&](AbstractSocket* socket){

		std::string message = "";
		std::string addr;
		socket->receive(message, addr, WAIT_FOREVER);
		EXPECT_STREQ(message.c_str(), ECHO_MSG);
		{
			std::unique_lock<std::mutex>lock(mutex);
			cv.notify_all();
		}
	});

	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->connect(ISocket::TCP_SOCKET, TEST_PORT);

	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_EQ(_node->sendPacket(ECHO_MSG, TEST_PORT, NO_WAIT), ISocket::FRAME_SUCCESS);
	{
		std::unique_lock<std::mutex>lock(mutex);
		cv.wait(lock);
	}
	std::string rx = "";
	using namespace std::chrono;
	steady_clock::time_point t0 = steady_clock::now();
	EXPECT_EQ(_node->receivePacket(rx, TEST_PORT, TEST_TIMEOUT_MS), ISocket::FRAME_TIMEOUT);
	steady_clock::time_point t1 = steady_clock::now();
	duration<double> diff = duration_cast<duration<double>>(t1 - t0);

	EXPECT_TRUE(((diff.count() * 1000)) >= TEST_TIMEOUT_MS);

	server.stop();

}

/**
 * @brief TEST_F Send Datagram without a connection
 */
TEST_F(MNetworkNodeUT, sendDatagramWithNonConnection_returnError)
{
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	EXPECT_EQ(_node->connections(), 0);
	EXPECT_EQ(_node->sendDatagram(ECHO_MSG, TEST_PORT), ISocket::FRAME_ERROR);
}

/**
 * @brief TEST_F Send Datagram with a valid udp connection
 */
TEST_F(MNetworkNodeUT, sendDatagramWithDisconnectedStoredConnection_returnSuccess)
{
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT);
	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->sendDatagram(ECHO_MSG, TEST_PORT, NO_WAIT), ISocket::FRAME_SUCCESS);
}

/**
 * @brief TEST_F Send empty datagram with a valid connection
 */
TEST_F(MNetworkNodeUT, sendEmptyDatagramWithConnectedStoredConnection_returnError)
{
	ServerMockable server;
	server.init(ISocket::UDP_SOCKET, TEST_PORT);
	server.runUdpServer();
	_node = new NetworkNode(LOCAL_ID, SERVER_MOCKABLE_ADDR);
	_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT);

	EXPECT_EQ(_node->connections(), 1);
	EXPECT_EQ(_node->sendDatagram("", TEST_PORT, NO_WAIT), ISocket::FRAME_ERROR);

	server.stop();
}

/************************* INI Server side **********************/

/**
 * @brief Initialization of tcp server
 */
TEST_F(MNetworkNodeUT, initServer_AddAnAccessPoint)
{
	ServerPublicNode node(LOCAL_ID, DEFAULT_ADDRESS);

	EXPECT_EQ(node.connections(), 0);
	EXPECT_EQ(node.accessPoints(), 0);
	EXPECT_TRUE(node.initServer(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_EQ(node.connections(), 0);
	EXPECT_EQ(node.accessPoints(), 1);
}

/**
 * @brief Initialization of tcp server
 */
TEST_F(MNetworkNodeUT, initServerOverInitiatedServer_returnFalse)
{
	ServerPublicNode node(LOCAL_ID, DEFAULT_ADDRESS);

	node.initServer(ISocket::UDP_SOCKET, TEST_PORT);
	EXPECT_EQ(node.accessPoints(), 1);
	EXPECT_FALSE(node.initServer(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_EQ(node.accessPoints(), 1);
}

/**
 * @brief Initialization of a busy port
 */
TEST_F(MNetworkNodeUT, initializeUDPServerOverInitiatedTCPServer_returnFalse)
{
	ServerPublicNode node(LOCAL_ID, DEFAULT_ADDRESS);

	node.initServer(ISocket::TCP_SOCKET, TEST_PORT);
	EXPECT_EQ(node.accessPoints(), 1);
	EXPECT_FALSE(node.initServer(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_EQ(node.accessPoints(), 1);
}

/**
 * @brief Accepting connections
 */
TEST_F(MNetworkNodeUT, acceptConnection_returnTrue)
{
    std::mutex mutex;
    std::condition_variable cv;
    std::atomic_bool running;

	ServerPublicNode node(LOCAL_ID, LOOP_BACK_ADDR);
	node.initServer(ISocket::TCP_SOCKET, TEST_PORT);

    running.store(false);
    ISocket* socket = nullptr;
    std::thread t = std::thread([&]()
    {
        {
            std::unique_lock<std::mutex>lock(mutex);
            cv.notify_one();
            running.store(true);
        }
		socket = node.accept(TEST_PORT);
    });
    if (!running.load())
    {
        std::unique_lock<std::mutex>lock(mutex);
        cv.wait(lock);
    }

    NetworkNode clientNode(REMOTE_ID, LOOP_BACK_ADDR);
    EXPECT_TRUE(clientNode.connect(ISocket::TCP_SOCKET, TEST_PORT));
    t.join();
    EXPECT_TRUE(socket != nullptr);
    delete socket;
}

/**
 * @brief Accepting connections with uninitialized server
 */
TEST_F(MNetworkNodeUT, uninitializedServerAcceptConnection_returnFalse)
{
	ServerPublicNode node(LOCAL_ID, LOOP_BACK_ADDR);
	ISocket* client = node.accept(TEST_PORT);
    EXPECT_EQ(client, nullptr);
}

/**
 * @brief Stop of a uninitialized server
 */
TEST_F(MNetworkNodeUT, stoppingUninitializedServer_returnFalse)
{
	ServerPublicNode node(LOCAL_ID, LOOP_BACK_ADDR);
	EXPECT_FALSE(node.stopServer(ISocket::TCP_SOCKET, TEST_PORT));
}

/**
 * @brief Stop of a initialized server
 */
TEST_F(MNetworkNodeUT, stoppingInitializedServer_removeAccessPoint)
{
	ServerPublicNode node(LOCAL_ID, LOOP_BACK_ADDR);
	node.initServer(ISocket::TCP_SOCKET, TEST_PORT);

	EXPECT_EQ(node.accessPoints(), 1);
	EXPECT_TRUE(node.stopServer(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_EQ(node.accessPoints(), 0);
}

/**
 * @brief Stop accepting connections
 */
TEST_F(MNetworkNodeUT, closeAcceptingSocket_StopsAcceptingMethod)
{
    std::mutex mutex;
    std::condition_variable cv;
    std::atomic_bool running;

	ServerPublicNode node(LOCAL_ID, LOOP_BACK_ADDR);
	node.initServer(ISocket::TCP_SOCKET, TEST_PORT);

    running.store(false);
    ISocket* socket = nullptr;
    std::thread t = std::thread([&]()
        {
            {
                std::unique_lock<std::mutex>lock(mutex);
                cv.notify_one();
                running.store(true);
            }
			socket = node.accept(TEST_PORT);
        });
    if (!running.load())
    {
        std::unique_lock<std::mutex>lock(mutex);
        cv.wait(lock);
    }
	node.stopServer(ISocket::TCP_SOCKET, TEST_PORT);
    t.join();
    EXPECT_TRUE(socket == nullptr);
}


/************************* END Server side **********************/

/**
 * @brief Remove connections by type and port test
 */
TEST_F(MNetworkNodeUT, removeConnection_returnSuccess)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->connections(), 1);
	EXPECT_TRUE(_node->removeConnection(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->connections(), 0);
}

/**
 * @brief Remove connections by socket test
 */
TEST_F(MNetworkNodeUT, removeConnectionSocket_returnSuccess)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	SocketMockable* socket = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::UNKNOWN);
	EXPECT_TRUE(_node->addConnection(socket));
	EXPECT_EQ(_node->connections(), 1);
	EXPECT_TRUE(_node->removeConnection(socket));
	EXPECT_EQ(_node->connections(), 0);
}

/**
 * @brief Disconnect status test
 */
TEST_F(MNetworkNodeUT, disconnectedSocket_returnDisconnected)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_TRUE(_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN)));
	EXPECT_EQ(_node->status(), NetworkNode::DISCONNECTED);
}

/**
 * @brief Connected status test
 */
TEST_F(MNetworkNodeUT, disconnectedAndConnectedSockets_returnConnected)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_TRUE(_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN)));
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
}

/**
 * @brief Add invalid connection test
 */
TEST_F(MNetworkNodeUT, addConnectionsInvalidAddress_returnFail)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	SocketMockable* sock = getNewSocket(LOOP_BACK_ADDR, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::CONNECTED);
	EXPECT_FALSE(_node->addConnection(sock));
	delete sock;
}

/**************** TODO: Remove ************************/
///**
// * @brief Request invalid socket test
// */
//TEST_F(MNetworkNodeUT, requestedSocket_ReturnNull)
//{
//	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
//	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
//	const SocketMockable* sock = dynamic_cast<const SocketMockable*>(_node->socket(ISocket::UDP_SOCKET, TEST_PORT));
//	EXPECT_TRUE(sock == nullptr);
//}

///**
// * @brief Request valid socket test
// */
//TEST_F(MNetworkNodeUT, requestedSocket_ReturnValidSocket)
//{
//	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
//	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
//	const SocketMockable* sock = dynamic_cast<const SocketMockable*>(_node->socket(ISocket::TCP_SOCKET, TEST_PORT));
//	EXPECT_TRUE(sock != nullptr);
//}

///**
// * @brief Request expected socket test
// */
//TEST_F(MNetworkNodeUT, requestedSocket_ReturnExpectedSocket)
//{
//	SocketMockable* local = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED);
//	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
//	_node->addConnection(local);
//	const SocketMockable* sock = dynamic_cast<const SocketMockable*>(_node->socket(ISocket::TCP_SOCKET, TEST_PORT));
//	EXPECT_TRUE(sock != nullptr);
//	EXPECT_TRUE((local == sock));
//}

/**
 * @brief Close node test
 */
TEST_F(MNetworkNodeUT, closeNode_returnZeroConnections)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::CONNECTED));
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 2, ISocket::CONNECTED));
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 3, ISocket::CONNECTED));
	EXPECT_EQ(_node->connections(), 3);
	_node->close();
	EXPECT_EQ(_node->connections(), 0);
}

/**
 * @brief Compare sockets test
 */
TEST_F(MNetworkNodeUT, isSameSocket_returnTrue)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	NetworkNode * node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	bool sameSocket = (*_node == *node);
	EXPECT_TRUE(sameSocket);
	delete node;
}
