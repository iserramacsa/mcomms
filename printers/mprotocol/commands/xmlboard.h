#ifndef MACSA_MPROTOCOL_XML_BOARD_H
#define MACSA_MPROTOCOL_XML_BOARD_H

#include "printer/printer.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace Macsa {
	namespace MProtocol {
			XMLElement* generalConfigToXml(const Printers::Printer& printer, XMLDocument& doc);
			XMLElement* boardConnectionsToXml(const Printers::PrinterComms &comms, XMLDocument& doc);
	}
}


#endif //MACSA_MPROTOCOL_XML_BOARD_H
