#include "clientmanager.h"
#include <iostream>
#include <sstream>

ClientManager::ClientManager() :
	Network::MNetwork (Network::ISocket::TCP_SOCKET)
{
  _server = nullptr;
  _running.store(false);
}

ClientManager::~ClientManager()
{
	stop();
}

bool ClientManager::initServer(uint16_t port)
{
	bool success = (_server != nullptr);
	if (_server == nullptr) {
		Network::ISocket::SocketType_n type = Network::ISocket::TCP_SOCKET;
		Network::ISocket *sock = _rootNode->socket(type, 0);
		if (!sock) {
			sock = _rootNode->socket(type, port);
		}
		if (sock) {
			success = (sock->bind(port) && sock->listen());
			if (success) {
				_server = sock;
			}
		}
	}
	return success;
}

void ClientManager::run(bool detached)
{
	if (!detached){
		return serverMainLoop();
	}
	else {
		_svrLoop = std::thread(&ClientManager::serverMainLoop, this);
	}
}

void ClientManager::stop()
{
	_running.store(false);
	_server->close();
	{
		std::unique_lock<std::mutex> lck(_mtx);
		_cv.wait(lck);
	}
	_svrLoop.joinable();
}

void ClientManager::serverMainLoop()
{
	_running.store(true);
	while (_running.load()) {
		NetworkNode* client = acceptConnection();
		if (client != nullptr){

		}
	}
	{
		std::unique_lock<std::mutex> lck(_mtx);
		_cv.notify_all();
	}
}

Network::NetworkNode* ClientManager::acceptConnection()
{
	NetworkNode* newClient = nullptr;
	if (_server ){
		Network::ISocket* client = _server->accept();
		if (client != nullptr) {
			std::stringstream id;
			id << "Client" << std::to_string(_nodes.size());
			std::cout << __func__ << " " << id.str() << std::endl;
			newClient = new NetworkNode(id.str(), client);
		}
	}

	return newClient;
}
