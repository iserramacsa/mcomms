#include "unixsocket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h> ///Local address

#include <string>
#include <cstring>
#include <fcntl.h>

#ifdef DEBUG
	#include <iostream>
#endif

#if __cplusplus < 201103L
	#include <errno.h>
#endif

using namespace Macsa::Network;


UnixSocket::UnixSocket(nSocketType type) :
	ISocket (type)
{
	_sock.fd = -1;
	_port = 0;
	if (createSocket(_sock.fd, _type) /*&& init()*/) {
//		int val = 1;
//		setSocketOption(_local.fd, SO_REUSEPORT, val);
		setStatus(CREATED);
	}
}

UnixSocket::~UnixSocket()
{
	close();
}

bool UnixSocket::bind(uint16_t port)
{
	bool success = false;
	if (status() == CREATED) {
		_port = port;
		init();
		int val = 1;
		setSocketOption(_sock.fd, SO_REUSEADDR, val);
		if (::bind(_sock.fd, reinterpret_cast<struct sockaddr*>(&_sock.addr), sizeof (_sock.addr)) != -1) {
			setStatus(BINDED);
			success = true;
		}
#ifdef DEBUG
		else {
			std::cout << __func__ << "(" << _sock.fd << ") bind => " << strerror(errno)<< std::endl;
		}
#endif
	}
	return  success;
}

bool UnixSocket::listen()
{
	bool success = false;

	if (status() == BINDED) {
		success = (::listen(_sock.fd, BACKLOG_CONNECTIONS) == 0);
		if (success){
			setStatus(LISTENING);
		}
#ifdef DEBUG
		else {
			std::cout << __func__ << "(" << _sock.fd << ") listen => " << strerror(errno)<< std::endl;
		}
#endif
	}

	return success;
}

ISocket *UnixSocket::accept()
{
	UnixSocket * client = nullptr;
	if (status() == LISTENING) {
		sConnection remote;
		clearSocket(remote.addr);
		socklen_t len = sizeof (_sock.addr);

		bool expired;
		if(waitForRead(_sock.fd, WAIT_FOREVER, expired)) {
			remote.fd = ::accept(_sock.fd, reinterpret_cast<struct sockaddr*>(&remote.addr), &len);
		}

		client = socketFromConnection(remote);
	}

	return client;
}

bool UnixSocket::connect(const std::string &addr, uint16_t port)
{
	bool success = false;
	if (_sock.fd != -1) {
		sConnection remote;
		if (status() < LISTENING) {
			clearSocket(remote.addr);
			initSocket(remote.addr, addr.c_str(), port);
			success = connect(_sock.fd, remote.addr);
			if (success) {
				setStatus(CONNECTED);
			}
		}
		else {
			success = (status() <= READY);
		}
	}
	return success;
}

bool UnixSocket::connect(const std::string &addr, const std::string &port)
{
	bool success = false;
	if (_sock.fd != -1) {
		sConnection remote;
		if (status() < LISTENING) {
			clearSocket(remote.addr);
			initSocket(remote.addr, addr.c_str(), port.c_str());
			success = connect(_sock.fd, remote.addr);
			if (success) {
				setStatus(CONNECTED);
			}
		}
		else {
			success = (status() <= READY);
		}
	}
	return success;
}

ISocket::nSocketFrameStatus UnixSocket::send(const std::string &tx, int timeout)
{
	nSocketFrameStatus sent = FRAME_ERROR;
	int fd = _sock.fd;
	if (fd != -1 && status() >= CONNECTED) {
		bool expired = false;
		if (waitForWrite(fd, timeout, expired)) {
			long bytesSent = ::send(fd, tx.c_str(), tx.length(), 0);
			if (bytesSent > 0){
				if(static_cast<unsigned>(bytesSent) == tx.length()) {
					sent = FRAME_SUCCESS;
				}
				else {
					sent = FRAME_INCOMPLETED;
				}
				setStatus(CONNECTED);
			}
			else {
				sent = FRAME_ERROR;
			}
		}
		else if (expired) {
			sent = FRAME_TIMEOUT;
			setStatus(READY);
		}
	}
#ifdef DEBUG
		if (sent == FRAME_ERROR) {
			std::cout << __func__ << "(" << fd << ") => " << strerror(errno)<< std::endl;
		}
#endif
	return sent;
}

ISocket::nSocketFrameStatus UnixSocket::send(const std::string &tx, const std::string &dest, uint16_t port, int timeout)
{
	nSocketFrameStatus sent = FRAME_ERROR;
	if (_type == UDP_SOCKET){
		bool expired = false;
		if (waitForWrite(_sock.fd, timeout, expired)) {
			sConnection remote;
			initSocket(remote.addr, dest.c_str(), port);
			long bytesSent = ::sendto(_sock.fd, tx.c_str(), tx.length(),0, reinterpret_cast<struct sockaddr*>(&remote.addr), sizeof (remote.addr));
			if (bytesSent > 0){
				if(static_cast<unsigned>(bytesSent) == tx.length()) {
					sent = FRAME_SUCCESS;
				}
				else {
					sent = FRAME_INCOMPLETED;
				}
				setStatus(CONNECTED);
			}
		}
		else if (expired) {
			sent = FRAME_TIMEOUT;
			setStatus(READY);
		}
	}

	return sent;

}

