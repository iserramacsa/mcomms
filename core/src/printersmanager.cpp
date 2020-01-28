#include "printersmanager.h"
#include "network/tcpsocket.h"
#include "tijprintercontroller.h"

using namespace Macsa;
using namespace Macsa::Network;

PrintersManager::PrintersManager() :
	_tcpNetwork(ISocket::TCP_SOCKET)
{}

PrintersManager::~PrintersManager()
{}

bool PrintersManager::addTijPrinter(const std::string name, const std::string &address)
{
	TijPrinterController* controller = new TijPrinterController(name, address);

	return  _tcpNetwork.addNewNode(controller);
}

bool PrintersManager::connectTijPrinter(const std::string name)
{
	bool connected = false;
	NetworkNode* node = _tcpNetwork.getNodeById(name);
	if (node != nullptr) {
		connected = dynamic_cast<TijPrinterController*>(node)->connect();
	}
	return connected;
}

bool PrintersManager::disconnectTijPrinter(const std::string name)
{
	bool disconnected = false;
	NetworkNode* node = _tcpNetwork.getNodeById(name);
	if (node != nullptr) {
		disconnected = dynamic_cast<TijPrinterController*>(node)->disconnect();
	}
	return disconnected;

}

TijPrinterController *PrintersManager::getPrinter(const std::string name)
{
	return dynamic_cast<TijPrinterController*>(_tcpNetwork.getNodeById(name));
}

