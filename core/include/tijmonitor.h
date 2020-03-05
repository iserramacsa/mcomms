#ifndef MACSA_MCOMMS_TIJ_PRINTER_MONITOR_H
#define MACSA_MCOMMS_TIJ_PRINTER_MONITOR_H

#include <string>
#include <list>
#include <condition_variable>
#include "tijcontroller.h"
#include <atomic>
#include <thread>

namespace Macsa {
	namespace MComms{
		class TijMonitor : public TijController{
			public:
				TijMonitor(const std::string &id, const std::string &address);
				virtual ~TijMonitor() override;

				virtual bool connect() override;
				virtual bool disconnect() override;

				int maxReconnections() const;
				void setMaxReconnections(int maxReconnections);

			protected:
				virtual void run();
				virtual bool send(MProtocol::MCommand *cmd) override;
				virtual bool sendCmd(MProtocol::MCommand *cmd);

			private:
				int _reconnections;
				int _maxReconnections;
				std::atomic_bool _running;
				std::mutex _mLoop;
				std::mutex _mCommands;
				std::condition_variable _cv;
				std::thread _th;
				Printers::ErrorCode _lastError;
				std::list<MProtocol::MCommand*> _commands;

				void start();
				void stop();
		};
	}
}


#endif

