#ifndef MACSA_MPROTOCOL_COMMANDS_CONFIG_BASE_H
#define MACSA_MPROTOCOL_COMMANDS_CONFIG_BASE_H
#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		/**
		 * @brief The MConfigCommand class is a class to easily parse or create xml for tij printer config
		 */
		class MConfigCommand : public MCommand
		{
			public:
				MConfigCommand(const std::string& command, Printers::TIJPrinter& printer);
				virtual ~MConfigCommand();

			protected:
				void generalConfigToXml(const Printers::TIJPrinter& printer, tinyxml2::XMLElement **parent);
				void printInvertedToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void nozzlesToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void shotModeToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void encoderToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void photocellToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void propertiesToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void cartridgeToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void inputsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void outputsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void dateCodesToXml(const Printers::TIJPrinter& printer, tinyxml2::XMLElement **parent);

				void generalConfigFromXml(const tinyxml2::XMLElement *parent, Printers::TIJPrinter& printer) const;
				void printInvertedFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void nozzlesFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void shotModeFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void encoderFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void photocellFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void propertiesFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void cartridgeFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void inputsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void outputsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void dateCodesFromXml(const tinyxml2::XMLElement *parent, Printers::TIJPrinter& printer) const;
		};
	}
}

#endif // MACSA_MPROTOCOL_COMMANDS_CONFIG_BASE_H
