#ifndef MACSA_NODE_NOTIFIER_H
#define MACSA_NODE_NOTIFIER_H

#include "utils/observer.h"
namespace Macsa {
	namespace Network {
		class NodeObserver;
		class NodeNotifier : public Utils::Notifier<NodeObserver>
		{
			protected:
				NodeNotifier();
				//Notifiers
				void notifyStatusChanged(const int& status);
				void notifyTimeout();

		};
	}
}

#endif //MACSA_NODE_NOTIFIER_H