ISocket::nSocketFrameStatus UnixSocket::receive(std::string &rx, int timeout)
{
	std::string dummy;
	return receive(rx, dummy, timeout);
}

ISocket::nSocketFrameStatus UnixSocket::receive(std::string &rx, std::string &addr, int timeout)
{
	nSocketFrameStatus received = FRAME_ERROR;
	char buff[DEFAULT_BUFF_SIZE  + 1] = {0};
	rx.clear();
	bool expired = false;
	if (_type == TCP_SOCKET && status() >= LISTENING){
		if (waitForRead(_sock.fd, timeout, expired)) {
			int ret = static_cast<int>(::recv(_sock.fd, buff, DEFAULT_BUFF_SIZE, 0));
			if (ret > 0) {
				if (ret > DEFAULT_BUFF_SIZE){
					buff[DEFAULT_BUFF_SIZE - 1] = '\0';
				} else {
					buff[ret] = '\0';
				}
				rx = buff;
				int len = ret;
				while(len > 0) {
					bool end = false;
					if (waitForRead(_sock.fd, 100, end)){
						memset(buff, 0, DEFAULT_BUFF_SIZE);
						len = static_cast<int>(::recv(_sock.fd, buff, DEFAULT_BUFF_SIZE, 0));
						if (len > 0) {
							if (ret > DEFAULT_BUFF_SIZE){
								buff[DEFAULT_BUFF_SIZE - 1] = '\0';
							} else {
								buff[ret] = '\0';
							}
							rx.append(buff);
						}
					}
					if (end) {
						break;
					}
				}

			}
			received = (ret > 0) ? FRAME_SUCCESS : FRAME_TIMEOUT;
		}
		else if (expired) {
			received = FRAME_TIMEOUT;
		}
	}
	else {
		if (waitForRead(_sock.fd, timeout, expired)) {
			sConnection remote;
			clearSocket(remote.addr);
			socklen_t len = sizeof(remote.addr);
			int ret = static_cast<int>(::recvfrom(_sock.fd, buff, DEFAULT_BUFF_SIZE, 0, reinterpret_cast<struct sockaddr*>(&remote.addr), &len));
			if (ret > 0) {
				rx = buff;
				addr = getAddress(remote.addr);
			}
			received = (ret > 0) ? FRAME_SUCCESS : FRAME_TIMEOUT;
		}
		else if (expired) {
			received = FRAME_TIMEOUT;
		}
	}

	if (received == FRAME_TIMEOUT) {
		setStatus(READY);
	}
	else if (received == FRAME_SUCCESS) {
		setStatus(CONNECTED);
	}

	return received;
}

bool UnixSocket::enableBroadcast()
{
	bool success = false;
	int bcast = 1;
	if (_sock.fd > -1){
		success = setSocketOption(_sock.fd, SO_BROADCAST, bcast);
	}
	return  success;
}

bool UnixSocket::close()
{
	bool success = false;

	if (_sock.fd > -1){
		int flag = fcntl(_sock.fd, F_GETFL);
		fcntl(_sock.fd, F_SETFL, flag | O_NONBLOCK);
		shutdown(_sock.fd, SHUT_RD);
		usleep(1000);
		success = (::close(_sock.fd) == 0);
		if (success){
			_sock.fd = -1;
			setStatus(UNKNOWN);
		}
	}
	return  success;
}

std::string UnixSocket::address() const
{
	std::string addr = "";

	switch (_type) {
		case TCP_SOCKET:
			addr = getAddress(_sock.addr);
			break;
		case UDP_SOCKET:
			addr = getAddress(_sock.addr);
			break;
	}

	return addr;
}

