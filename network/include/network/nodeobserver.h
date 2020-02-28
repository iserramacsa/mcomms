#ifndef MACSA_NETWORK_NODE_OBSERVER_H
#define MACSA_NETWORK_NODE_OBSERVER_H

#include "utils/observer.h"
namespace Macsa {
	namespace Network {
		class NodeObserver : public Utils::Observer<NodeObserver>
		{
			public:
				NodeObserver(Utils::Notifier<NodeObserver>* subject) :
					Utils::Observer<NodeObserver>(subject){}

				virtual void nodeStatusChanged(const int& status){;}
				virtual void nodeTimeout(){;}
		};
	}
}

#endif //MACSA_NETWORK_NODE_OBSERVER_H
