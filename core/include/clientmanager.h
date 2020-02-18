#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "network/network.h"
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "clientHandler.h"
#include "tij/tijprinter.h"

#if SSIGNALS
	#include "SimpleSignal.h"
#endif

using namespace Macsa;
using namespace Macsa::Network;

class AbstractSocket;
class ClientManager : protected Network::MNetwork
{
	public:
		ClientManager(Printers::TIJPrinter& printer);
		~ClientManager();
		bool initServer(uint16_t port);
		void run(bool detached = true);
		void stop();

#if SSIGNALS
	public:
		void connect (std::function<void(const std::string&, const std::string&)>& slot)
		{
			clientConnected.connect(slot);
		}

	private:
		Simple::Signal<void(const std::string& /*name*/, const std::string& /*address*/)> clientConnected;
#endif

	private:
		std::thread _svrLoop;
		std::atomic_bool _running;
		std::mutex _mtx;
		std::condition_variable _cv;
		uint16_t _svrPort;

		Printers::TIJPrinter& _printer;
		std::vector<ClientHandler*> _handlers;

		void serverMainLoop();
		Network::AbstractSocket *acceptConnection();

};

#endif //CLIENT_MANAGER_H
