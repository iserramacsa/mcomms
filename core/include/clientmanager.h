#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "network/network.h"
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "clientHandler.h"
#include "tij/tijprinter.h"

using namespace Macsa;
using namespace Macsa::Network;

class AbstractSocket;
class ClientManager : protected Network::MNetwork
{
	public:
		ClientManager(Printers::TijPrinter& printer);
		~ClientManager();
		bool initServer(uint16_t port);
		void run(bool detached = true);
		void stop();

	private:
		std::thread _svrLoop;
		std::atomic_bool _running;
		std::mutex _mtx;
		std::condition_variable _cv;
		uint16_t _svrPort;

		Printers::TijPrinter& _printer;
		std::vector<ClientHandler*> _handlers;

		void serverMainLoop();
		ISocket *acceptConnection();

};

#endif //CLIENT_MANAGER_H
