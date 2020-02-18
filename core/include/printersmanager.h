#ifndef MCOMM_PRINTER_MANAGER_H
#define MCOMM_PRINTER_MANAGER_H

#include "network/network.h"
#include "tijprintercontroller.h"

#ifdef SSIGNALS
#include "SimpleSignal.h"
#endif

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
#if SSIGNALS
		public:
			void onPrinterConnected(std::function<void(const std::string&, const std::string&)>& slot)
			{
				printerConnected.connect(slot);
			}

		private:
			Simple::Signal<void(const std::string& /*name*/, const std::string& /*address*/)> printerConnected;
			Simple::Signal<void(const std::string& /*name*/)> printerDisconnected;
#endif


		private:
			Network::MNetwork _tcpNetwork;
	};
}

#endif
