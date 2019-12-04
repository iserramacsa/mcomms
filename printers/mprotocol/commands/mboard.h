#ifndef MACSA_MPROTOCOL_XML_BOARD_H
#define MACSA_MPROTOCOL_XML_BOARD_H

#include "printer/printer.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace Macsa {
	namespace MProtocol {
		namespace MPrinter {
			XMLElement* generalConfigToXml(const Printers::Printer& printer, XMLDocument& doc);
			XMLElement* printerConnectionsToXml(const Printers::PrinterComms &comms, XMLDocument& doc);
			XMLElement* boardConfigToXml(const Printers::Board& board, XMLDocument& doc);
			XMLElement* boardBCDTableToXml(const Printers::BcdTable& bcdTable, XMLDocument& doc);
			XMLElement* boardShotModeToXml(const Printers::ShotMode& shotMode, XMLDocument& doc);
			XMLElement* boardEncoderToXml(const Printers::Encoder& encoder, XMLDocument& doc);
			void boardFromXml(Printers::Printer& printer, const XMLElement * xml);
			void parseCounters(Printers::Board &board, const XMLElement * eBoard);
			void parseErrors(Printers::Board &board, const XMLElement * eBoard);
			void parseInputs(Printers::Board &board, const XMLElement * eBoard);
			void parseOutputs(Printers::Board &board, const XMLElement * eBoard);
		}
	}
}


#endif //MACSA_MPROTOCOL_XML_BOARD_H
