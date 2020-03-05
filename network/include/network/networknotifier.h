#ifndef MACSA_NETWORK_NOTIFIER_H
#define MACSA_NETWORK_NOTIFIER_H

#include "utils/observer.h"

namespace Macsa {
	namespace Network {
		class NetworkObserver;
		class NetworkNotifier : public Utils::Notifier<NetworkObserver>
		{
			public:
				NetworkNotifier();
				void notifyNodeDiscovered(const std::string& name, const std::string& addr);
				void notifyDatagramReceived(const std::string& addr, const std::string& datagram);
		};
	}
}

#endif //MACSA_NETWORK_NOTIFIER_H
