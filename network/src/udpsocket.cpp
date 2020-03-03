#include "udpsocket.h"

using namespace Macsa::Network;

UdpSocket::UdpSocket(uint16_t port) :
	AbstractSocket (ISocket::UDP_SOCKET)
{
	_port = port;
}

UdpSocket::~UdpSocket()
{

}
