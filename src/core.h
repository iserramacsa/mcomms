#ifndef MCOMM_CORE_H
#define MCOMM_CORE_H

#include "network/network.h"

namespace Macsa {
	namespace MComm {
		class CommCore {
			public:
				CommCore();
				~CommCore();

			private:
				Network::MNetwork _network;
		};
	}
}

#endif
