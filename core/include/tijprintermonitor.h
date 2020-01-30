#ifndef TIJ_PRINTER_MONITOR_H
#define TIJ_PRINTER_MONITOR_H

#include <string>
#include "printermonitor.h"
#include "tijprintercontroller.h"

namespace Macsa {
	class TijPrinterMonitor : public PrinterMonitor{
		public:
			TijPrinterMonitor(const std::string &id, const std::string &address);
			~TijPrinterMonitor();

		protected:
			virtual void run();

		private:

	};
}


#endif

