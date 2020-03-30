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
				void printheadToXml(const Printers::JetPrinter& printer, tinyxml2::XMLElement **parent);
				void printerCommsToXml(const Printers::JetComms& comms, tinyxml2::XMLElement **parent);
				void printheadFromXml( const tinyxml2::XMLElement *ePrinthead, Printers::JetPrinter& printer);
				void printerCommsFromXml(const tinyxml2::XMLElement *eComms, Printers::JetComms& comms);

			private:
				tinyxml2::XMLElement* insertPrintheadProperty(const std::string &propetyName, const std::string &value, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement* insertPrintheadProperty(const std::string &propetyName, unsigned int value, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement* insertPrintheadProperty(const std::string &propetyName, bool value, tinyxml2::XMLElement **parent);
				void networkApaterToXml(const Printers::Ethernet& eth, tinyxml2::XMLElement **parent);
				void networkAdapterFromXml(const tinyxml2::XMLElement* eEth, Printers::Ethernet& eth);
		};
	}
}

#endif // MACSA_JETPROTOCOL_COMMANDS_CONFIG_BASE_H
