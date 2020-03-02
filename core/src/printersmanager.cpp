#include "printersmanager.h"
#include "tijprintercontroller.h"
#include "tijprintermonitor.h"

#include <cstdint>

#define DISCOVER_PORT  31416
#define DISCOVER_MSG "WHO ARE YOU?"

using namespace Macsa;
using namespace Macsa::Network;
using namespace std::chrono;

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
	bool added;
	if (monitorize){
		TijPrinterMonitor* controller = new TijPrinterMonitor(name, address);
		controller->connect();
		added = addNewNode(controller);
	}
	else {
		TijController* controller = new TijController(name, address);
		added = addNewNode(controller);
	}
	return added;
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

void PrintersManager::sendDiscover(int timeout)
{
	if (runDiscoverServer()) {
		std::vector<ISocket*>::const_iterator ap = accessPoint(DISCOVER_PORT);
		if (ap != _accessPoints.end()){
			ISocket* server = (*ap);
			if (server->enableBroadcast()){
				std::thread t(&PrintersManager::sendDiscoverFrames, this, std::move(server), timeout);
				t.detach();
			}
		}
	}
}

void PrintersManager::clear()
{
	MNetwork::close();
}

PrinterController * PrintersManager::getPrinter(const std::string name)
{
	return dynamic_cast<PrinterController*>(getNodeById(name));
}

PrinterController * PrintersManager::getPrinter(const uint index)
{
	return dynamic_cast<PrinterController*>(getNode(static_cast<uint>(index)));
}

bool PrintersManager::runDiscoverServer()
{
	bool running = (accessPoint(DISCOVER_PORT) != _accessPoints.end());
	if (!running) {
		running = initServer(ISocket::UDP_SOCKET, DISCOVER_PORT);
	}
	return running;
}

void PrintersManager::sendDiscoverFrames(ISocket* server, int timeout)
{
	std::atomic_bool listenDiscover;
	std::thread receive (&PrintersManager::receiveDiscoverFrames, this, std::ref(listenDiscover));

	std::vector<InetAddr> local = server->localAddress();
	steady_clock::time_point start = steady_clock::now();
	duration<double> diff = std::chrono::steady_clock::now() - start;
	while (diff.count() < timeout) {
		diff = std::chrono::steady_clock::now() - start;
		for (auto inet : local){
			uint32_t  ipv4 = inet.toIpv4() | (0x000000FF);
			if (ipv4){
				InetAddr addr (inet.name(), ipv4);
				server->send(DISCOVER_MSG, addr.toString(), DISCOVER_PORT);
			}
		}
		std::this_thread::sleep_for(seconds(1));
	}
	removeConnection(ISocket::UDP_SOCKET, DISCOVER_PORT);
	listenDiscover.store(false);
	server->close();
	receive.join();
}

#include <iostream>
void PrintersManager::receiveDiscoverFrames(std::atomic_bool &condition)
{
	condition.store(true);
	std::vector<ISocket*>::const_iterator ap = accessPoint(DISCOVER_PORT);
	if (ap != _accessPoints.end()) {
		ISocket* server = (*ap);
		if (server) {
			std::vector<InetAddr> local = server->localAddress();
			while (condition.load()) {
				std::string rx, addr;
				if (server->receive(rx, addr, WAIT_FOREVER) == ISocket::FRAME_SUCCESS) {
					std::string name = rx.substr((rx.find_first_of(",") + 1));
					if ((rx != DISCOVER_MSG) && (getPrinter(name) == nullptr)) {
						std::cout << "Discovered printer: " << name << " @:"  << addr << std::endl;
						notifyNodeDiscovered(name, addr);
					}
				}
			}
		}
	}
	std::cout << "Closing receive discover frames" << std::endl;
}

