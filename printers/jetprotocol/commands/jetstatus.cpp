#include "jetprotocol/jetstatus.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

//================		GET STATUS COMMAND		================//
JetGetStatus::JetGetStatus(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_STATUS, printer)
{}

JetGetStatus::~JetGetStatus()
{}

void JetGetStatus::buildRequest()
{
	newCommandWind();
}

bool JetGetStatus::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetStatus::buildResponse()
{
	newCommandWind();
}

void JetGetStatus::parsePrintheadsTemperature(const XMLElement *ePrintheads)
{
	if (ePrintheads){
		const XMLElement* ePH = ePrintheads->FirstChildElement(JET_PRINTHEAD_TAG);
		while(ePH != nullptr) {
			unsigned int id = ePH->UnsignedAttribute(ID_ATTRIBUTE, 0);
			unsigned int temperature = ePH->UnsignedAttribute(TEMPERATURE_ATTRIBUTE);
			_printer.setPrintheadTemperature(id, temperature);
			ePH = ePH->NextSiblingElement(JET_PRINTHEAD_TAG);
		}
	}
}

void JetGetStatus::parseInkLevels(const XMLElement *eTanks)
{
	if (eTanks != nullptr) {
		const XMLElement* eTank = eTanks->FirstChildElement(JET_INK_TANK);
		while(eTank != nullptr) {
			unsigned int id = eTank->UnsignedAttribute(ID_ATTRIBUTE);
			unsigned int level = eTank->UnsignedAttribute(LEVEL_ATTRIBUTE);
			_printer.setTankLevel(id, level);
			eTank = eTank->NextSiblingElement(JET_PRINTHEAD_TAG);
		}
	}
}

void JetGetStatus::parseCurrentMessage(const XMLElement *eCmd)
{
	if (eCmd) {
		const XMLElement* eMsgNum = eCmd->FirstChildElement(JET_MESSAGE_NUMBER);
		const XMLElement* eMsgName = eCmd->FirstChildElement(JET_MESSAGE_NAME);
		Printers::JetMessagesManager& manager = _printer.messageManager();
	}
}

bool JetGetStatus::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid) {
		parseCommandError();
		parsePrintheadsTemperature(xml->FirstChildElement(JET_PRINTHEADS_LIST));
		parseInkLevels(xml->FirstChildElement(JET_INK_TANKS_LIST));
		_printer.setPrintStatus(getBoolFromChildNode(xml, JET_PRINT_STATUS, _printer.printStatus()));
		_printer.setPause(getBoolFromChildNode(xml, JET_PRINT_PAUSE, _printer.paused()));

	}
	return valid;
}

//================		GET IO STATUS COMMAND		================//
JetGetIOStatus::JetGetIOStatus(Macsa::Printers::JetPrinter &printer):
	JetCommand("", printer)
{}

JetGetIOStatus::~JetGetIOStatus()
{}

void JetGetIOStatus::buildRequest()
{
	newCommandWind();
}

bool JetGetIOStatus::parseRequest(const XMLElement *xml)
{
	return false;
}

void JetGetIOStatus::buildResponse()
{
}

bool JetGetIOStatus::parseResponse(const XMLElement *xml)
{
	return false;

}

//================		GET CURRENT ERRORS COMMAND		================//
JetGetErrors::JetGetErrors(Macsa::Printers::JetPrinter &printer):
	JetCommand("", printer)
{}

JetGetErrors::~JetGetErrors()
{}

void JetGetErrors::buildRequest()
{
	newCommandWind();
}

bool JetGetErrors::parseRequest(const XMLElement *xml)
{
	return false;
}
void JetGetErrors::buildResponse()
{

}
bool JetGetErrors::parseResponse(const XMLElement *xml)
{
	return false;
}

