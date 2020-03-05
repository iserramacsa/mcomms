#ifndef MACSA_MPROTOCOL_COMMANDSFACTORY_H
#define MACSA_MPROTOCOL_COMMANDSFACTORY_H

#include <map>
#include "mcommands.h"
#include "mlive.h"
#include "printer/printer.h"

namespace Macsa {
	namespace MProtocol {
		class MCommandsFactory
		{
			public:
				MCommandsFactory(Printers::TijPrinter& printer, LiveFlags& _liveFlags);
				~MCommandsFactory();

				bool parseResponse(const std::string &rx, MCommand *cmd);
				bool parseRequest(const std::string &frame, MCommand **cmd);

//				//SERVER
//				std::string getResponse(); //TODO: Move to commandsHandler (server)

				//Live
				MCommand *getLiveCommand();
				//Status
				MCommand* getStatusCommand();
				MCommand* getIOStatusCommand();
				MCommand* getCurrentErrors();

				//Config
				MCommand* getConfigCommand();
				MCommand* setDateTimeCommand(const time_t &dateTime);
				MCommand* setConfigBoard(const Printers::Board& board);

				//Files
				MCommand* getFontsCommand();
				MCommand* getMessagesCommand();
				MCommand* getImagesCommand();
				MCommand* getAllFilesCommand();
				MCommand* getFileContent(const std::string &filePath, bool rawMode = false);
				MCommand* getMsgUserValues(const std::string &filePath);
				MCommand* getMsgDataSources(const std::string &filePath);

				// Log
				MCommand* getErrorsList();

				inline uint32_t nextId() {
					if(++_requestId < 0) { _requestId = 0; }
					return static_cast<uint32_t>(_requestId);
				}

			private:
				tinyxml2::XMLDocument _doc;
				Printers::TijPrinter& _printer;
				LiveFlags& _liveFlags;
				int32_t _requestId;

				MCommand* getCommand(tinyxml2::XMLElement* eCmd); //Refactor required
//				MCommand* getResponseCommand(tinyxml2::XMLElement* wind) const;
				inline bool isElement(const tinyxml2::XMLElement *wind, const std::string& name) const;
				inline bool isWindValid(tinyxml2::XMLElement* wind) const;

		};
	}
}

#endif // MCOMMANDSFACTORY_H
