#ifndef MACSA_JETPROTOCOL_COMMANDS_CONFIG_H
#define MACSA_JETPROTOCOL_COMMANDS_CONFIG_H
#include "jetconfigbase.h"

namespace Macsa {
	namespace JetProtocol {
		/**
		 * @brief The GETCONFIG command class
		 */
		class JetGetConfig : public JetConfigCommand
		{
			public:
				JetGetConfig(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

		};

		/**
		 * @brief The SETCONFIG command class
		 */
		class JetSetConfig : public JetConfigCommand
		{
			public:
				JetSetConfig(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MCONFIGCOMMANDS_H
