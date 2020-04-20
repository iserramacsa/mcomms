#ifndef MACSA_MCOMMS_JET_PRINTER_MONITOR_H
#define MACSA_MCOMMS_JET_PRINTER_MONITOR_H

#include <string>
#include <list>
#include <condition_variable>
#include "jetcontroller.h"
#include <atomic>
#include <thread>

namespace Macsa {
	namespace MComms{
		class JetMonitor : public JetController{
			public:
				JetMonitor(const std::string &id, const std::string &address);
				virtual ~JetMonitor() override;

				virtual bool connect() override;
				virtual bool disconnect() override;

				inline int maxReconnections() const {return _maxReconnections;}
				inline void setMaxReconnections(int maxReconnections) {_maxReconnections = maxReconnections;}

			protected:
				virtual void run();
				virtual bool send(XMLCommand *cmd) override;
				virtual bool sendCmd(JetProtocol::JetCommand *cmd);
				virtual void checkCommand(const std::string& command, const std::map<std::string, std::string> &attributes);
				virtual void updateMessageGroups();

			private:
				int _reconnections;
				int _maxReconnections;
				std::atomic_bool _running;
				std::mutex _mLoop;
				std::mutex _mCommands;
				std::condition_variable _cv;
				std::thread _th;
//				Printers::ErrorCode _lastError;
				std::list<JetProtocol::JetCommand*> _commands;

				void start();
				void stop();
		};
	}
}


#endif

