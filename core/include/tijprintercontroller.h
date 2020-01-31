#ifndef TIJ_PRINTER_CONTROLLER_H
#define TIJ_PRINTER_CONTROLLER_H

#include "printercontroller.h"
#include "mprotocol/mcommandsfactory.h"

namespace Macsa {
	class TIJPrinterController : public PrinterController {
		public:
			TIJPrinterController(const std::string& id, const std::string& address);
			virtual Printers::Printer* printer() override {return &_printer;}

			//Live
			Printers::ErrorCode getLive();
			bool statusChanged() const {return _liveFlags.statusChanged;}
			bool configChanged() const {return _liveFlags.configChanged;}
			bool filesChanged() const {return _liveFlags.filesChanged;}
			bool fontsChanged() const {return _liveFlags.fontsChanged;}
			bool userValuesChanged() const {return _liveFlags.userValueChanged;}
			bool errorsLogsChanged() const {return _liveFlags.errorsLogChanged;}
			bool isInError() const {return _liveFlags.isInError;}

			//Status
			Printers::ErrorCode updateStatus();
			std::string printerStatus();
			//Config
			Printers::ErrorCode updateConfig();
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
			MProtocol::LiveFlags _liveFlags;
			Printers::TIJPrinter _printer;
			MProtocol::MCommandsFactory _factory;

			void checkConnection();
			
	};
}


#endif //TIJ_PRINTER_CONTROLLER_H

