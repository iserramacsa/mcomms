#ifndef MACSA_JETPROTOCOL_GET_VERSIONS_COMMAND_H
#define MACSA_JETPROTOCOL_GET_VERSIONS_COMMAND_H

#include "jetcommand.h"

namespace Macsa{
	namespace JetProtocol {
		///
		/// \brief The GetPrinterVersionInfo command class
		///
		class JetGetVersions : public JetCommand
		{
			public:
				JetGetVersions(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MACSA_JETPROTOCOL_PAUSE_COMMAND_H
