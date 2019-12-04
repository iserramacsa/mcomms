#ifndef TIJ_PRINTER_CONTROLLER
#define TIJ_PRINTER_CONTROLLER

#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <list>

#include "network/networknode.h"
#include "tij/tijprinter.h"
#include "mprotocol/mcommands.h"
#include "mprotocol/mcommandsfactory.h"

namespace Macsa {
	class TijPrinterController : protected Network::NetworkNode {
		public:
			TijPrinterController(const std::string& id, const std::string& address);
			~TijPrinterController();
			bool connect();
			bool disconnect();

			time_t getDateTime();
			bool setDateTime(std::tm dt);


		protected:
			virtual bool send(MProtocol::MCommand *cmd);

		private:
			Printers::TIJPrinter _printer;
			std::atomic_bool _running;
			std::list<MProtocol::MCommand*> _commands;
			MProtocol::MCommandsFactory _factory;

			using itCommand = std::list<MProtocol::MCommand*>::iterator;
	};
}


#endif

