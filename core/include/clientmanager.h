#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "network/network.h"
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

using namespace Macsa;

class ClientManager : public Network::MNetwork
{
	public:
		ClientManager();
		~ClientManager();
		bool initServer(uint16_t port);
		void run(bool detached);

	private:
		Network::ISocket *_server;
		std::thread _mainLoop;
		std::atomic_bool _running;
		std::mutex _mtx;
		std::condition_variable _cv;

		void serverMainLoop();
		bool acceptConnection();

};

#endif //CLIENT_MANAGER_H
