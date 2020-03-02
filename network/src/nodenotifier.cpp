#include "network/nodenotifier.h"
#include "network/nodeobserver.h"
#include "network/networknode.h"
#include <iostream>

using namespace Macsa;
using namespace Macsa::Network;

NodeNotifier::NodeNotifier()
{}

void NodeNotifier::notifyStatusChanged(const int &status)
{
	const NetworkNode::NodeStatus_n nodeStatus = static_cast<const NetworkNode::NodeStatus_n>(status);
	std::function<void(NodeObserver*, const NetworkNode::NodeStatus_n &)> func = &NodeObserver::nodeStatusChanged;
	notifyObservers(func, nodeStatus);
}

void NodeNotifier::notifyTimeout()
{
	std::function<void(NodeObserver*)> func = &NodeObserver::nodeTimeout;
	notifyObservers(func);
}


