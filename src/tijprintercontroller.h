#ifndef TIJ_PRINTER_CONTROLLER
#define TIJ_PRINTER_CONTROLLER

#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include "network/networknode.h"
#include "printer/printer.h"

namespace Macsa {

	class TijPrinterController : protected Network::NetworkNode{
		public:
			TijPrinterController(const std::string& id, const std::string& address);
			~TijPrinterController();
			bool connect();
			bool disconnect();

		protected:
			virtual void run();

		private:
			Printers::Printer _printer;
			std::atomic_bool _running;
	};
}


#endif

