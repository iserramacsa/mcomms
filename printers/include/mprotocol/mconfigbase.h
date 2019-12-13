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
				inline void generalConfigToXml(const Printers::TIJPrinter& printer, tinyxml2::XMLElement **parent);
				inline void printerConnectionsToXml(const Printers::TIJComms* comms, tinyxml2::XMLElement **parent);
				inline void boardToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				inline void boardTypeToXml(const std::string &boardType, tinyxml2::XMLElement **parent);
				inline void autostartToXml(bool autostart, tinyxml2::XMLElement **parent);
				inline void enabledToXml(bool enabled, tinyxml2::XMLElement **parent);
				inline void blockToXml(bool block, tinyxml2::XMLElement **parent);
				inline void userMessageToXml(const std::string &userMessage, tinyxml2::XMLElement **parent);
				inline void bcdToXml(const Macsa::Printers::BCDMode& bcdMode, const Printers::BCDTable& bcdTable, tinyxml2::XMLElement **parent);
				inline void printDirectionToXml(const Printers::PrinterDir &printDir, tinyxml2::XMLElement **parent);
				inline void printInvertedToXml(bool printRotated, tinyxml2::XMLElement **parent);
				inline void nozzlesToXml(const Printers::NozzlesCol &nozzlesCol, tinyxml2::XMLElement **parent);
				inline void shotModeToXml(const Printers::ShotMode& shotMode, tinyxml2::XMLElement **parent);
				inline void encoderToXml(const Printers::Encoder &encoder, tinyxml2::XMLElement **parent);
				inline void photocellToXml(const Printers::Photocell& photocell, tinyxml2::XMLElement **parent);
				inline void propertiesToXml(const Printers::Board::propertyMap& properties, tinyxml2::XMLElement **parent);
				inline void cartridgeToXml(const Printers::Cartridge& cartridge, tinyxml2::XMLElement **parent);
				inline void inputsToXml(const std::vector<Printers::Input>& inputs, tinyxml2::XMLElement **parent);
				inline void outputsToXml(const std::vector<Printers::Output>& outputs, tinyxml2::XMLElement **parent);
				inline void dateCodesToXml(const Printers::DateCodes& dateCodes, tinyxml2::XMLElement **parent);

				inline void generalConfigFromXml(const tinyxml2::XMLElement *parent, Printers::TIJPrinter& printer) const;
				inline void printerConnectionsFromXml(const tinyxml2::XMLElement *parent, Printers::TIJComms& comms) const;
				inline void boardFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void bcdFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void shotModeFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void encoderFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void propertiesFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void cartridgeFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void inputsFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void outputsFromXml(const tinyxml2::XMLElement *xBoard, Printers::Board& board) const;
				inline void dateCodesFromXml(const tinyxml2::XMLElement *xBoard, Printers::TIJPrinter& printer) const;

			private:
				template<class T>
				inline void dateCodesFormatedListToXml(const std::string &format, const std::vector<T>& dateCodesList, tinyxml2::XMLElement **parent);
				inline void boardTextValueToXml(const std::string &valueName, const std::string &value, tinyxml2::XMLElement **parent);

		};
	}
}

#endif // MACSA_MPROTOCOL_COMMANDS_CONFIG_BASE_H
