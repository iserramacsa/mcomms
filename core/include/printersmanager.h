#ifndef MCOMM_PRINTER_MANAGER_H
#define MCOMM_PRINTER_MANAGER_H

#include "network/network.h"
#include "tijprintercontroller.h"

#include <signals.hpp>

namespace Macsa {
	class PrintersManager {
		private:
			typedef Signal<std::string> AddedPrinterSignal;

		public:
			typedef AddedPrinterSignal::Callback   AddedPrinterCallback;
			typedef AddedPrinterSignal::Connection AddedPrinterConnection;
			typedef AddedPrinterSignal::ScopedConnection AddedPrinterScopedConnection;

		public:
			PrintersManager();
			~PrintersManager();

			bool addTijPrinter(const std::string name, const std::string& address);
			bool connectPrinter(const std::string name);
			bool disconnectPrinter(const std::string name);

			TijPrinterController* getPrinter(const std::string name);
			TijPrinterController* getPrinter(const int index);

			unsigned int size() const;

			AddedPrinterConnection connect(const AddedPrinterCallback& callback) {
				_printerAddedEvent.connect(callback);
			}


		private:
			Network::MNetwork _tcpNetwork;
			AddedPrinterSignal _printerAddedEvent;
	};
}

#endif
