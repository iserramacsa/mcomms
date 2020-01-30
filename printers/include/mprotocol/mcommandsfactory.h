#ifndef MACSA_MPROTOCOL_COMMANDSFACTORY_H
#define MACSA_MPROTOCOL_COMMANDSFACTORY_H

#include <map>
#include "mcommands.h"
#include "printer/printer.h"

namespace Macsa {
	namespace MProtocol {
		class MCommandsFactory
		{
			public:
				MCommandsFactory(Printers::TIJPrinter& printer);
				~MCommandsFactory();

				bool parse(const std::string &frame, Printers::ErrorCode &error);

//				//SERVER
//				std::string getResponse(); //TODO: Move to commandsHandler (server)

				//Live
				MCommand *getLiveCommand();
				//Status
				MCommand* getStatusCommand();
				//Config
				MCommand* getConfigCommand();
				MCommand* setDateTimeCommand();
				//Files
				MCommand* getFontsCommand();
				MCommand* getMessagesCommand();
				MCommand* getImagesCommand();
				MCommand* getAllFilesCommand();

				MCommand* getErrorsList();

				inline uint32_t nextId() {
					if(++_requestId < 0) { _requestId = 0; }
					return static_cast<uint32_t>(_requestId);
				}

			private:
				tinyxml2::XMLDocument _doc;
				Printers::TIJPrinter& _printer;
				int32_t _requestId;

				MCommand* getCommand(tinyxml2::XMLElement* wind) const; //Refacotr
//				MCommand* getResponseCommand(tinyxml2::XMLElement* wind) const;
				inline bool isElement(const tinyxml2::XMLElement *wind, const std::string& name) const;
				inline bool isWindValid(tinyxml2::XMLElement* wind) const;

		};
	}
}

#endif // MCOMMANDSFACTORY_H
