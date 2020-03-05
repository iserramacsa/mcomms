#ifndef MACSA_MCOMMS_CLIENT_MANAGER_H
#define MACSA_MCOMMS_CLIENT_MANAGER_H

#include <thread>
#include <atomic>
#include <mutex>

#include <condition_variable>
#include "network/network.h"
#include "clientHandler.h"
#include "tij/tijprinter.h"


namespace Macsa {
	using namespace Network;
	namespace MComms {
		class ClientManager : protected Network::MNetwork
		{
			public:
				ClientManager(Printers::TijPrinter& printer);
				~ClientManager();
				bool initTcpServer(uint16_t port);
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
	}
}


#endif //MACSA_MCOMMS_CLIENT_MANAGER_H
