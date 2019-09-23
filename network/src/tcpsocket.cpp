#include "network/tcpsocket.h"
using namespace Macsa::Network;

TcpSocket::TcpSocket() :
	AbstractSocket (ISocket::TCP_SOCKET)
{

}

TcpSocket::~TcpSocket()
{

}
