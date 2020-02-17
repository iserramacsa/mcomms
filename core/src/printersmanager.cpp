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
	TIJPrinterController* controller = new TIJPrinterController(name, address);

	bool success = _tcpNetwork.addNewNode(controller);
//	if ( success) {
//		_printerAddedEvent(name);
//	}
	return success;
}

bool PrintersManager::removeTijPrinter(const std::string name)
{
	return _tcpNetwork.removeNode(name);
}

bool PrintersManager::connectPrinter(const std::string name)
{
	bool connected = false;
	NetworkNode* node = _tcpNetwork.getNodeById(name);
	if (node != nullptr) {
		connected = dynamic_cast<PrinterController*>(node)->connect();
	}
	return connected;
}

bool PrintersManager::disconnectPrinter(const std::string name)
{
	bool disconnected = false;
	NetworkNode* node = _tcpNetwork.getNodeById(name);
	if (node != nullptr) {
		disconnected = dynamic_cast<PrinterController*>(node)->disconnect();
	}
	return disconnected;

}

PrinterController *PrintersManager::getPrinter(const std::string name)
{
	return dynamic_cast<PrinterController*>(_tcpNetwork.getNodeById(name));
}

PrinterController *PrintersManager::getPrinter(const int index)
{
	return dynamic_cast<PrinterController*>(_tcpNetwork.getNode(static_cast<uint>(index)));
}

unsigned int PrintersManager::size() const
{
	return _tcpNetwork.size();
}

