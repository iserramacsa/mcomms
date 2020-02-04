#include "clientHandler.h"
#include "network/tcpsocket.h"

using namespace Macsa::Network;
using namespace Macsa::MProtocol;

ClientHandler::ClientHandler(Printers::TIJPrinter &printer, ISocket *socket, uint16_t port) :
	_svrPort(port),
	_printer(printer),
	_socket(socket),
	_factory(_printer, _liveFlags)
{
	_running.store(false);
}

ClientHandler::~ClientHandler()
{
	stop();
}

bool ClientHandler::start()
{
	if (!_running.load()) {
		_running.store(true);
		_svrThread = std::thread(&ClientHandler::serverSocketLoop, this);
	}

	return _running;
}

bool ClientHandler::stop()
{
	if (_running.load()) {
		_running.store(false);
		_svrThread.join();
	}

	return !_running.load();
}


#include <iostream>
void ClientHandler::serverSocketLoop()
{
	while (_running.load()) {
		std::string frame = "";
		if (_socket->receive(frame, WAIT_FOREVER)) {
			MCommand* cmd = nullptr;
			std::cout << frame << std::endl;
			if (_factory.parseRequest(frame, &cmd)) {
				_socket->send(cmd->getResponse());
			}
		}
	}
}
