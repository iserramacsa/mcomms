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

	bool success = _tcpNetwork.addNewNode(controller);
	if ( success) {
		_printerAddedEvent(name);
	}
	return success;
}

bool PrintersManager::connectPrinter(const std::string name)
{
	bool connected = false;
	NetworkNode* node = _tcpNetwork.getNodeById(name);
	if (node != nullptr) {
		connected = dynamic_cast<TijPrinterController*>(node)->connect();
	}
	return connected;
}

bool PrintersManager::disconnectPrinter(const std::string name)
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

TijPrinterController *PrintersManager::getPrinter(const int index)
{
	return dynamic_cast<TijPrinterController*>(_tcpNetwork.getNode(static_cast<uint>(index)));
}

unsigned int PrintersManager::size() const
{
	return _tcpNetwork.size();
}

