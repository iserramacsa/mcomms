#ifndef MACSA_JETPROTOCOL_COMMANDS_ERRORS_LOGS_H
#define MACSA_JETPROTOCOL_COMMANDS_ERRORS_LOGS_H

#include "jetcommand.h"

namespace Macsa
{
	namespace JetProtocol {

		class JetErrorsLogs : public JetCommand
		{
			public:
				JetErrorsLogs(Printers::JetPrinter &printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

//				virtual void addNewItem(const Macsa::Printers::Error& error, tinyxml2::XMLElement** parent);
//				virtual bool parseItem(const tinyxml2::XMLElement* item, Macsa::Printers::Error& error);
		};
	}
}

#endif // MACSA_MPROTOCOL_COMMANDS_ERRORS_LOGS_H
