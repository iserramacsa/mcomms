#ifndef MUPDATECOMMANDS_H
#define MUPDATECOMMANDS_H
#include "mprotocol/mcommands.h"

namespace Macsa {
	namespace MProtocol {
		class MUpdate : public MCommand
		{
			public:
				MUpdate(Printers::TIJPrinter& printer);
				virtual ~MUpdate();

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);


			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MUPDATECOMMANDS_H
