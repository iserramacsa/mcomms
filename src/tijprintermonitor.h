#ifndef TIJ_PRINTER_MONITOR
#define TIJ_PRINTER_MONITOR

#include <string>
#include "tijprintercontroller.h"

namespace Macsa {
	class TijPrinterMonitor : public TijPrinterController{
		public:
			TijPrinterMonitor(const std::string &id, const std::string &address);
			~TijPrinterMonitor();

		protected:
			virtual void run();

		private:

	};
}


#endif

