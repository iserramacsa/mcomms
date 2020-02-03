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
	_running.store(true);

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

}

void ClientManager::serverMainLoop()
{
	_running.store(true);
	while (_running.load()) {
		if (acceptConnection()){

		}
	}
}

bool ClientManager::acceptConnection()
{
	bool newClient = false;
	if (_server ){
		Network::ISocket* client = _server->accept();
		if (client != nullptr) {
			std::stringstream id;
			id << "Client" << std::to_string(_nodes.size());
			std::cout << __func__ << " " << id.str() << std::endl;
			NetworkNode* node = new NetworkNode(id.str(), client);
			newClient = addNewNode(node);
			if (!newClient) {
				delete node;
			}
		}
	}
	return newClient;
}

