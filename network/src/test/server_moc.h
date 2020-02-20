#ifndef SERVER_MOCK_H
#define SERVER_MOCK_H

#include <gmock/gmock.h>
#include "abstractsocket.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include <functional>
#include <atomic>

using namespace Macsa::Network;

#define SERVER_MOCKABLE_ADDR "127.0.0.1"

class ServerMockable
{
	public:
		ServerMockable();
		virtual ~ServerMockable();
		virtual bool init(ISocket::SocketType_n type, uint16_t port, bool bcast = false);
		virtual void run(std::function<void (AbstractSocket*)> onNewConnection);
		virtual void runTcpServer();
		virtual void runUdpServer();
		virtual void stop();

	protected:
		std::atomic_bool _running;
		std::thread _serverThread;
		std::mutex _mutex;
		std::condition_variable _cv;

		AbstractSocket* _server;
		uint16_t _udpPort;

		virtual void serverMainLoop(std::function<void (AbstractSocket*)> onNewConnection);
		virtual void echoSocketLoop(AbstractSocket*);
};



#endif //SOCKET_MOCK_H
