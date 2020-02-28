#ifndef MCOMM_PRINTER_MANAGER_H
#define MCOMM_PRINTER_MANAGER_H

#include "network/network.h"
#include "tijprintermonitor.h"

namespace Macsa {
	class PrintersManager : protected Network::MNetwork{

		public:
			PrintersManager();
			~PrintersManager();

			virtual unsigned int size() const;

			bool addTijPrinter(const std::string name, const std::string& address, bool monitorize = false);
			bool removeTijPrinter(const std::string name);
			bool connectPrinter(const std::string name);
			bool disconnectPrinter(const std::string name);
			void sendDiscover();

			PrinterController* getPrinter(const std::string name);
			PrinterController* getPrinter(const uint index);

	};
}

#endif
