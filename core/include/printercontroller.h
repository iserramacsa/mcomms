#ifndef PRINTER_CONTROLLER_H
#define PRINTER_CONTROLLER_H

#include <string>

#include "network/isocket.h"
#include "network/networknode.h"
#include "printer/printer.h"
#include "mprotocol/mcommands.h"

namespace Macsa {
	class PrinterController : public Network::NetworkNode {
		public:
			PrinterController(const std::string& id, const std::string& address, uint16_t port);
			~PrinterController();
			virtual bool connect();
			virtual bool disconnect();
			virtual bool reconnect();

			virtual Printers::Printer* printer() = 0;

		protected:
			virtual bool send(MProtocol::MCommand *cmd) = 0;

		private:
			uint16_t _printerPort;
	};
}

#endif //PRINTER_CONTROLLER_H
