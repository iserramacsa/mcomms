#ifndef MACSA_JETPROTOCOL_FILES_COMMANDS_H
#define MACSA_JETPROTOCOL_FILES_COMMANDS_H

#include "jetcommands.h"

namespace Macsa {
	namespace JetProtocol {
		/**
		 * @brief The GETCONFIG command class
		 */
		class JetGetFilesList : public JetCommand
		{
			public:
				JetGetFilesList(Printers::JetPrinter& printer);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}
#endif // MACSA_JETPROTOCOL_FILES_COMMANDS_H
