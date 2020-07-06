#include "winsocket.h"
#include <string>
#include <errno.h>

#if __cplusplus < 201103L
#include <errno.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

using namespace Macsa::Network;

WinSocket::WinSocket(ISocket::nSocketType type) :
	ISocket(type)
{
	initWinSocket();
	_sock.fd = INVALID_SOCKET;
	_port = 0;
	if (createSocket(_sock.fd, _type)) {
		setStatus(CREATED);
	}	
}

WinSocket::~WinSocket()
{
	close();
}

bool WinSocket::bind(uint16_t port) 
{
	bool success = false;

	if (status() == CREATED) {
		_port = port;
		init();				//TODO: review
		int val = 1;		//TODO: review
		setSocketOption(_sock.fd, SO_REUSEADDR, val); //TODO: review

		success = (::bind(_sock.fd, reinterpret_cast<struct sockaddr*>(&_sock.addr), sizeof(_sock.addr)) != SOCKET_ERROR);
		if (success) {
			setStatus(BINDED);
		}
		else {
			std::cout << "Bind socket Error: " << WSAGetLastError()<< std::endl;
		}
	}

	return success; 
}

bool WinSocket::listen()
{ 
	bool success = false;

	if (status() == BINDED) {
		success = (::listen(_sock.fd, BACKLOG_CONNECTIONS) == 0);
		if (success) {
			setStatus(LISTENING);
		}
#ifdef DEBUG
		else {
			std::cout << __func__ << "(" << _sock.fd << ") listen => " << strerror(errno) << std::endl;
		}
#endif
	}

	return success;
}

ISocket* WinSocket::accept()
{
	//TODO
	return nullptr; 
}

bool WinSocket::connect(const std::string& addr, uint16_t port)
{
	//TODO
	return false;
}

bool WinSocket::connect(const std::string& addr, const std::string& port)
{
	//TODO
	return false;
}

ISocket::nSocketFrameStatus WinSocket::send(const std::string& tx, int timeout)
{
	//TODO
	return ISocket::FRAME_ERROR;
}

ISocket::nSocketFrameStatus WinSocket::send(const std::string& tx, const std::string& dest, uint16_t port, int timeout)
{
	//TODO
	return ISocket::FRAME_ERROR;
}

ISocket::nSocketFrameStatus WinSocket::receive(std::string& rx, int timeout)
{
	//TODO
	return ISocket::FRAME_ERROR;
}

ISocket::nSocketFrameStatus WinSocket::receive(std::string& rx, std::string& addr, int timeout)
{
	//TODO
	return ISocket::FRAME_ERROR;
}

bool WinSocket::enableBroadcast()
{
	//TODO
	return false;
}

bool WinSocket::close()
{
	//TODO

	WSACleanup();
	return false;
}

std::string WinSocket::address() const
{
	//TODO
	return std::string();
}

std::vector<InetAddr> WinSocket::localAddress() const
{
	//TODO
	return std::vector<InetAddr>();
}


bool WinSocket::init()
{
	//TODO
	return false;
}

void WinSocket::initWinSocket()
{
	int ret = WSAStartup(MAKEWORD(2, 2), &_wsaData);
	if (ret) {
		perror("ERROR:\tOpening library WSAStartup\n");
	}
}

bool WinSocket::createSocket(SOCKET& fd, nSocketType type)
{
	if (fd == INVALID_SOCKET)
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

		fd = socket(AF_INET, sockType, protocol);
#ifdef DEBUG
		if (fd == INVALID_SOCKET) {
			std::cout << __func__ << "(" << fd << ") => " << strerror(errno) << std::endl;
		}
#endif
	}
	return (fd != INVALID_SOCKET);

}

bool WinSocket::setSocketOption(SOCKET &fd, int optName, int &optValue)
{
	bool success = false;// (0 == setsockopt(fd, SOL_SOCKET, optName, &optValue, sizeof(optValue)));
#ifdef DEBUG
	if (!success) {
		std::cout << __func__ << " => " << strerror(errno) << std::endl;
	}
#endif
	return success;
}


/******************************************************************************************************/
/* INFO SOURCES: */
/* 		https://www.codeproject.com/Articles/1904/Beginning-Winsock-Programming-Simple-TCP-client */
/* 		https://docs.microsoft.com/en-us/windows/desktop/WinSock/porting-socket-applications-to-winsock */
/* 		https://docs.microsoft.com/en-us/windows/desktop/winsock/getting-started-with-winsock */
/* 		https://tangentsoft.net/wskfaq/articles/bsd-compatibility.html */

