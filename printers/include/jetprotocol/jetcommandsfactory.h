#ifndef MACSA_JETPROTOCOL_COMMANDSFACTORY_H
#define MACSA_JETPROTOCOL_COMMANDSFACTORY_H

#include <map>
#include "jetcommand.h"
#include "printer/printer.h"

namespace Macsa {
	namespace JetProtocol {
		class JetCommandsFactory
		{
			public:
				JetCommandsFactory(Printers::JetPrinter& printer);
				virtual ~JetCommandsFactory();

				virtual bool parseResponse(const std::string& rx, JetCommand *cmd);
				virtual bool parseRequest(const std::string& frame, JetCommand **cmd);

				//Status
				JetCommand* getCounters();
				JetCommand* getSSCC();
				JetCommand* getStatus();
				JetCommand* getDateTime();
				JetCommand* getPrinterLogs(time_t from = 0, time_t to = time(nullptr), Printers::JetLogType type = Printers::nJetLogType::LOG_TYPE_ALL);
				JetCommand* getPause();
				JetCommand* setCounters(std::map<unsigned int, unsigned int> counters);
				JetCommand* resetCounters();

				//Files
				JetCommand* getUSBMessages();
				JetCommand* getFiles();
				JetCommand* getVersions();
				JetCommand* getFonts();

				//Messages
				JetCommand* setCurrentMessage(unsigned int messageNumber);
				JetCommand* sendMessage(const Printers::Message& message, const std::vector<char>& content, bool raw);
				JetCommand* resetMessagesGroup();
				JetCommand* getMessagesGroup(const std::string& group);
				JetCommand* createMessageGroup(const std::string& group);
				JetCommand* sendMessageGroup(const std::string& group, const Printers::Message& message, const std::vector<char>& content, bool raw);
				JetCommand* deleteMessageGroup(const std::string& group);
				JetCommand* setMessageVariable(unsigned int filenum, const std::string& variable, const std::string& value);
				JetCommand* setMessageVariables(unsigned int filenum, const std::map<std::string, std::string>& values);
				JetCommand* getUserInputs(unsigned int filenum, const std::string& group = "");
				JetCommand* setUserInputs(unsigned int filenum, const std::map<std::string, std::string>& uiFields, const std::string& group = "");

				//Config
				JetCommand* setPause(bool pause);
				JetCommand* incrementSSCC();
				JetCommand* setDateTime(const time_t& datetime);
				JetCommand* setOutput(const Printers::JetIO& output);
				JetCommand* setPrintDirection(Printers::PrintDirection dir);
				JetCommand* setPrintBitmapInverted(bool inverted);
				JetCommand* setPrintheadEnabled(Printers::PHEnableMode mode);
				JetCommand* setPrintSpeed(unsigned int speed);
				JetCommand* setPrintDelay(unsigned int delay);
				JetCommand* setHorizontalResolution(unsigned int resolution);
				JetCommand* setConfig(Printers::JetPrinter& printer);

				JetCommand* getPrintSpeed();
				JetCommand* getPrintDelay();
				JetCommand* getHorizontalResolution();
				JetCommand* getConfig();
				JetCommand* resetInkAlarm();

				//Nisx Commands
				JetCommand* getNisXMessage(unsigned int msgNum);
				JetCommand* setNisXElement(const std::string& filename = "",  const std::string& content = "");


			private:
				tinyxml2::XMLDocument _doc;
				Printers::JetPrinter& _printer;

				JetCommand* getCommand(tinyxml2::XMLElement* eCmd);

		};
	}
}

#endif // MACSA_JETPROTOCOL_COMMANDSFACTORY_H
