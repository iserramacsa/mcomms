#ifndef MACSA_MPROTOCOL_COMMANDS_UPDATE_H
#define MACSA_MPROTOCOL_COMMANDS_UPDATE_H

#include "mprotocol/mcommands.h"

namespace Macsa {
	namespace MProtocol {
		class MUpdate : public MCommand
		{
			public:
				MUpdate(Printers::TijPrinter& printer);
				virtual ~MUpdate();

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);


			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MACSA_MPROTOCOL_COMMANDS_UPDATE_H
