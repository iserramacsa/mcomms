#ifndef MACSA_NETWORK_NODE_OBSERVER_H
#define MACSA_NETWORK_NODE_OBSERVER_H

#include "networknode.h"

namespace Macsa {
	namespace Network {
		class NodeObserver
		{
			public:
				NodeObserver(NetworkNode* subject);
				virtual ~NodeObserver();
				unsigned id() const;

				virtual void nodeStatusChanged(const NetworkNode::NodeStatus_n& status) = 0;
				virtual void nodeTimeout() = 0;

				virtual inline bool operator == (const NodeObserver& other) const { return  equal(other);}
				virtual inline bool operator != (const NodeObserver& other) const { return !equal(other);}


			private:
				const unsigned _id;
				NetworkNode* _node;

				bool equal(const NodeObserver& other) const;
		};
	}
}

#endif //MACSA_NETWORK_NODE_OBSERVER_H
