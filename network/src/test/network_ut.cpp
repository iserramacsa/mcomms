#include "network/network.h"
#include "gtest/gtest.h"
#include "socket_moc.h"

using namespace Macsa::Network;
using ::testing::Return;

#define TEST_PORT	8080

class MNetworkUT: public ::testing::Test {
	public:
		MNetworkUT( ) {
			// initialization code here
			network = nullptr;
		}

		void SetUp( ) {
			// code here will execute just before the test ensues

			network = new MNetwork();
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
			try {
				if(network != nullptr) {
					delete network;
				}
			} catch (std::exception e) {
				std::cout << __FUNCTION__ << " exception: " << e.what() << std::endl;
			}
		}

		~MNetworkUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}

		SocketMockable * getNewSocket(const std::string expectedAddress) {
			SocketMockable * sock = new SocketMockable(ISocket::TCP_SOCKET, TEST_PORT);
			EXPECT_CALL(*sock, address()).WillRepeatedly(Return(expectedAddress));
			return sock;
		}
		// put in any custom data members that you need
	protected:
		MNetwork* network;
};

TEST_F(MNetworkUT, setupTeardown)
{}

///
/// \brief Add node test
///
TEST_F(MNetworkUT, addNewNode_returnIncrementedSize)
{
	EXPECT_EQ(network->size(), 0);
	NetworkNode* node = new NetworkNode("testNode", "192.168.0.1");
	network->addNewNode(node);
	EXPECT_EQ(network->size(), 1);
}

///
/// \brief remove node test
///
TEST_F(MNetworkUT, removeNode_returnDecrementedSize)
{
	EXPECT_EQ(network->size(), 0);
	NetworkNode* node = new NetworkNode("testNode", "192.168.0.1");
	network->addNewNode(node);
	EXPECT_EQ(network->size(), 1);
	network->removeNode("testNode");
	EXPECT_EQ(network->size(), 0);
}
