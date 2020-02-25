#ifndef SOCKET_MOCK_H
#define SOCKET_MOCK_H

#include <gmock/gmock.h>
#include "abstractsocket.h"

using namespace Macsa::Network;

class SocketMockable : public AbstractSocket
{
	public:
		SocketMockable(SocketType_n type, uint16_t port);
		virtual ~SocketMockable();

		MOCK_CONST_METHOD0 (port, uint16_t());
		uint16_t mock_port();

		MOCK_CONST_METHOD0 (status, ISocket::SocketStatus_n());
		ISocket::SocketStatus_n mock_status();

		MOCK_CONST_METHOD0 (address, std::string());
		virtual std::string mock_address() const;

		MOCK_METHOD1(bind, bool(uint16_t));
		virtual bool mock_bind(uint16_t port);

		MOCK_METHOD0 (listen, bool(void));
		virtual bool mock_listen();

		MOCK_METHOD0 (accepts, ISocket*(void));
		virtual ISocket* mock_accept();

		MOCK_METHOD2 (connect, bool(const std::string&, uint16_t));
		virtual bool mock_connect(const std::string& addr, uint16_t port);

		MOCK_METHOD2 (connect, bool(const std::string&, const std::string&));
		virtual bool mock_connect(const std::string& addr, const std::string& port);

		MOCK_METHOD2 (send, nSocketFrameStatus(const std::string&, int));
		virtual nSocketFrameStatus mock_send(const std::string& tx, int timeout = NO_WAIT);

		MOCK_METHOD4 (send, nSocketFrameStatus(const std::string&, const std::string&, uint16_t, int));
		virtual nSocketFrameStatus mock_send(const std::string& tx, const std::string& dest, uint16_t port, int timeout = NO_WAIT);

		MOCK_METHOD2 (receive, nSocketFrameStatus(std::string&, int));
		virtual nSocketFrameStatus mock_receive(std::string& rx, int timeout = DEFAULT_TIMEOUT);

		MOCK_METHOD3 (receive, nSocketFrameStatus(std::string&, std::string&, int));
		virtual nSocketFrameStatus mock_receive(std::string& rx, std::string& addr, int timeout = DEFAULT_TIMEOUT);

		MOCK_METHOD0 (close, bool(void));
		virtual bool mock_close();

		MOCK_METHOD0 (enableBroadcast, bool(void));
		virtual bool mock_enableBroadcast();

	protected:
		MOCK_METHOD0 (init, bool(void));
		virtual bool mock_init();
};



#endif //SOCKET_MOCK_H
