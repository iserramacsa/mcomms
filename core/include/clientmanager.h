#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "network/network.h"

using namespace Macsa;

class ClientManager : public Network::MNetwork
{
	public:
		ClientManager(uint16_t port);
		~ClientManager();

	private:

};

#endif //CLIENT_MANAGER_H
