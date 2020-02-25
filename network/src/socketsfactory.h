#ifndef NETWORK_SOCKETS_FACTORY_H
#define NETWORK_SOCKETS_FACTORY_H
#include "network/isocket.h"

namespace Macsa {
	namespace Network {

		class SocketsFactory
		{
			public:
				SocketsFactory();
				~SocketsFactory();
				ISocket* tcpSocket();
				ISocket* udpSocket(uint16_t port);
				ISocket* socket(ISocket::SocketType_n type, uint16_t port);
		};
	}
}


#endif //NETWORK_SOCKETS_FACTORY_H
