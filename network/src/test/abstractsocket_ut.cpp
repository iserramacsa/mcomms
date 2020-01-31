#include "network/network.h"
#include "gtest/gtest.h"

#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <tuple>

#include "network/tcpsocket.h"
#include "network/udpsocket.h"
#include "server_moc.h"

#define TEST_PORT				8080
#define LOOPBACK_ADDR			"127.0.0.1"
#define BCAST_ADDR				"127.0.0.255"
#define CONNECTION_TIMEOUT_MS	2000
#define FAST_RECEIVE_TIMEOUT_MS	500
#define ECHO_MSG				"echo"

using namespace Macsa;

class SocketUT: public ::testing::Test {
	public:
		SocketUT( ) {
			// initialization code here
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
			_socket = nullptr;
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
			if (_socket !=  nullptr) {
				delete _socket;
			}
		}

		~SocketUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}

		void acceptNewConnection(AbstractSocket** client)
		{
			*client = dynamic_cast<AbstractSocket*>(_socket->accept());
			{
				std::unique_lock<std::mutex>lck(_mutex);
				_cv.notify_all();
			}
		}
		void echoSocket(AbstractSocket* socket)
		{
			std::string message = "";
			while (_running.load())
			{
				std::string addr;
				ISocket::nSocketFrameStatus status = socket->receive(message, addr, WAIT_FOREVER);
				if(status == ISocket::FRAME_SUCCESS){
					switch (socket->type()){
						case ISocket::TCP_SOCKET:
							socket->send(message);
							break;
						case ISocket::UDP_SOCKET:
							socket->send(message, addr, TEST_PORT + 1);
							break;
					}
				}
			}
			{/* Scoped wait */
				std::unique_lock<std::mutex>lck(_mutex);
				_cv.notify_all();
			}
		}

	// put in any custom data members that you need
	protected:
		AbstractSocket* _socket;
		std::mutex _mutex;
		std::condition_variable _cv;
		std::atomic_bool _running;
		ServerMockable _server;

};

TEST_F(SocketUT, setupTearDown)
{
	_socket = new TcpSocket();
}

TEST_F(SocketUT, initTcpSocket_returnCreated)
{
	_socket = new TcpSocket();
	EXPECT_EQ(_socket->status(), ISocket::CREATED);
}

TEST_F(SocketUT, closeTcpSocket_returnClosed)
{
	_socket = new TcpSocket();
	EXPECT_EQ(_socket->status(), ISocket::CREATED);
	_socket->close();
	EXPECT_EQ(_socket->status(), ISocket::UNKNOWN);
}

TEST_F(SocketUT, bindTcpServerSocket_returnBinded)
{
	_socket = new TcpSocket();
	EXPECT_TRUE(_socket->bind(TEST_PORT));
	EXPECT_EQ(_socket->status(), ISocket::BINDED);
}

TEST_F(SocketUT, listenTcpServerSocket_returnFalse)
{
	_socket = new TcpSocket();
	EXPECT_FALSE(_socket->listen());
	_socket->close();
}

TEST_F(SocketUT, listenTcpServerSocket_returnListening)
{
	_socket = new TcpSocket();
	_socket->bind(TEST_PORT);
	EXPECT_TRUE(_socket->listen());
	EXPECT_EQ(_socket->status(), ISocket::LISTENING);
	_socket->close();
}

TEST_F(SocketUT, acceptTcpServerSocket_returnNewClientSocket)
{
	_socket = new TcpSocket();
	_socket->bind(TEST_PORT);
	_socket->listen();

	AbstractSocket* client = nullptr;
	/* Accept connection is runned in another thread due to his blocking nature and
	 * needs another socket connecting to it, in order to unblock the execution */
	std::thread th = std::thread(&SocketUT::acceptNewConnection, this, &client);


	/* sleeping this thread forces scheduler to start acceptNewConnection thread */
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	/* New we create the client socket that connect to the server socket to unblock
	 * the accept execution */
	AbstractSocket remote(ISocket::TCP_SOCKET);
	remote.connect(LOOPBACK_ADDR, TEST_PORT);
	{
		std::unique_lock<std::mutex>lck(_mutex);
		_cv.wait_for(lck, std::chrono::milliseconds(CONNECTION_TIMEOUT_MS));
	}
	bool hasClient = (client != nullptr);
	th.join();

	EXPECT_EQ(hasClient, true);

	if (client != nullptr) {
		delete client;
	}
	_socket->close();

}

