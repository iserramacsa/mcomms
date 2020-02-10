#ifndef TIJ_PRINTER_CONTROLLER_H
#define TIJ_PRINTER_CONTROLLER_H

#include "printercontroller.h"
#include "mprotocol/mcommandsfactory.h"

namespace Macsa {
	class TIJPrinterController : public PrinterController
	{
		public:
			enum class TIJPrinterStatus
			{
				DISCONNECTED = -1,
				STOPPED,
				WARNING,
				RUNNING,
				PRINTING,
			};

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
			TIJPrinterStatus printerStatus();

			Printers::ErrorCode updateErrorsList();
			//Config
			Printers::ErrorCode updateConfig();
			Printers::ErrorCode setDateTime(const std::time_t& dt);
			Printers::ErrorCode setEnabled(bool enabled);
			//Files
			Printers::ErrorCode updateFiles();
			Printers::ErrorCode updateFonts();
			Printers::ErrorCode updateMessages();
			Printers::ErrorCode updateImages();
			Printers::ErrorCode updateFile(const std::string& filepath, bool rawMode = false);

			std::vector<std::string> getDrives();
			std::vector<uint8_t> getFile(const std::string& filepath);

			inline std::vector<std::string> getFonts() { return getFiles(FONTS_FILTER); }
			inline std::vector<std::string> getFonts(const std::string &drive) { return getFiles(drive, FONTS_FOLDER);}

			inline std::vector<std::string> getMessages() { return getFiles(MESSAGES_FILTER); }
			inline std::vector<std::string> getMessages(const std::string &drive) { return getFiles(drive, MESSAGES_FOLDER);}

			inline std::vector<std::string> getImages() { return getFiles(IMAGES_FILTER); }
			inline std::vector<std::string> getImages(const std::string &drive) { return getFiles(drive, IMAGES_FOLDER);}

			inline std::vector<std::string> getAllFiles() { return getFiles(ALL_FILES_FILTER); }

		protected:
			virtual bool send(MProtocol::MCommand *cmd, Printers::ErrorCode& err);

		private:
			MProtocol::LiveFlags _liveFlags;
			Printers::TIJPrinter _printer;
			MProtocol::MCommandsFactory _factory;

			void checkConnection();
			std::vector<std::string> getFiles(const std::string &extension);
			std::vector<std::string> getFiles(const std::string &drive,const std::string &folder);
			
	};
}


#endif //TIJ_PRINTER_CONTROLLER_H

