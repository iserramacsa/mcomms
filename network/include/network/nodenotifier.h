#ifndef MACSA_NODE_NOTIFIER_H
#define MACSA_NODE_NOTIFIER_H

#include "utils/observer.h"
namespace Macsa {
	namespace Network {
		class NodeObserver;//
		/**
		 * @brief The NodeNotifier class. Implementation of Utils::Notifier class
		 *
		 * NodeNotifier like as a Notifier class, allows the inherited classes to call the NodeObserver callbacks.
		 * The inherited classes can notify if network node has changed the status or if last receive call returns by timeout
		 */
		class NodeNotifier : public Utils::Notifier<NodeObserver>
		{
			protected:
				//Notifications
				/**
				 * @brief notifyStatusChanged. When this method is called the observers
				 * are notified of the inherited notifier class has changed its status.
				 * @param status. Int with the NetworkNode new status.
				 */
				void notifyStatusChanged(const int& status);
				/**
				 * @brief notifyTimeoutWhen this method is called the observers
				 * are notified of the inherited notifier class performas a receive calls
				 * that returns timeout.
				 */
				void notifyTimeout();

		};
	}
}

#endif //MACSA_NODE_NOTIFIER_H
