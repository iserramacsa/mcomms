#ifndef MCOMM_PRINTER_MANAGER_H
#define MCOMM_PRINTER_MANAGER_H

#include "network/network.h"
#include "tijprintercontroller.h"

namespace Macsa {
	class PrintersManager {
		public:
			PrintersManager();
			~PrintersManager();

			bool addTijPrinter(const std::string name, const std::string& address);
			bool connectTijPrinter(const std::string name);
			bool disconnectTijPrinter(const std::string name);
			TijPrinterController* getPrinter(const std::string name);


		private:
			Network::MNetwork _tcpNetwork;
	};
}

#endif
