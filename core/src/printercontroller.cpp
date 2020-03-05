#include "tijprintercontroller.h"
#include "mprotocol/mcommandsfactory.h"

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
	return NetworkNode::connect(ISocket::TCP_SOCKET, _printerPort);
}

bool PrinterController::disconnect()
{
	return NetworkNode::disconnect(_printerPort);
}

bool PrinterController::reconnect()
{
	return NetworkNode::reconnect(ISocket::TCP_SOCKET, _printerPort);
}
