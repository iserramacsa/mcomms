#ifndef MACSA_MNETWORK_WINDOWS_SOCKET_H
#define MACSA_MNETWORK_WINDOWS_SOCKET_H

#include "network/isocket.h"
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

namespace Macsa {
	namespace Network {

		class WinSocket : public ISocket
		{
			public:
				WinSocket(nSocketType type);
				virtual ~WinSocket();

				virtual bool bind(uint16_t port);
				virtual bool listen();
				virtual ISocket* accept();
				virtual bool connect(const std::string& addr, uint16_t port);
				virtual bool connect(const std::string& addr, const std::string& port);
				virtual nSocketFrameStatus send(const std::string& tx, int timeout = NO_WAIT);
				virtual nSocketFrameStatus send(const std::string& tx, const std::string& dest, uint16_t port, int timeout = NO_WAIT);
				virtual nSocketFrameStatus receive(std::string& rx, int timeout = DEFAULT_TIMEOUT);
				virtual nSocketFrameStatus receive(std::string& rx, std::string& addr, int timeout = DEFAULT_TIMEOUT);
				virtual bool enableBroadcast();
				virtual bool close();
				virtual std::string address() const;
				virtual std::vector<InetAddr> localAddress() const;

			protected:
				struct sConnection {
					SOCKET		fd;
					sockaddr_in	addr;
					int			addrLen;
				};

			protected:
				virtual bool init();
//				WinSocket* socketFromConnection(sConnection& conn);

			private:
				WSADATA _wsaData;
				sConnection _sock;

				void initWinSocket();

				bool createSocket(SOCKET& fd, nSocketType type);
//				bool initSocket(struct sockaddr_in& socket, const char *addr, uint16_t port);
//				bool initSocket(struct sockaddr_in& socket, const char *addr, const char *port);
//				bool setAddress(struct sockaddr_in& socket,  const char *addr = "");
//				void clearSocket(struct sockaddr_in& socket);
				bool setSocketOption(SOCKET &fd, int optName, int &optValue);
//				bool waitForRead(int fd, int timeout, bool& expired);
//				bool waitForWrite(int fd, int timeout, bool& expired);
//				bool connect(int fd, const struct sockaddr_in& socket);
//				inline std::string getAddress(const struct sockaddr_in& socket) const;
		};
	}
}


#endif //MACSA_MNETWORK_WINDOWS_SOCKET_H
