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
		unsigned int num = getUnsignedFromChildNode(eCmd, JET_MESSAGE_NUMBER);
		std::string filename = getTextFromChildNode(eCmd, JET_MESSAGE_NAME);
		if (filename.length()){
			_printer.messageManager().setCurrentMessage(filename, num);
		}
	}
}

void JetGetStatus::parseNetworkStatus(const XMLElement *eNetwork)
{
	if (eNetwork) {
		const XMLElement* eAdapter = eNetwork->FirstChildElement(JET_NETWORK_ADAPTER);
		while(eAdapter) {
			const XMLAttribute* eIfaceID = eAdapter->FindAttribute(ID_ATTRIBUTE);
			if (eIfaceID){
				std::string id = (eIfaceID->Value() ? eIfaceID->Value() : "");
				Printers::JetComms* comms =  dynamic_cast<Printers::JetComms*>(_printer.comms());
				if (comms) {
					Printers::Ethernet* eth = comms->ethernetIface(id);
					eth->setConnected(eAdapter->BoolAttribute(CONNECTED_ATTRIBUTE, false));
				}
			}
			eAdapter = eAdapter->NextSiblingElement(JET_NETWORK_ADAPTER);
		}
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
		parseCurrentMessage(xml);
		parseNetworkStatus(xml->FirstChildElement(JET_NETWORKS_LIST));

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

