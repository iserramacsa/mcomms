#ifndef MACSA_MPROTOCOL_COMMANDS_LIVE_H
#define MACSA_MPROTOCOL_COMMANDS_LIVE_H

#include "mcommands.h"

namespace Macsa
{
	namespace MProtocol {
		class MLive : public MCommand
		{
			public:
				MLive(Printers::TIJPrinter &printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MLIVE_COMMANDS_H
