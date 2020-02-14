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
	int error = 0;
	while (_running.load()) {
		std::string frame = "";
		ISocket::nSocketFrameStatus status = _socket->receive(frame, WAIT_FOREVER);
		if (status == ISocket::FRAME_SUCCESS) {
			error = 0;
			MCommand* cmd = nullptr;
			std::cout << frame << std::endl;
			if (_factory.parseRequest(frame, &cmd)) {
				std::string tx = cmd->getResponse();
				_socket->send(tx);
				std::cout << tx << std::endl;
			}
		}
		else {
			switch (status) {
				case ISocket::FRAME_ERROR:		 std::cout << "FRAME ERROR" << std::endl;break;
				case ISocket::FRAME_TIMEOUT:	 std::cout << "FRAME TIMEOUT" << std::endl; error++; break;
				case ISocket::FRAME_INCOMPLETED: std::cout << "FRAME INCOMPLETED" << std::endl;	break;
				default: std::cout << "UNKNOWN" << std::endl; break;
			}

			if(error >= 10){
				std::cout << "Client " << _socket->address() << " disconnected" << std::endl;
				_running.store(false);
			}
		}
	}
}
