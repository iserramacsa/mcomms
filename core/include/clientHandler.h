#ifndef MCOMM_CLIENT_HANDLER_H
#define MCOMM_CLIENT_HANDLER_H

#include "mprotocol/mcommandsfactory.h"
#include "tij/tijprinter.h"
#include "network/isocket.h"
#include <thread>
#include <atomic>

using namespace Macsa;

class ClientHandler
{
	public:
		ClientHandler(Printers::TijPrinter& printer, Macsa::Network::ISocket *socket, uint16_t port);
		~ClientHandler();
		bool start();
		bool stop();

	private:
		uint16_t _svrPort;
		std::atomic_bool _running;
		Printers::TijPrinter& _printer;
		Network::ISocket* _socket;
		MProtocol::LiveFlags _liveFlags;
		MProtocol::MCommandsFactory _factory;
		std::thread _svrThread;


		void serverSocketLoop();

};


#endif //MCOMM_CLIENT_HANDLER_H
