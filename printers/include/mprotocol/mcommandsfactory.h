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
				bool parse(const std::string &frame);
				bool parse(const std::string &frame, MCommandBase* handler);
	#if defined (MSERVER)
				std::string getResponse();
	#elif defined (MCLIENT)
				//Live
				MCommandBase* getLiveCommand();

				//Status
				MCommandBase* getStatusCommand();

				//Config
				MCommandBase* getConfigCommand();

				//Files
				MCommandBase* getFontsCommand();
				MCommandBase* getMessagesCommand();
				MCommandBase* getImagesCommand();
				MCommandBase* getAllFilesCommand();
	//			MCommandBase* getErrorsList();
	#endif
			private:
				tinyxml2::XMLDocument _doc;
				Printers::Printer& _printer;
				std::string  getCommandResponse(tinyxml2::XMLElement* wind);
				inline bool isElement(const tinyxml2::XMLElement *wind, const std::string& name) const;
				inline bool isWindValid(tinyxml2::XMLElement* wind);
		};
	}
}

#endif // MCOMMANDSFACTORY_H
