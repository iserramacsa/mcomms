#ifndef MACSA_MCOMMS_TIJ_CONTROLLER_H
#define MACSA_MCOMMS_TIJ_CONTROLLER_H
#include "tij/datatypes.h"
#include "printercontroller.h"
#include "tijnotifier.h"
#include "mprotocol/mcommandsfactory.h"
#include <mutex>

namespace Macsa {
	namespace MComms {
		class TijController : public PrinterController, public TijNotifier
		{
			public:
				TijController(const std::string& id, const std::string& address);
				virtual Printers::Printer* printer() override {return &_printer;}

				//Live
				void getLive();
				bool isStatusChanged() const {return _liveFlags.statusChanged;}
				bool isConfigChanged() const {return _liveFlags.configChanged;}
				bool isFilesChanged() const {return _liveFlags.filesChanged;}
				bool isFontsChanged() const {return _liveFlags.fontsChanged;}
				bool isUserValuesChanged() const {return _liveFlags.userValueChanged;}
				bool isErrorsLogsChanged() const {return _liveFlags.errorsLogChanged;}
				bool isInError() const {return _liveFlags.isInError;}

				//Status
				bool updateStatus();
				bool updateErrorsList();

				//Config
				bool updateConfig();
				bool setDateTime(const std::time_t& dt);
				bool setEnabled(bool enabled);
				bool setAutoStart(bool enabled);
				bool setLowLevelOutput(bool enabled);
				bool setCartridgeBlocked(bool blocked);
				bool setPrintRotated(bool rotated);
				bool setUserMessage(const std::string& filepath);
				bool setBcdMode(const Printers::BCDMode& mode);
				//Files
				bool updateFilesList();
				bool updateFontsList();
				bool updateMessagesList();
				bool updateImagesList();
				bool updateFile(const std::string& filepath, bool rawMode = false);
				bool updateUserValues();

				std::vector<std::string> getDrives();
				std::vector<uint8_t> getFile(const std::string& filepath);

				inline std::vector<std::string> getFonts() { return getFiles(FONTS_FILTER); }
				inline std::vector<std::string> getFonts(const std::string &drive) { return getFiles(drive, FONTS_DIRECTORY);}

				inline std::vector<std::string> getMessages() { return getFiles(MESSAGES_FILTER); }
				inline std::vector<std::string> getMessages(const std::string &drive) { return getFiles(drive, MESSAGES_DIRECTORY);}

				inline std::vector<std::string> getImages() { return getFiles(IMAGES_FILTER); }
				inline std::vector<std::string> getImages(const std::string &drive) { return getFiles(drive, IMAGES_DIRECTORY);}

				inline std::vector<std::string> getAllFiles() { return getFiles(ALL_FILES_FILTER); }

			protected:
				using nFrameStatus=Network::ISocket::nSocketFrameStatus;
				MProtocol::MCommandsFactory _factory;
				MProtocol::LiveFlags _liveFlags;
				nFrameStatus _lastSentStatus;

				virtual bool send(XMLCommand *cmd) override;

			private:
				std::mutex _mutex;
				Printers::TijPrinter _printer;

				bool getBaseBoard(Printers::Board& board);
				bool changeBoardConfig(const Printers::Board& board);

				void checkCommand(const std::string& cmd, const std::map<std::string, std::string> &attributes);

				// void checkConnection(); // TODO
				std::vector<std::string> getFiles(const std::string &extension);
				std::vector<std::string> getFiles(const std::string &drive,const std::string &folder);

//				template<typename... Args>
//				bool sendCommand(std::function<MProtocol::MCommand*(MProtocol::MCommandsFactory*, const Args& ...)>& command, const Args& ...args);

		};
	}
}


#endif //MACSA_MCOMMS_TIJ_CONTROLLER_H

