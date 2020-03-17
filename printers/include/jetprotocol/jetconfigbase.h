#ifndef MACSA_JETPROTOCOL_COMMANDS_CONFIG_BASE_H
#define MACSA_JETPROTOCOL_COMMANDS_CONFIG_BASE_H
#include "jetcommand.h"

namespace Macsa {
	namespace JetProtocol {
		/**
		 * @brief The MConfigCommand class is a class to easily parse or create xml for tij printer config
		 */
		class JetConfigCommand : public JetCommand
		{
			public:
				JetConfigCommand(const std::string& command, Printers::JetPrinter& printer);
				virtual ~JetConfigCommand();

			protected:
				void generalConfigToXml(const Printers::JetPrinter& printer, tinyxml2::XMLElement **parent);
				void datetimeToXml(const Printers::JetPrinter& printer, tinyxml2::XMLElement **parent);

		};
	}
}

#endif // MACSA_JETPROTOCOL_COMMANDS_CONFIG_BASE_H
