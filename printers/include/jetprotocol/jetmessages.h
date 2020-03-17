#ifndef  MACSA_JETPROTOCOL_MESSAGES_COMMANDS_H
#define  MACSA_JETPROTOCOL_MESSAGES_COMMANDS_H

#include "jetcommand.h"
#include <string>

namespace Macsa {
	namespace JetProtocol {
		class JetSetCurrentMessage : public JetCommand
		{
			public:
				JetSetCurrentMessage(Printers::JetPrinter& printer, const std::string& filename = "");
				virtual ~JetSetCurrentMessage();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif  //MACSA_MPROTOCOL_COMMANDS_SET_CURRENT_MESSAGE_H
