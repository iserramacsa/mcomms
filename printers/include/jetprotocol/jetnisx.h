#ifndef MACSA_JETPROTOCOL_NISX_COMMAND_H
#define MACSA_JETPROTOCOL_NISX_COMMAND_H

#include "jetcommand.h"

namespace Macsa{
	namespace JetProtocol {
		///
		/// \brief The JetGetNisxMessage is the command class to get all nisx file content
		/// of jet printers
		///
		class JetGetNisxMessage : public JetCommand
		{
			public:
				JetGetNisxMessage(Printers::JetPrinter& printer, unsigned int msgNum = 0);
				virtual ~JetGetNisxMessage();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();

			private:
				unsigned int _msgNum;
		};

		///
		/// \brief The JetSetNisxElement is the command class to set the pause status
		/// of jet printers
		///
		class JetSetNisxElement : public JetCommand
		{
			public:
				JetSetNisxElement(Printers::JetPrinter& printer, const std::string& name = "",  const std::string& content = "");
				virtual ~JetSetNisxElement();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();

			private:
				std::string _name;
				std::string _content;
		};
	}
}

#endif // MACSA_JETPROTOCOL_NISX_COMMAND_H