//  ClientWinSocket::ClientWinSocket()
//  {
//  	_connectSocket		= INVALID_SOCKET;
//  	_opened		= false;
//  	_connected	= false;
//  	/* pthread_mutex_init ( &_mutex, NULL); */
//  }
//  
//  ClientWinSocket::~ClientWinSocket()
//  {
//  	disconnect();
//  }
//  
//  bool ClientWinSocket::open()
//  {
//  	if (!isOpen)
//  	{
//  		int winSockLib = WSAStartup(MAKEWORD(2, 2), &wsaData);
//  		if (winSockLib){
//  			error("ERROR:\tOpening library WSAStartup\n");
//  			return _opened;
//  		}
//  		_connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//  		if (_connectSocket == INVALID_SOCKET){
//  			error("ERROR:\tOpening socket\n");
//  		}
//  		else{
//  			_opened = true;
//  		}
//  	}
//  	return _opened;
//  }
//  
//  bool ClientWinSocket::connectTo(const char *address, int port)
//  {
//  	if(isOpen() && isValidConnectionData(address, port)){
//  		unsigned long addr = inet_addr(address); //convert IP into standard network address
//  		struct hostent *hostInfo;
//  		hostInfo = getnameinfo((char *) &addr, sizeof(addr), AF_INET);
//  		if (hostInfo == NULL){
//  			disconnect();
//  			error("ERROR:\tNo such hostn\n");
//  			_connected = false;
//  			return _connected;
//  		}
//  		_connected = connect(_connectSocket,(char *) &addr, sizeof(addr));
//  		if (!_connected){
//  			disconnect();
//  			error("ERROR:\tConnecting\n");
//  			_connected = false;
//  			return _connected;
//  		}
//  	}
//  	return _connected;
//  }
//  
//  bool ClientWinSocket::disconnect()
//  {
//  	/* pthread_mutex_lock(&_mutex); */
//  	if(_opened){
//  		closesocket(_connectSocket);
//  		_opened = false;
//  		_connected = false;
//  	}
//  	/* pthread_mutex_unlock(&_mutex); */
//  	return !_opened;
//  }
//  
//  bool ClientWinSocket::send(const char *tx)
//  {
//  	if (_connected){
//  		int sendResult = send(_connectSocket, tx, strlen(tx), 0);
//  
//  		if (sendResult == SOCKET_ERROR){
//  			error("ERROR:\tSending\n");
//  			return false;
//  		}
//  	}
//  	return true;
//  }
//  
//  bool ClientWinSocket::receive(char &rx, int timeout)
//  {
//  	if (_connected){
//  		int recvBufLen = DEFAULT_BUFLEN;
//  		int receiveResult = recv(_connectSocket, recvbuf, recvBufLen, 0);
//  		if (receiveResult > 0){
//  			error("ERROR:\tReceiving\n");
//  			return false;
//  		}
//  	}
//  	return true;
//  }
//  
//  bool ClientWinSocket::isOpen() const
//  {
//  	return _opened;
//  }
//  
//  bool ClientWinSocket::connectToServer(int fd, struct sockaddr * addr)
//  {
//  	int success = connect(_connectSocket, addr, sizeof(*addr));
//  
//  	if (success == -1) {
//  		perror(__PRETTY_FUNCTION__);
//  	}
//  
//  	return (success == 0);
//  }
//  
//  bool ClientWinSocket::isValidConnectionData(const char *address, int port)
//  {
//  	bool validAddress = false;
//  	bool validPort = false;
//  	std::string add = address;
//  
//  	if (add.size() >= 7) {
//  		std::vector<std::string> vals = utils::split(add, '.');
//  		if(vals.size() == 4){
//  			for (unsigned int i = 0; i < vals.size(); i++){
//  				int val = std::atoi(vals.at(i).c_str());
//  				validAddress = (val >= 0 && val <= 255);
//  				if (!validAddress) {
//  					break;
//  				}
//  			}
//  		}
//  	}
//  	validPort = (port > 0 && port < 0xFFFF);
//  
//  	return validAddress && validPort;
//  }
//
