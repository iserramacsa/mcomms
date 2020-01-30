#include "tijprintercontroller.h"
#include "mprotocol/mcommandsfactory.h"
#include "network/tcpsocket.h"

using namespace Macsa;
using namespace Macsa::Network;

PrinterController::PrinterController(const std::string &id, const std::string &address, uint16_t port) :
	Network::NetworkNode(id, address),
	_printerPort(port)
{
	addConnection(ISocket::TCP_SOCKET, port);
}

PrinterController::~PrinterController()
{}

bool PrinterController::connect()
{
	TcpSocket* socket = dynamic_cast<TcpSocket*>(NetworkNode::socket(ISocket::TCP_SOCKET, _printerPort));
	if (socket != nullptr){
		socket->connect(address(), _printerPort);
		return (socket->status() == ISocket::CONNECTED);
	}
	else {
		return false;
	}
}

bool PrinterController::disconnect()
{
	TcpSocket* socket = dynamic_cast<TcpSocket*>(NetworkNode::socket(ISocket::TCP_SOCKET, _printerPort));
	if (socket != nullptr){
		socket->close();
		return (socket->status() == ISocket::UNKNOWN);
	}
	else{
		return false;
	}
}
