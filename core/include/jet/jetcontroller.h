#ifndef MACSA_MCOMMS_JET_CONTROLLER_H
#define MACSA_MCOMMS_JET_CONTROLLER_H
#include "jet/datatypes.h"
#include "printercontroller.h"
#include "jetnotifier.h"
#include "jetprotocol/jetcommandsfactory.h"
#include <mutex>

namespace Macsa {
	namespace MComms {
		class JetController : public PrinterController, public JetNotifier
		{
			public:
				JetController(const std::string& id, const std::string& address);
				virtual ~JetController() override;
				virtual Printers::Printer* printer() override {return &_printer;}

				void initPrinter();

				//Status
				bool getCounters();
				bool getSSCC();
				bool getStatus();
				bool getDateTime();
				bool getPrinterLogs(time_t from = 0, time_t to = time(nullptr), Printers::JetLogType type = Printers::nJetLogType::LOG_TYPE_ALL);
				bool getPause();
				bool setCounters(std::map<unsigned int, unsigned int>& counters);
				bool resetCounters();

				//Files
				bool getUSBMessages();
				bool getFiles();
				bool getVersions();
				bool getFonts();

				//Messages
				bool setCurrentMessage(unsigned int messageNumber);
				bool sendMessage(const Printers::Message& message, const std::vector<char> &content, bool raw);
				bool resetMessagesGroup();
				bool getMessagesGroup(const std::string& group);
				bool createMessageGroup(const std::string& group);
				bool sendMessageGroup(const std::string& group, const Printers::Message &message, const std::vector<char> &content, bool raw);
				bool deleteMessageGroup(const std::string& group);
				bool setMessageVariable(unsigned int filenum, const std::string& variable, const std::string& value);
				bool setMessageVariables(unsigned int filenum, const std::map<std::string, std::string>& values);
				bool getUserInputs(unsigned int filenum, const std::string &group = "");
				bool setUserInputs(unsigned int filenum, const std::map<std::string, std::string>& uiFields, const std::string& group = "");

				//Config
				bool setPause(bool pause);
				bool incrementSSCC();
				bool setDateTime(const time_t &datetime);
				bool setOutput(const Printers::JetIO& output);
				bool setPrintDirection(Printers::PrintDirection dir);
				bool setPrintBitmapInverted(bool inverted);
				bool setPrintSpeed(unsigned int speed);
				bool setPrintDelay(unsigned int delay);
				bool setHorizontalResolution(unsigned int resolution);
				bool setConfig(Printers::JetPrinter &printer);

				bool getPrintSpeed();
				bool getPrintDelay();
				bool getHorizontalResolution();
				bool getConfig();
				bool resetInkAlarm();

				//Nisx Commands
				bool getNisXMessage(unsigned int msgNum);
				bool setNisXElement(const std::string& filename,  const std::string& content);

			protected:
				Printers::JetPrinter _printer;
				using nFrameStatus=Network::ISocket::nSocketFrameStatus;
				JetProtocol::JetCommandsFactory _factory;
				nFrameStatus _lastSentStatus;

				virtual bool send(XMLCommand *cmd);
				virtual void checkCommand(const std::string& command, const std::map<std::string, std::string> &attributes);
				virtual void updateMessageGroups();

			private:
				std::mutex _mutex;
		};
	}
}


#endif //MACSA_MCOMMS_JET_CONTROLLER_H

