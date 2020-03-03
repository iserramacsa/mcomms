#ifndef ABSTRACT_SOCKET_H
#define ABSTRACT_SOCKET_H

#if defined (__linux__) || defined (__unix__) || defined (__APPLE__) || defined (__MACH__)
#define UNIX_SOCKETS
#include "unixsocket.h"
#elif defined (_WIN32) || defined (_WIN64)
#define WIN_SOCKETS
#include "winsocket.h"
#endif

namespace Macsa {
	namespace Network {
#if defined(UNIX_SOCKETS)
		typedef UnixSocket AbstractSocket;
#elif defined (WIN_SOCKETS)
		typedef WinSocket AbstractSocket;
#endif
	}
}

#endif //ABSTRACT_SOCKET_H
