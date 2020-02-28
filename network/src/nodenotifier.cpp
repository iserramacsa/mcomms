#include "network/nodenotifier.h"
#include "network/nodeobserver.h"
#include <iostream>

using namespace Macsa;
using namespace Macsa::Network;

NodeNotifier::NodeNotifier()
{}

void NodeNotifier::notifyStatusChanged(const int &status)
{
	std::function<void(NodeObserver*, const int &)> func = &NodeObserver::nodeStatusChanged;
	notifyObservers(func, status);
}

void NodeNotifier::notifyTimeout()
{
	std::function<void(NodeObserver*)> func = &NodeObserver::nodeTimeout;
	notifyObservers(func);
}


