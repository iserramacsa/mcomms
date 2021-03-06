#ifndef MACSA_MCOMMS_PRINTER_MANAGER_H
#define MACSA_MCOMMS_PRINTER_MANAGER_H

#include "network/network.h"
#include "tij/tijmonitor.h"
#include "jet/jetmonitor.h"

#define DEFAULT_DISCOVER_TIMEOUT	5

namespace Macsa {
	namespace MComms {
		class PrintersManager : public Network::MNetwork{

			public:
				PrintersManager();
				~PrintersManager();

				virtual unsigned int size() const;


				bool addTijPrinter(const std::string name, const std::string& address, bool monitorize = false);
				bool addJetPrinter(const std::string name, const std::string& address, bool monitorize = false);

				bool removePrinter(const std::string name);
				bool connectPrinter(const std::string name);
				bool disconnectPrinter(const std::string name);
				void sendDiscover(int timeout = DEFAULT_DISCOVER_TIMEOUT);
				void clear();

				PrinterController* getPrinter(const std::string name);
				PrinterController* getPrinter(const uint index);

			private:
				bool runDiscoverServer();
				void sendDiscoverFrames(Network::ISocket *server, int timeout);
				void receiveDiscoverFrames(std::atomic_bool& condition);
		};
	}
}

#endif //MACSA_MCOMM_PRINTER_MANAGER_H
