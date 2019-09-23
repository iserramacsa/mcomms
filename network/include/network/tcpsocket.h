#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "abstractsocket.h"

namespace Macsa {
	namespace Network {
		class TcpSocket: public AbstractSocket
		{
			public:
				TcpSocket();
				virtual ~TcpSocket();
			private:
				virtual bool enableBroadcast(){return false;}
		};
	}
}


#endif //UNIX_SOCKET_H
