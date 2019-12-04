#ifndef MSTATUS_COMMANDS_H
#define MSTATUS_COMMANDS_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {

		class MGetStatus : public MCommand
		{
			public:
				MGetStatus(Printers::Printer& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MSTATUS_COMMANDS_H
