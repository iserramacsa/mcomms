#ifndef MACSA_JETPROTOCOL_PAUSE_COMMAND_H
#define MACSA_JETPROTOCOL_PAUSE_COMMAND_H

#include "jetcommand.h"

namespace Macsa{
	namespace JetProtocol {
		///
		/// \brief The JetGetPause is the command class to get the pause status
		/// of jet printers
		///
		class JetGetPause : public JetCommand
		{
			public:
				JetGetPause(Printers::JetPrinter& printer);
				virtual ~JetGetPause();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		///
		/// \brief The JetSetPause is the command class to set the pause status
		/// of jet printers
		///
		class JetSetPause : public JetCommand
		{
			public:
				JetSetPause(Printers::JetPrinter& printer);
				virtual ~JetSetPause();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MACSA_JETPROTOCOL_PAUSE_COMMAND_H
