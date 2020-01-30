#ifndef TIJ_PRINTER_CONTROLLER_H
#define TIJ_PRINTER_CONTROLLER_H

#include "printercontroller.h"
#include "mprotocol/mcommandsfactory.h"

namespace Macsa {
	class TIJPrinterController : public PrinterController {
		public:
			TIJPrinterController(const std::string& id, const std::string& address);
			virtual ~TIJPrinterController();
			virtual Printers::Printer* printer() override {return &_printer;}


			//Live
			Printers::ErrorCode getLive();
			//Status
			Printers::ErrorCode updateStatus();
			std::string printerStatus();
			//Config
			bool getConfig();
			bool setDateTime(const std::time_t& dt);
			//Files
			std::vector<std::string> getFonts();
			std::vector<std::string> getMessages();
			std::vector<std::string> getImages();
			std::vector<std::string> getAllFiles();
			bool getErrorsList();

		protected:
			virtual bool send(MProtocol::MCommand *cmd, Printers::ErrorCode& err);

		private:
			Printers::TIJPrinter _printer;
			MProtocol::MCommandsFactory _factory;
	};
}


#endif //TIJ_PRINTER_CONTROLLER_H

