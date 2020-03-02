#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include "network/isocket.h"
#include "netinet/in.h"

namespace Macsa {
	namespace Network {
		class UnixSocket : public ISocket
		{
			public:
				UnixSocket(nSocketType type);
				virtual ~UnixSocket();

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
						int			fd;
						sockaddr_in	addr;
				};

			protected:
				virtual bool init();
				UnixSocket* socketFromConnection(sConnection& conn);

			private:
				sConnection _sock;

				bool createSocket(int& fd, nSocketType type);
				bool initSocket(struct sockaddr_in& socket, const char *addr, uint16_t port);
				bool initSocket(struct sockaddr_in& socket, const char *addr, const char *port);
				bool setAddress(struct sockaddr_in& socket,  const char *addr = "");
				void clearSocket(struct sockaddr_in& socket);
				bool setSocketOption(int &fd, int optName, int &optValue);
				bool waitForRead(int fd, int timeout, bool& expired);
				bool waitForWrite(int fd, int timeout, bool& expired);
				bool connect(int fd, const struct sockaddr_in& socket);
				inline std::string getAddress(const struct sockaddr_in& socket) const;
		};
	}
}


#endif //UNIX_SOCKET_H
