#include "tcpsocket.h"
using namespace Macsa::Network;

TcpSocket::TcpSocket(uint16_t port) :
	AbstractSocket (ISocket::TCP_SOCKET)
{
	_port = port;
}

TcpSocket::~TcpSocket()
{

}
