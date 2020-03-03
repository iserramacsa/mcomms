#ifndef MACSA_NETWORK_OBSERVER_H
#define MACSA_NETWORK_OBSERVER_H

#include "utils/observer.h"

namespace Macsa {
	namespace Network {
		class NetworkNotifier;
		class NetworkObserver : public Utils::Observer<NetworkObserver>
		{
			public:
				NetworkObserver(NetworkNotifier* subject);
				virtual void nodeDiscovered(const std::string& name, const std::string& addr){}
				virtual void datagramReceived(const std::string& addr, const std::string& datagram){}
		};
	}
}

#endif //MACSA_NETWORK_OBSERVER_H
