#ifndef MACSA_NETWORK_NODE_OBSERVER_H
#define MACSA_NETWORK_NODE_OBSERVER_H

#include "utils/observer.h"
#include "networknode.h"
namespace Macsa {
	namespace Network {
		class NodeNotifier;
		class NodeObserver : public Utils::Observer<NodeObserver>
		{
			public:
				NodeObserver(NodeNotifier* subject);

				virtual void nodeStatusChanged(const NetworkNode::nNodeStatus& status);
				virtual void nodeTimeout();
		};
	}
}

#endif //MACSA_NETWORK_NODE_OBSERVER_H
