#include "socket_moc.h"


SocketMockable::SocketMockable(ISocket::nSocketType type, uint16_t port) :
	AbstractSocket(type)
{
	EXPECT_CALL(*this, port()).WillRepeatedly(::testing::Return(port));
}

SocketMockable::~SocketMockable()
{}

uint16_t SocketMockable::mock_port()
{
	return AbstractSocket::port();
}

ISocket::nSocketStatus SocketMockable::mock_status()
{
	return AbstractSocket::status();
}

std::string SocketMockable::mock_address() const
{
	return AbstractSocket::address();
}

bool SocketMockable::mock_bind(uint16_t port)
{
	return AbstractSocket::bind(port);
}

bool SocketMockable::mock_listen()
{
	return AbstractSocket::listen();
}

ISocket *SocketMockable::mock_accept()
{
	return AbstractSocket::accept();
}

bool SocketMockable::mock_connect(const std::string& addr, uint16_t port)
{
	return AbstractSocket::connect(addr, port);
}

bool SocketMockable::mock_connect(const std::string& addr, const std::string& port)
{
	return AbstractSocket::connect(addr, port);
}

ISocket::nSocketFrameStatus SocketMockable::mock_send(const std::string& tx, int timeout)
{
	return AbstractSocket::send(tx, timeout);
}

ISocket::nSocketFrameStatus SocketMockable::mock_send(const std::string& tx, const std::string& dest, uint16_t port, int timeout)
{
	return AbstractSocket::send(tx, dest, port, timeout);
}

ISocket::nSocketFrameStatus SocketMockable::mock_receive(std::string& rx, int timeout)
{
	return AbstractSocket::receive(rx, timeout);
}

ISocket::nSocketFrameStatus SocketMockable::mock_receive(std::string& rx, std::string& addr, int timeout)
{
	return AbstractSocket::receive(rx, addr, timeout);
}

bool SocketMockable::mock_close()
{
	return AbstractSocket::close();
}

bool SocketMockable::mock_enableBroadcast()
{
	return AbstractSocket::enableBroadcast();
}

bool SocketMockable::mock_init()
{
	return AbstractSocket::init();
}
