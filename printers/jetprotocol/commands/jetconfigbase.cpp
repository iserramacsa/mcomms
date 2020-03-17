#include "jetprotocol/jetconfigbase.h"
#include "jetprotocol/jetprotocol.h"

#include <algorithm>

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetConfigCommand::JetConfigCommand(const std::string &command, Printers::JetPrinter &printer):
	JetCommand(command, printer)
{}

JetConfigCommand::~JetConfigCommand()
{}

void JetConfigCommand::generalConfigToXml(const Printers::JetPrinter &printer, XMLElement **parent)
{
//	XMLElement * xGeneral = createChildNode(MCONFIG_GENERAL, parent);
}

void JetConfigCommand::datetimeToXml(const Macsa::Printers::JetPrinter &printer, XMLElement **parent)
{
//	createTextChildNode(MCONFIG_GENERAL_DT, printer.formatedDateTime(), parent);
}
