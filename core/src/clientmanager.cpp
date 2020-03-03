#include "clientmanager.h"
#include "clientHandler.h"
#include <iostream>
#include <sstream>

ClientManager::ClientManager(Printers::TijPrinter& printer) :
	Network::MNetwork (),
	_printer(printer)
{
  _running.store(false);
  _svrPort = 0;
}

ClientManager::~ClientManager()
{
	stop();
}

bool ClientManager::initTcpServer(uint16_t port)
{
	bool success = initServer(ISocket::TCP_SOCKET, port);
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
		Network::ISocket* clientSocket = acceptConnection();
		if (clientSocket){
			std::stringstream id;
			id << "Client" << std::to_string(_nodes.size());
			std::cout << __func__ << " " << id.str() << std::endl;
			NetworkNode* clientNode = new NetworkNode(id.str());
			clientNode->addConnection(clientSocket);

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

Network::ISocket* ClientManager::acceptConnection()
{
	Network::ISocket* client = nullptr;
	client = dynamic_cast<Network::ISocket*>(NetworkNode::accept(_svrPort));

	if (client){
		std::cout << "Socket type:" << std::to_string(client->type()) << std::endl;
	}

	return client;
}
