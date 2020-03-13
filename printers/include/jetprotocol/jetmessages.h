#ifndef  MACSA_MPROTOCOL_COMMANDS_SET_CURRENT_MESSAGE_H
#define  MACSA_MPROTOCOL_COMMANDS_SET_CURRENT_MESSAGE_H

#include "mcommands.h"
#include <string>

namespace Macsa {
	namespace MProtocol {
		class MSetCurrentMessage : public MCommand
		{
			public:
				MSetCurrentMessage(Printers::TijPrinter& printer, const std::string& filename = "");
				virtual ~MSetCurrentMessage();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
				std::string _filePath;
		};
	}
}

#endif  //MACSA_MPROTOCOL_COMMANDS_SET_CURRENT_MESSAGE_H
