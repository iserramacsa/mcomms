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

	   /**
		* @brief getNewSocket: Helper function that creates a mocked socket
		* @param expectedAddress: Address of the mocked socket
		* @param type: Type of the mocked socket
		* @param port: Port of the mocked socket
		* @param expectedStatus: Status of the socket
		* @return Mocked socket pointer
		*/
	   SocketMockable * getNewSocket(const std::string expectedAddress, ISocket::SocketType_n type, uint16_t port, ISocket::SocketStatus_n expectedStatus) {
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
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
}

/**
 * @brief Constructor with null socket return empty address
 */
TEST_F(MNetworkNodeUT, constructorWithNullConnection_returnEmptyAddress)
{
	_node = new NetworkNode(LOCAL_ID, nullptr);
	EXPECT_STREQ(_node->address().c_str(), "");
}

/**
 * @brief Constructor with valid socket return socket address as node address
 */
TEST_F(MNetworkNodeUT, constructorWithConnection_returnSocketAddress)
{
	SocketMockable* socket = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN);
	_node = new NetworkNode(LOCAL_ID, socket);
	EXPECT_STREQ(_node->address().c_str(), DEFAULT_ADDRESS);
}

/**
 * @brief Constructor with null socket return no connections
 */
TEST_F(MNetworkNodeUT, constructorWithNullConnection_returnZeroConnections)
{
	_node = new NetworkNode(LOCAL_ID, nullptr);
	EXPECT_EQ(_node->connections(), 0);
}

/**
 * @brief Constructor with valid socket return one connection
 */
TEST_F(MNetworkNodeUT, constructorWithConnection_returnOneConnection)
{
	SocketMockable* socket = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN);
	_node = new NetworkNode(LOCAL_ID, socket);
	EXPECT_EQ(_node->connections(), 1);
}

/**
 * @brief Adding connections test
 */
TEST_F(MNetworkNodeUT, addNewConnection_returnSuccess)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_EQ(_node->connections(), 0);
	EXPECT_TRUE(_node->addConnection(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_EQ(_node->connections(), 1);
}

/**
 * @brief Duplicated connection detection test
 */
TEST_F(MNetworkNodeUT, addDuplicatedConnection_returnFail)
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
	SocketMockable* sockA = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN);
	EXPECT_TRUE(_node->addConnection(sockA));
	SocketMockable* sockB = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN);
	EXPECT_FALSE(_node->addConnection(sockB));
	delete sockB;
}

/**
 * @brief Remove connections by type and port test
 */
TEST_F(MNetworkNodeUT, removeConnection_returnSuccess)
{
	_node = new NetworkNode(LOCAL_ID, DEFAULT_ADDRESS);
	EXPECT_EQ(_node->connections(), 0);
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
	SocketMockable* socket = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN);
	_node = new NetworkNode(LOCAL_ID, socket);
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
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));

	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
	EXPECT_TRUE(_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::UNKNOWN)));
	EXPECT_EQ(_node->status(), NetworkNode::CONNECTED);
}

/**
 * @brief Add invalid connection test
 */
TEST_F(MNetworkNodeUT, addConnectionsInvalidAddress_returnFail)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	SocketMockable* sock = getNewSocket("192.168.0.2", ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::CONNECTED);
	EXPECT_FALSE(_node->addConnection(sock));
	delete sock;
}

/**
 * @brief Request invalid socket test
 */
TEST_F(MNetworkNodeUT, requestedSocket_ReturnNull)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	const SocketMockable* sock = dynamic_cast<const SocketMockable*>(_node->socket(ISocket::UDP_SOCKET, TEST_PORT));
	EXPECT_TRUE(sock == nullptr);
}

/**
 * @brief Request valid socket test
 */
TEST_F(MNetworkNodeUT, requestedSocket_ReturnValidSocket)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	const SocketMockable* sock = dynamic_cast<const SocketMockable*>(_node->socket(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_TRUE(sock != nullptr);
}

/**
 * @brief Request expected socket test
 */
TEST_F(MNetworkNodeUT, requestedSocket_ReturnExpectedSocket)
{
	SocketMockable* local = getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED);
	_node = new NetworkNode(LOCAL_ID, local);
	const SocketMockable* sock = dynamic_cast<const SocketMockable*>(_node->socket(ISocket::TCP_SOCKET, TEST_PORT));
	EXPECT_TRUE(sock != nullptr);
	EXPECT_TRUE((local == sock));
}

/**
 * @brief Close node test
 */
TEST_F(MNetworkNodeUT, closeNode_returnZeroConnections)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 1, ISocket::CONNECTED));
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 2, ISocket::CONNECTED));
	_node->addConnection(getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT + 3, ISocket::CONNECTED));
	EXPECT_EQ(_node->connections(), 4);
	_node->close();
	EXPECT_EQ(_node->connections(), 0);
}

/**
 * @brief Compare sockets test
 */
TEST_F(MNetworkNodeUT, isSameSocket_returnTrue)
{
	_node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	NetworkNode * node = new NetworkNode(LOCAL_ID, getNewSocket(DEFAULT_ADDRESS, ISocket::TCP_SOCKET, TEST_PORT, ISocket::CONNECTED));
	bool sameSocket = (*_node == *node);
	EXPECT_TRUE(sameSocket);
	delete node;
}
