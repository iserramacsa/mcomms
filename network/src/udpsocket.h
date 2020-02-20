#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "abstractsocket.h"

namespace Macsa {
	namespace Network {
		class UdpSocket : public AbstractSocket
		{
			public:
				UdpSocket(uint16_t port);
				virtual ~UdpSocket();

			private:
				virtual bool listen(){return false;}
				virtual bool connect(const std::string&, uint16_t){return false;}
				virtual bool connect(const std::string&, const std::string&){return false;}
		};
	}
}


#endif //UNIX_SOCKET_H
