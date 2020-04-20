#include "network/nodenotifier.h"
#include "network/nodeobserver.h"
#include "network/networknode.h"
#include <iostream>

using namespace Macsa;
using namespace Macsa::Network;

void NodeNotifier::notifyStatusChanged(const int &status)
{
	const NetworkNode::nNodeStatus nodeStatus = static_cast<const NetworkNode::nNodeStatus>(status);
	std::function<void(NodeObserver*, const NetworkNode::nNodeStatus &)> func = &NodeObserver::nodeStatusChanged;
	notifyObservers(func, nodeStatus);
}

void NodeNotifier::notifyTimeout()
{
	std::function<void(NodeObserver*)> func = &NodeObserver::nodeTimeout;
	notifyObservers(func);
}


