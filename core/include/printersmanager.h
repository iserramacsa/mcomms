#ifndef MCOMM_PRINTER_MANAGER_H
#define MCOMM_PRINTER_MANAGER_H

#include "network/network.h"
#include "tijprintermonitor.h"

namespace Macsa {
	class PrintersManager {

		public:
			PrintersManager();
			~PrintersManager();

			bool addTijPrinter(const std::string name, const std::string& address, bool monitorize = false);
			bool removeTijPrinter(const std::string name);
			bool connectPrinter(const std::string name);
			bool disconnectPrinter(const std::string name);
			//			void discoverPrinters();

			PrinterController* getPrinter(const std::string name);
			PrinterController* getPrinter(const int index);

			unsigned int size() const;

		private:
			Network::MNetwork _printersNetwork;
	};
}

#endif
