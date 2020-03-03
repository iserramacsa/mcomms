#include "network/nodeobserver.h"
#include "network/nodenotifier.h"
using namespace Macsa::Network;

NodeObserver::NodeObserver(NodeNotifier *subject) :
	Utils::Observer<NodeObserver>(subject){}

void NodeObserver::nodeStatusChanged(const NetworkNode::NodeStatus_n &/*status*/)
{}

void NodeObserver::nodeTimeout()
{}
