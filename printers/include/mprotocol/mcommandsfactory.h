#ifndef MCOMMANDSFACTORY_H
#define MCOMMANDSFACTORY_H

#include <map>
#include "mcommands.h"
#include "printer/printer.h"

namespace Macsa {
	namespace MProtocol {
		class MCommandsFactory
		{
			public:
				MCommandsFactory(Printers::Printer& printer);
				~MCommandsFactory();
//				bool parse(const std::string &frame);
//				bool parse(const std::string &frame, MCommand* handler);
//				//SERVER
//				std::string getResponse(); //TODO: Refactorize
//				//CLIENT
//				//Live
//				MCommand *getLiveCommand();		//TODO: Refactorize
//				//Status
//				MCommand* getStatusCommand();	//TODO: Refactorize
//				//Config
//				MCommand* getConfigCommand();	//TODO: Refactorize
//				//Files
//				MCommand* getFontsCommand();	//TODO: Refactorize
//				MCommand* getMessagesCommand(); //TODO: Refactorize
//				MCommand* getImagesCommand();	//TODO: Refactorize
//				MCommand* getAllFilesCommand(); //TODO: Refactorize
	//			MCommand* getErrorsList();		//TODO: Refactorize
			private:
				tinyxml2::XMLDocument _doc;
				Printers::Printer& _printer;
//				std::string  getCommandResponse(tinyxml2::XMLElement* wind);
				inline bool isElement(const tinyxml2::XMLElement *wind, const std::string& name) const;
				inline bool isWindValid(tinyxml2::XMLElement* wind);
		};
	}
}

#endif // MCOMMANDSFACTORY_H
