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
				MConfigCommand(const std::string& command, Printers::TijPrinter& printer);
				virtual ~MConfigCommand();

			protected:
				void generalConfigToXml(const Printers::TijPrinter& printer, tinyxml2::XMLElement **parent);
				void datetimeToXml(const Printers::TijPrinter& printer, tinyxml2::XMLElement **parent);
				void loggerToXml(const Printers::TijPrinter& printer, tinyxml2::XMLElement **parent);
				void printerConnectionsToXml(const Printers::TijComms* comms, tinyxml2::XMLElement **parent);
				void boardToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void boardTypeToXml(const std::string &boardType, tinyxml2::XMLElement **parent);
				void autostartToXml(bool autostart, tinyxml2::XMLElement **parent);
				void lowLevelOutputToXml(bool lowLevel, tinyxml2::XMLElement **parent);
				void enabledToXml(bool enabled, tinyxml2::XMLElement **parent);
				void blockToXml(bool block, tinyxml2::XMLElement **parent);
				void userMessageToXml(const std::string &userMessage, tinyxml2::XMLElement **parent);
				void bcdToXml(const Macsa::Printers::BCDMode& bcdMode, const Printers::BCDTable& bcdTable, tinyxml2::XMLElement **parent);
				void printDirectionToXml(const Printers::PrinterDir &printDir, tinyxml2::XMLElement **parent);
				void printInvertedToXml(bool printRotated, tinyxml2::XMLElement **parent);
				void nozzlesToXml(const Printers::NozzlesCol &nozzlesCol, tinyxml2::XMLElement **parent);
				void shotModeToXml(const Printers::ShotMode& shotMode, tinyxml2::XMLElement **parent);
				void encoderToXml(const Printers::Encoder &encoder, tinyxml2::XMLElement **parent);
				void photocellToXml(const Printers::Photocell& photocell, tinyxml2::XMLElement **parent);
				void propertiesToXml(const Printers::Board::propertyMap& properties, tinyxml2::XMLElement **parent);
				void cartridgeToXml(const Printers::Cartridge& cartridge, tinyxml2::XMLElement **parent);
				void inputsToXml(const std::vector<Printers::Input>& inputs, tinyxml2::XMLElement **parent);
				void outputsToXml(const std::vector<Printers::Output>& outputs, tinyxml2::XMLElement **parent);
				void dateCodesToXml(const Printers::DateCodes& dateCodes, tinyxml2::XMLElement **parent);

				void generalConfigFromXml(const tinyxml2::XMLElement *parent, Printers::TijPrinter& printer) const;
				void printerConnectionsFromXml(const tinyxml2::XMLElement *parent, Printers::TijComms& comms) const;
				void boardFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void bcdFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void shotModeFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void encoderFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void propertiesFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void cartridgeFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void inputsFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void outputsFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				void dateCodesFromXml(const tinyxml2::XMLElement *xBoard, Printers::TijPrinter& printer) const;

			private:
				template<class T>
				void dateCodesFormatedListToXml(const std::string &format, const std::vector<T>& dateCodesList, tinyxml2::XMLElement **parent);
				void boardTextValueToXml(const std::string &valueName, const std::string &value, tinyxml2::XMLElement **parent);

		};
	}
}

#endif // MACSA_MPROTOCOL_COMMANDS_CONFIG_BASE_H
