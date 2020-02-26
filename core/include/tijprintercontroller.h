#ifndef TIJ_PRINTER_CONTROLLER_H
#define TIJ_PRINTER_CONTROLLER_H
#include "printer/datatypes.h"
#include "printercontroller.h"
#include "mprotocol/mcommandsfactory.h"
#include <mutex>

namespace Macsa {
	class TijObserver;
	class TijController : public PrinterController
	{
		public:
			enum class TijPrinterStatus
			{
				DISCONNECTED = -1,
				STOPPED,
				WARNING,
				RUNNING,
				PRINTING,
			};

		public:
			TijController(const std::string& id, const std::string& address);
			virtual ~TijController();
			virtual Printers::Printer* printer() override {return &_printer;}

			//Live
			Printers::ErrorCode getLive();
			bool isStatusChanged() const {return _liveFlags.statusChanged;}
			bool isConfigChanged() const {return _liveFlags.configChanged;}
			bool isFilesChanged() const {return _liveFlags.filesChanged;}
			bool isFontsChanged() const {return _liveFlags.fontsChanged;}
			bool isUserValuesChanged() const {return _liveFlags.userValueChanged;}
			bool isErrorsLogsChanged() const {return _liveFlags.errorsLogChanged;}
			bool isInError() const {return _liveFlags.isInError;}

			//Status
			Printers::ErrorCode updateStatus();
			TijPrinterStatus printerStatus();

			Printers::ErrorCode updateErrorsList();
			//Config
			Printers::ErrorCode updateConfig();
			Printers::ErrorCode setDateTime(const std::time_t& dt);
			Printers::ErrorCode setEnabled(bool enabled);
			Printers::ErrorCode setAutoStart(bool enabled);
			Printers::ErrorCode setLowLevelOutput(bool enabled);
			Printers::ErrorCode setCartridgeBlocked(bool blocked);
			Printers::ErrorCode setPrintRotated(bool rotated);

			//Files
			Printers::ErrorCode updateFilesList();
			Printers::ErrorCode updateFontsList();
			Printers::ErrorCode updateMessagesList();
			Printers::ErrorCode updateImagesList();
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

			virtual void attach(TijObserver* tijObserver);
			virtual void detach(TijObserver* tijObserver);

		protected:
			bool _deleteAfterSend;
			MProtocol::MCommandsFactory _factory;
			MProtocol::LiveFlags _liveFlags;

			virtual bool send(MProtocol::MCommand *cmd, Printers::ErrorCode& err) override;

			virtual void notifyStatusChanged();
			virtual void notifyIOStatusChanged();
			virtual void notifyConfigChanged();
			virtual void notifyFilesListChanged();
			virtual void notifyFontsChanged();
			virtual void notifyUserValuesChanged();
			virtual void notifyErrorsLogsChanged();
			virtual void notifyFileChanged(const std::string &unit, const std::string &filepath);
			void notifyDestruction();

			template<typename... Args>
			void notifyToObservers(std::function<void(TijObserver*, const Args& ... )>&,  const Args&... arg);

		private:
			std::mutex _mutex;
			Printers::TijPrinter _printer;
			std::vector<TijObserver*> _tijObservers;

			bool getBaseBoard(Printers::Board& board);
			Printers::ErrorCode changeBoardConfig(const Printers::Board& board);

			void checkCommand(const std::string& cmd, const std::map<std::string, std::string> &attributes);

			std::vector<TijObserver*>::iterator observer(const unsigned int id);
//			void checkConnection(); // TODO
			std::vector<std::string> getFiles(const std::string &extension);
			std::vector<std::string> getFiles(const std::string &drive,const std::string &folder);
			
	};
}


#endif //TIJ_PRINTER_CONTROLLER_H

