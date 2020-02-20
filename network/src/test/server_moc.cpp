#include "server_moc.h"
#include "tcpsocket.h"
#include "udpsocket.h"

ServerMockable::ServerMockable()
{
	_server = nullptr;
	_running.store(false);
}

ServerMockable::~ServerMockable()
{
	if(_server != nullptr){
		delete _server;
	}
}

bool ServerMockable::init(ISocket::SocketType_n type, uint16_t port, bool bcast)
{
	bool initiated = false;
	switch (type) {
		case ISocket::TCP_SOCKET:
			_server = new TcpSocket();
			_server->bind(port);
			_server->listen();
			initiated = (_server->status() == ISocket::LISTENING);
			break;
		case ISocket::UDP_SOCKET:
			_server = new UdpSocket(port);
			if (bcast) {
				_server->enableBroadcast();
			}
			_server->bind(port);
			_udpPort = port;
			initiated = (_server->status() == ISocket::BINDED);
			break;
	}

	_running.store(initiated);
	return initiated;
}

void ServerMockable::run(std::function<void (AbstractSocket *)> onNewConnection)
{
	std::unique_lock<std::mutex>lock(_mutex);
	_serverThread = std::thread(&ServerMockable::serverMainLoop, this, onNewConnection);
	_cv.wait(lock);
}

void ServerMockable::runTcpServer()
{
	return run (std::bind(&ServerMockable::echoSocketLoop, this, std::placeholders::_1));
}

void ServerMockable::runUdpServer()
{
	std::unique_lock<std::mutex>lock(_mutex);
	_serverThread = std::thread(&ServerMockable::echoSocketLoop, this, _server);
	_cv.wait(lock);
}

void ServerMockable::stop()
{
	if (_server != nullptr && _running.load()){
		{
			std::unique_lock<std::mutex>lock(_mutex);
			_running.store(false);
			_server->close();
			if (_server->type() == ISocket::TCP_SOCKET) {
				if(_cv.wait_for(lock, std::chrono::milliseconds(500)) == std::cv_status::timeout) {
					std::cout << __PRETTY_FUNCTION__ << ": Waiting for close server timed out" << std::endl;
				}
			}
		}
		_serverThread.join();
	}
}

void ServerMockable::serverMainLoop(std::function<void (AbstractSocket*)> onNewConnection)
{
	std::vector<std::tuple <AbstractSocket*, std::thread>> clients;
	{
		std::unique_lock<std::mutex>lock(_mutex);
		_cv.notify_one();
	}

	while (_running.load())
	{
		AbstractSocket* client = dynamic_cast<AbstractSocket*>(_server->accept());
		if(client !=  nullptr) {
			clients.push_back(std::make_tuple(client, std::thread(std::bind(onNewConnection, client))));
		}
	}
	{
		std::unique_lock<std::mutex>lock(_mutex);
		_cv.notify_all();
	}

	for (auto& client : clients) {
		AbstractSocket* sock = std::get<0>(client);
		std::thread& th = std::get<1>(client);
		sock->close();
		th.join();
		delete sock;
	}

	clients.clear();
}

void ServerMockable::echoSocketLoop(AbstractSocket *socket)
{
	{
		std::unique_lock<std::mutex>lock(_mutex);
		_cv.notify_one();
	}
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
					socket->send(message, addr, (_udpPort + 1));
					break;
			}
		}
	}

}
