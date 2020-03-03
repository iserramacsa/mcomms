#include "socketsfactory.h"
#include "tcpsocket.h"
#include "udpsocket.h"

using namespace Macsa::Network;

SocketsFactory::SocketsFactory()
{}

SocketsFactory::~SocketsFactory()
{}

ISocket *SocketsFactory::tcpSocket()
{
	return new TcpSocket();
}

ISocket *Macsa::Network::SocketsFactory::udpSocket(uint16_t port)
{
	return new UdpSocket(port);
}

ISocket *SocketsFactory::socket(ISocket::SocketType_n type, uint16_t port)
{
	switch (type) {
		case ISocket::TCP_SOCKET:
			return tcpSocket();
		case ISocket::UDP_SOCKET:
			return udpSocket(port);
	}

	return nullptr;
}
