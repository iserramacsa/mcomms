#include "printersmanager.h"
#include "tijprintercontroller.h"
#include "tijprintermonitor.h"

#include <cstdint>

#define DISCOVER_PORT  31416
#define CLIENT_MSG "WHO ARE YOU?"

using namespace Macsa;
using namespace Macsa::Network;

PrintersManager::PrintersManager()
{}

PrintersManager::~PrintersManager()
{}

unsigned int PrintersManager::size() const
{
	return MNetwork::size();
}

bool PrintersManager::addTijPrinter(const std::string name, const std::string &address, bool monitorize)
{
	if (monitorize){
		TijPrinterMonitor* controller = new TijPrinterMonitor(name, address);
		return addNewNode(controller);
	}
	else {
		TijController* controller = new TijController(name, address);
		return addNewNode(controller);
	}
}

bool PrintersManager::removeTijPrinter(const std::string name)
{
	return removeNode(name);
}

bool PrintersManager::connectPrinter(const std::string name)
{
	bool connected = false;
	NetworkNode* node = getNodeById(name);
	if (node != nullptr) {
		connected = dynamic_cast<PrinterController*>(node)->connect();
	}
	return connected;
}

bool PrintersManager::disconnectPrinter(const std::string name)
{
	bool disconnected = false;
	NetworkNode* node = getNodeById(name);
	if (node != nullptr) {
		disconnected = dynamic_cast<PrinterController*>(node)->disconnect();
	}
	return disconnected;

}

void PrintersManager::sendDiscover()
{
	if (initServer(ISocket::UDP_SOCKET, DISCOVER_PORT)) {

	}
}

PrinterController *PrintersManager::getPrinter(const std::string name)
{
	return dynamic_cast<PrinterController*>(getNodeById(name));
}

PrinterController *PrintersManager::getPrinter(const uint index)
{
	return dynamic_cast<PrinterController*>(getNode(static_cast<uint>(index)));
}

