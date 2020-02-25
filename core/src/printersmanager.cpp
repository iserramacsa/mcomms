#include "printersmanager.h"
#include "tijprintercontroller.h"
#include "tijprintermonitor.h"

using namespace Macsa;
using namespace Macsa::Network;

PrintersManager::PrintersManager()
{}

PrintersManager::~PrintersManager()
{}

bool PrintersManager::addTijPrinter(const std::string name, const std::string &address, bool monitorize)
{
	if (monitorize){
		TijPrinterMonitor* controller = new TijPrinterMonitor(name, address);
		return _printersNetwork.addNewNode(controller);
	}
	else {
		TijController* controller = new TijController(name, address);
		return _printersNetwork.addNewNode(controller);
	}
}

bool PrintersManager::removeTijPrinter(const std::string name)
{
	return _printersNetwork.removeNode(name);
}

bool PrintersManager::connectPrinter(const std::string name)
{
	bool connected = false;
	NetworkNode* node = _printersNetwork.getNodeById(name);
	if (node != nullptr) {
		connected = dynamic_cast<PrinterController*>(node)->connect();
	}
	return connected;
}

bool PrintersManager::disconnectPrinter(const std::string name)
{
	bool disconnected = false;
	NetworkNode* node = _printersNetwork.getNodeById(name);
	if (node != nullptr) {
		disconnected = dynamic_cast<PrinterController*>(node)->disconnect();
	}
	return disconnected;

}

PrinterController *PrintersManager::getPrinter(const std::string name)
{
	return dynamic_cast<PrinterController*>(_printersNetwork.getNodeById(name));
}

PrinterController *PrintersManager::getPrinter(const int index)
{
	return dynamic_cast<PrinterController*>(_printersNetwork.getNode(static_cast<uint>(index)));
}

unsigned int PrintersManager::size() const
{
	return _printersNetwork.size();
}

