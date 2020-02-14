#include "clientmanager.h"
#include "clientHandler.h"
#include <iostream>
#include <sstream>
#include "network/abstractsocket.h"

ClientManager::ClientManager(Printers::TIJPrinter& printer) :
	Network::MNetwork (Network::ISocket::TCP_SOCKET),
	_printer(printer)
{
//  _server = nullptr;
  _running.store(false);
  _svrPort = 0;
}

ClientManager::~ClientManager()
{
	stop();
}

bool ClientManager::initServer(uint16_t port)
{
	bool success = NetworkNode::initServer(port);
	if (success){
		_svrPort = port;
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
	NetworkNode::close();
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
		Network::AbstractSocket* clientSocket = acceptConnection();
		if (clientSocket){
			std::stringstream id;
			id << "Client" << std::to_string(_nodes.size());
			std::cout << __func__ << " " << id.str() << std::endl;
			NetworkNode* clientNode = new NetworkNode(id.str(), clientSocket);

			if (clientNode != nullptr && addNewNode(clientNode)){
				ClientHandler* handler = new ClientHandler(_printer, clientSocket, _svrPort);
				_handlers.push_back(handler);
				handler->start();
			}
		}
	}
	for (auto& handler : _handlers) {
		handler->stop();
		delete handler;
	}
	{
		std::unique_lock<std::mutex> lck(_mtx);
		_cv.notify_all();
	}
}

Network::AbstractSocket* ClientManager::acceptConnection()
{
	Network::AbstractSocket* client = nullptr;
	client = dynamic_cast<Network::AbstractSocket*>(NetworkNode::accept(_svrPort));

	if (client){
		std::cout << "Socket type:" << std::to_string(client->type()) << std::endl;
	}

	return client;
}
