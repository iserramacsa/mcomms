#ifndef MACSA_JETPROTOCOL_COMMANDSFACTORY_H
#define MACSA_JETPROTOCOL_COMMANDSFACTORY_H

#include <map>
#include "jetcommands.h"
#include "printer/printer.h"

namespace Macsa {
	namespace JetProtocol {
		class JetCommandsFactory
		{
			public:
				JetCommandsFactory(Printers::JetPrinter& printer);
				~JetCommandsFactory();

				bool parseResponse(const std::string &rx, JetCommand *cmd);
				bool parseRequest(const std::string &frame, JetCommand **cmd);

				//Status
//				JetCommand* getStatusCommand();
//				JetCommand* getPrinterLogs();

				//Config
//				JetCommand* getConfigCommand();
//				JetCommand* setDateTimeCommand(const time_t &dateTime);
//				JetCommand* setConfigBoard(const Printers::Board& board);
//				JetCommand* setCurrentMessage(const std::string& filepath);

				//Files
//				JetCommand* getFontsCommand();
//				JetCommand* getMessagesCommand();
//				JetCommand* getAllFilesCommand();
//				JetCommand* getNisxFileContent(const std::string &filePath);
//				JetCommand* getMsgUserValues(const std::string &filePath);
//				JetCommand* getMsgDataSources(const std::string &filePath);

			private:
				tinyxml2::XMLDocument _doc;
				Printers::JetPrinter& _printer;

				JetCommand* getCommand(tinyxml2::XMLElement* eCmd); //Refactor required
//				MCommand* getResponseCommand(tinyxml2::XMLElement* wind) const;
				inline bool isElement(const tinyxml2::XMLElement *wind, const std::string& name) const;
				inline bool isWindValid(tinyxml2::XMLElement* wind) const;

		};
	}
}

#endif // MACSA_JETPROTOCOL_COMMANDSFACTORY_H