TEST_F(SocketUT, receiveTcpServerSocket_returnEchoMessage)
{
	_socket = new TcpSocket();
	_socket->bind(TEST_PORT);
	_socket->listen();

	AbstractSocket* client = nullptr;
	/* Accept connection is runned in another thread due to his blocking nature and
	 * needs another socket connecting to it, in order to unblock the execution */
	std::thread th = std::thread(&SocketUT::acceptNewConnection, this, &client);


	/* sleeping this thread forces scheduler to start acceptNewConnection thread */
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	/* New we create the client socket that connect to the server socket to unblock
	 * the accept execution */
	AbstractSocket remote(ISocket::TCP_SOCKET);
	std::string server_rx = "";
	std::string remote_rx = "";
	if(remote.connect(LOOPBACK_ADDR, TEST_PORT))
	{
		{/* Scoped wait */
			std::unique_lock<std::mutex>lck(_mutex);
			_cv.wait_for(lck, std::chrono::milliseconds(CONNECTION_TIMEOUT_MS));
		}
		bool hasClient = (client != nullptr);
		th.join();

		if(hasClient) {
			remote.send(ECHO_MSG);
			ISocket::nSocketFrameStatus fStatus = client->receive(server_rx);
			EXPECT_EQ(fStatus, ISocket::FRAME_SUCCESS);
			if(fStatus == ISocket::FRAME_SUCCESS){
				client->send(ECHO_MSG);
				remote.receive(remote_rx);
			}
		}
	}
	if (client != nullptr) {
		delete client;
	}
	_socket->close();

	EXPECT_EQ(server_rx.compare(ECHO_MSG), 0);
	EXPECT_EQ(remote_rx.compare(ECHO_MSG), 0);
}

TEST_F(SocketUT, receiveTcpServerSocket_returnClientClosed)
{
	_socket = new TcpSocket();
	_socket->bind(TEST_PORT);
	_socket->listen();

	AbstractSocket* client = nullptr;
	/* Accept connection is runned in another thread due to his blocking nature and
	 * needs another socket connecting to it, in order to unblock the execution */
	std::thread th = std::thread(&SocketUT::acceptNewConnection, this, &client);

	/* sleeping this thread forces scheduler to start acceptNewConnection thread */
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	/* New we create the client socket that connect to the server socket to unblock
	 * the accept execution */
	AbstractSocket remote(ISocket::TCP_SOCKET);
	std::string server_rx = "";
	std::string remote_rx = "";

	bool connected = remote.connect(LOOPBACK_ADDR, TEST_PORT);
	EXPECT_TRUE(connected);

	if(connected)
	{
		{/* Scoped wait */
			std::unique_lock<std::mutex>lck(_mutex);
			_cv.wait_for(lck, std::chrono::milliseconds(CONNECTION_TIMEOUT_MS));
		}
		bool hasClient = (client != nullptr);
		th.join();

		EXPECT_TRUE(hasClient);
		if(hasClient) {
			_running.store(true);
			th = std::thread(&SocketUT::echoSocket, this, client);
			{/* Scoped wait */
				remote.close();
				_running.store(false);
				std::unique_lock<std::mutex>lck(_mutex);
				_cv.wait_for(lck, std::chrono::milliseconds(CONNECTION_TIMEOUT_MS));
			}

			EXPECT_EQ(client->status(), ISocket::READY); //Remote client could be down

			th.join();
		}
	}

	if (client != nullptr) {
		delete client;
	}
}

