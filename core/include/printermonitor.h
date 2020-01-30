#ifndef PRINTER_MONITOR_H
#define PRINTER_MONITOR_H

#include <string>
#include "tijprintercontroller.h"

namespace Macsa {
	class PrinterMonitor : public PrinterController {
		public:
			PrinterMonitor(const std::string &id, const std::string &address);
			~PrinterMonitor();

		protected:
			virtual void run() = 0;

		private:

	};
}

#endif //PRINTER_MONITOR_H
