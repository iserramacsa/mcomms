#include "network/networknotifier.h"
#include "network/networkobserver.h"
#include <iostream>

using namespace Macsa;
using namespace Macsa::Network;

NetworkNotifier::NetworkNotifier() :
	Utils::Notifier<NetworkObserver>()
{}

void NetworkNotifier::notifyNodeDiscovered(const std::string &name, const std::string &addr)
{
	std::function<void(NetworkObserver*, const std::string&, const std::string&)>func = &NetworkObserver::nodeDiscovered;
	notifyObservers(func, name, addr);
}