std::vector<InetAddr> UnixSocket::localAddress() const
{
	std::vector<InetAddr> local;
	struct ifaddrs *ifaddr = nullptr;
	if (getifaddrs(&ifaddr) == 0) {
		for (struct ifaddrs *ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {

		}
	}
	if (ifaddr != nullptr) {
		freeifaddrs(ifaddr);
	}


	return local;
}

bool UnixSocket::init()
{
	return  initSocket(_sock.addr, "", _port);
}

UnixSocket *UnixSocket::socketFromConnection(UnixSocket::sConnection &conn)
{
	UnixSocket * socket = nullptr;
	if (conn.fd != -1){
		socket = new UnixSocket(this->type());
		socket->_sock.fd = conn.fd;
		socket->_sock.addr = conn.addr;
		socket->setStatus(nSocketStatus::CONNECTED);
	}
	return socket;
}

bool UnixSocket::createSocket(int &fd, nSocketType type)
{
    int protocol = IPPROTO_UDP;
    int sockType = SOCK_DGRAM;
	switch (type) {
		case UDP_SOCKET:
			sockType = SOCK_DGRAM;
			protocol = IPPROTO_UDP;
			break;
		case TCP_SOCKET:
			sockType = SOCK_STREAM;
			protocol = IPPROTO_TCP;
			break;
	}

	if (fd == -1)
	{
		fd = socket(AF_INET, sockType, protocol);
#ifdef DEBUG
		if (fd == -1) {
			std::cout << __func__ << "(" << fd << ") => " << strerror(errno)<< std::endl;
		}
#endif
	}
	return (fd != -1);
}

bool UnixSocket::initSocket(sockaddr_in &socket, const char *addr, uint16_t port)
{
	bool success = false;

	clearSocket(socket);
	socket.sin_family = AF_INET;

	if (setAddress(socket, addr))  {
		if (port == 0) {
			socket.sin_port = 0;
			success = true;
		}
		else {
			socket.sin_port = htons(port);
			_port = port;
			success = true;
		}
	}

	if(success) {
		setStatus(INITIATED);
	}

	return success;
}

bool UnixSocket::initSocket(sockaddr_in &socket, const char *addr, const char *port)
{
	bool success = false;

	clearSocket(socket);
	socket.sin_family = AF_INET;

	if (setAddress(socket, addr))  {
		if (strlen(port)) {
			// Lookup the service:
			std::string proto;
			switch (_type) {
				case UDP_SOCKET:
					proto = UDP_PROTOCOL;
					break;
				case TCP_SOCKET:
					proto = TCP_PROTOCOL;
					break;
			}

			struct servent *sp = getservbyname( port, proto.c_str());
			if (sp != nullptr) {
				success = true;
				socket.sin_port = static_cast<uint16_t>(sp->s_port);
			}
		}
		else {
			success = true;
			socket.sin_port = 0;
		}
	}
	return success;
}

bool UnixSocket::setAddress(sockaddr_in &socket, const char *addr)
{
	bool success = false;

	if (strlen(addr)) {
		if  (isdigit(*addr)) {
			//Numeric IP address:
			socket.sin_addr.s_addr = inet_addr(addr);
			success = (inet_aton(addr, &socket.sin_addr) != -1);
		}
		else {
			//Assume a hostname
			struct hostent *hp = gethostbyname(addr);
			if (hp != nullptr &&  hp->h_addrtype == AF_INET) {
				success = true;
				socket.sin_addr = *(reinterpret_cast<struct in_addr*>(hp->h_addr_list[0]));
			}
		}
	}
	else {
		success = true;
		socket.sin_addr.s_addr = INADDR_ANY;
	}
#ifdef DEBUG
	if (!success) {
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
	}
#endif
	return success;
}

void UnixSocket::clearSocket(sockaddr_in &socket)
{
	memset(reinterpret_cast<char*>(&socket), 0, sizeof(socket));
}

bool UnixSocket::setSocketOption(int &fd, int optName, int &optValue)
{
	bool success = (0 == setsockopt(fd, SOL_SOCKET, optName, &optValue, sizeof (optValue)));
#ifdef DEBUG
	if (!success) {
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
	}
#endif
	return success;
}

bool UnixSocket::waitForWrite(int fd, int timeout, bool& expired)
{
	bool ready = false;
	expired = false;
	struct timeval *ptout = nullptr;
	struct timeval tout;
	if (timeout >= 0){
		tout.tv_sec = timeout / 1000;
		tout.tv_usec = (timeout - tout.tv_sec * 1000) * 1000;
		ptout = &tout;
	}

	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET(fd, &wfds);

	int ret = select(fd + 1, nullptr, &wfds, nullptr, ptout);

	ready = (ret > 0);
	expired = (ret == 0);

	return ready;
}

bool UnixSocket::waitForRead(int fd, int timeout, bool& expired)
{
	bool ready = false;
	expired = false;
	struct timeval *ptout = nullptr;
	struct timeval tout;
	if (timeout >= 0){
		tout.tv_sec = timeout / 1000;
		tout.tv_usec = (timeout - tout.tv_sec * 1000) * 1000;
		ptout = &tout;
	}

	fd_set rfds;
	fd_set excfds;
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	FD_SET(fd, &excfds);

	int ret = select(fd + 1, &rfds, nullptr, &excfds, ptout);

	if (FD_ISSET(fd, &rfds)){
		ready = (ret > 0);
	}
#if 0
	else {
		std::cout << "Select returns from exception " << ret << std::endl;
	}
#endif

	expired = (ret == 0);
#if 0
	std::cout << __func__ << " READY: " << (ready?"true":"false")
			  << " EXPIRED: " << (expired?"true":"false")<< std::endl;
#endif

	return ready;
}

bool UnixSocket::connect(int fd, const sockaddr_in &socket)
{
	bool success = false;
	success = (::connect(fd,reinterpret_cast<const struct sockaddr*>(&socket), sizeof (socket)) == 0);

	if  (success) {
		_sock.addr = socket;
	}
#ifdef DEBUG
	else{
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
	}
#endif

	return success;
}

std::string UnixSocket::getAddress(const sockaddr_in &socket) const
{
	return inet_ntoa(socket.sin_addr);
}
