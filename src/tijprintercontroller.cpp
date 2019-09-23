#include "tijprintercontroller.h"
#include "printer/printer.h"
#include "network/tcpsocket.h"

#define MPROTOCOL_PORT	9991

using namespace Macsa;
using namespace Macsa::Network;

TijPrinterController::TijPrinterController(const std::string &id, const std::string &address) :
	Network::NetworkNode(id, address)
{
	_running.store(false);

	addConnection(ISocket::TCP_SOCKET, MPROTOCOL_PORT);
}

TijPrinterController::~TijPrinterController()
{}

bool TijPrinterController::connect()
{
	TcpSocket* socket = dynamic_cast<TcpSocket*>(NetworkNode::socket(ISocket::TCP_SOCKET, MPROTOCOL_PORT));
	if (socket != nullptr){
		socket->connect(address(), MPROTOCOL_PORT);
		return (socket->status() == ISocket::CONNECTED);
	}
	else {
		return false;
	}
}

bool TijPrinterController::disconnect()
{
	TcpSocket* socket = dynamic_cast<TcpSocket*>(NetworkNode::socket(ISocket::TCP_SOCKET, MPROTOCOL_PORT));
	if (socket != nullptr){
		socket->close();
		return (socket->status() == ISocket::UNKNOWN);
	}
	else{
		return false;
	}
}


void TijPrinterController::run()
{
	//TODO
}