TEST_F(SocketUT, tcpClientSocket_returnConnectionFail)
{
	_socket = new TcpSocket();

	EXPECT_FALSE(_socket->connect(LOOPBACK_ADDR, TEST_PORT));
	EXPECT_EQ(_socket->status(), ISocket::INITIATED);
	_socket->close();
}

TEST_F(SocketUT, tcpClientSocket_returnConnected)
{
	_socket = new TcpSocket();

	//Start a server to test client sockets
	_server.init(ISocket::TCP_SOCKET, TEST_PORT);
	_server.runTcpServer();

	EXPECT_TRUE(_socket->connect(LOOPBACK_ADDR, TEST_PORT));
	EXPECT_EQ(_socket->status(), ISocket::CONNECTED);

	_server.stop();
	_socket->close();
}

TEST_F(SocketUT, tcpClientSocket_returnReceiveEcho)
{
	_socket = new TcpSocket();

	//Start a server to test client sockets
	_server.init(ISocket::TCP_SOCKET, TEST_PORT);
	_server.runTcpServer();

	EXPECT_TRUE(_socket->connect(LOOPBACK_ADDR, TEST_PORT));
	EXPECT_EQ(_socket->status(), ISocket::CONNECTED);
	EXPECT_EQ(_socket->send(ECHO_MSG), ISocket::FRAME_SUCCESS);
	std::string msg = "";
	EXPECT_EQ(_socket->receive(msg), ISocket::FRAME_SUCCESS);
	EXPECT_EQ(msg.compare(ECHO_MSG), 0);

	_server.stop();
	_socket->close();
}

TEST_F(SocketUT, tcpClientSocket_returnServerClosed)
{
	_socket = new TcpSocket();

	//Start a server to test client sockets
	_server.init(ISocket::TCP_SOCKET, TEST_PORT);
	_server.runTcpServer();

	EXPECT_TRUE(_socket->connect(LOOPBACK_ADDR, TEST_PORT));
	EXPECT_EQ(_socket->status(), ISocket::CONNECTED);
	_server.stop();

	EXPECT_EQ(_socket->send(ECHO_MSG), ISocket::FRAME_ERROR);

	_socket->close();
}

TEST_F(SocketUT, udpClientSocket_returnEchoMessage)
{
	_socket = new UdpSocket(TEST_PORT + 1);
	_socket->bind(TEST_PORT + 1);
	//Start a udp server to test client sockets
	// Keep in mind that udp sockets on same process must be binded on different ports
	_server.init(ISocket::UDP_SOCKET, TEST_PORT);
	_server.runUdpServer();


	EXPECT_EQ(_socket->send(ECHO_MSG, LOOPBACK_ADDR, TEST_PORT), ISocket::FRAME_SUCCESS);
	std::string msg = "";
	std::string addr = "";
	EXPECT_EQ(_socket->receive(msg, addr), ISocket::FRAME_SUCCESS);
	EXPECT_EQ(msg, ECHO_MSG);
	_socket->close();
	_server.stop();
}

TEST_F(SocketUT, udpClientSocket_returnEchoThroughBroadcast)
{
	_socket = new UdpSocket(TEST_PORT + 1);
	//Start a udp server to test client sockets
	// Keep in mind that udp sockets on same process must be binded on different ports
	_server.init(ISocket::UDP_SOCKET, TEST_PORT, true);
	_server.runUdpServer();

	_socket->bind(TEST_PORT + 1);

	EXPECT_TRUE(_socket->enableBroadcast());

	EXPECT_EQ(_socket->send(ECHO_MSG, BCAST_ADDR, TEST_PORT), ISocket::FRAME_SUCCESS);
	std::string msg = "";
	std::string addr = "";
	EXPECT_EQ(_socket->receive(msg, addr), ISocket::FRAME_SUCCESS);
	EXPECT_EQ(msg, ECHO_MSG);
	_socket->close();
	_server.stop();
}
