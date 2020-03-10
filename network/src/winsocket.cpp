#include "winsocket.h"

using namespace Macsa::Network;

WinSocket::WinSocket(ISocket::nSocketType type)
{

}


/******************************************************************************************************/
#include "winsockets.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "strings.hpp"

/* INFO SOURCES: */
/* 		https://www.codeproject.com/Articles/1904/Beginning-Winsock-Programming-Simple-TCP-client */
/* 		https://docs.microsoft.com/en-us/windows/desktop/WinSock/porting-socket-applications-to-winsock */
/* 		https://docs.microsoft.com/en-us/windows/desktop/winsock/getting-started-with-winsock */
/* 		https://tangentsoft.net/wskfaq/articles/bsd-compatibility.html */

ClientWinSocket::ClientWinSocket()
{
	_connectSocket		= INVALID_SOCKET;
	_opened		= false;
	_connected	= false;
	/* pthread_mutex_init ( &_mutex, NULL); */
}

ClientWinSocket::~ClientWinSocket()
{
	disconnect();
}

bool ClientWinSocket::open()
{
	if (!isOpen)
	{
		int winSockLib = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (winSockLib){
			error("ERROR:\tOpening library WSAStartup\n");
			return _opened;
		}
		_connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_connectSocket == INVALID_SOCKET){
			error("ERROR:\tOpening socket\n");
		}
		else{
			_opened = true;
		}
	}
	return _opened;
}

bool ClientWinSocket::connectTo(const char *address, int port)
{
	if(isOpen() && isValidConnectionData(address, port)){
		unsigned long addr = inet_addr(address); //convert IP into standard network address
		struct hostent *hostInfo;
		hostInfo = getnameinfo((char *) &addr, sizeof(addr), AF_INET);
		if (hostInfo == NULL){
			disconnect();
			error("ERROR:\tNo such hostn\n");
			_connected = false;
			return _connected;
		}
		_connected = connect(_connectSocket,(char *) &addr, sizeof(addr));
		if (!_connected){
			disconnect();
			error("ERROR:\tConnecting\n");
			_connected = false;
			return _connected;
		}
	}
	return _connected;
}

bool ClientWinSocket::disconnect()
{
	/* pthread_mutex_lock(&_mutex); */
	if(_opened){
		closesocket(_connectSocket);
		_opened = false;
		_connected = false;
	}
	/* pthread_mutex_unlock(&_mutex); */
	return !_opened;
}

bool ClientWinSocket::send(const char *tx)
{
	if (_connected){
		int sendResult = send(_connectSocket, tx, strlen(tx), 0);

		if (sendResult == SOCKET_ERROR){
			error("ERROR:\tSending\n");
			return false;
		}
	}
	return true;
}

bool ClientWinSocket::receive(char &rx, int timeout)
{
	if (_connected){
		int recvBufLen = DEFAULT_BUFLEN;
		int receiveResult = recv(_connectSocket, recvbuf, recvBufLen, 0);
		if (receiveResult > 0){
			error("ERROR:\tReceiving\n");
			return false;
		}
	}
	return true;
}

bool ClientWinSocket::isOpen() const
{
	return _opened;
}

bool ClientWinSocket::connectToServer(int fd, struct sockaddr * addr)
{
	int success = connect(_connectSocket, addr, sizeof(*addr));

	if (success == -1) {
		perror(__PRETTY_FUNCTION__);
	}

	return (success == 0);
}

bool ClientWinSocket::isValidConnectionData(const char *address, int port)
{
	bool validAddress = false;
	bool validPort = false;
	std::string add = address;

	if (add.size() >= 7) {
		std::vector<std::string> vals = utils::split(add, '.');
		if(vals.size() == 4){
			for (unsigned int i = 0; i < vals.size(); i++){
				int val = std::atoi(vals.at(i).c_str());
				validAddress = (val >= 0 && val <= 255);
				if (!validAddress) {
					break;
				}
			}
		}
	}
	validPort = (port > 0 && port < 0xFFFF);

	return validAddress && validPort;
}
