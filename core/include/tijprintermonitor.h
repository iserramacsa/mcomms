#ifndef TIJ_PRINTER_MONITOR_H
#define TIJ_PRINTER_MONITOR_H

#include <string>
#include <list>
#include <condition_variable>
#include "printermonitor.h"
#include "tijprintercontroller.h"
#include <atomic>
#include <thread>

namespace Macsa {
	class TijPrinterMonitor : public TijController{
		public:
			TijPrinterMonitor(const std::string &id, const std::string &address);
			virtual ~TijPrinterMonitor() override;

		protected:
			virtual void run();
			virtual bool send(MProtocol::MCommand *cmd, Printers::ErrorCode& err) override;

		private:
			std::atomic_bool _running;
			std::mutex _mutex;
			std::condition_variable _cv;
			std::thread _th;
			Printers::ErrorCode _lastError;
			std::list<MProtocol::MCommand*> _commands;

			void stop();
	};
}


#endif

