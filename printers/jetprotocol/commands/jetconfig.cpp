#include "jetprotocol/jetconfig.h"
#include "jetprotocol/jetprotocol.h"


using namespace Macsa::JetProtocol;
using namespace tinyxml2;

/*********************************   GET CONFIG   *********************************/
JetGetConfig::JetGetConfig(Printers::JetPrinter &printer):
	JetConfigCommand(CMD_GET_CONFIG, printer)
{}

void JetGetConfig::buildRequest()
{
	newCommandWind();
}

bool JetGetConfig::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetConfig::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		printheadToXml(_printer, &cmd);
		const Printers::JetComms* comms = dynamic_cast<const Printers::JetComms*>(_printer.comms());
		if (comms){
			printerCommsToXml(*comms, &cmd);
		}
	}
}

bool JetGetConfig::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);

	if (valid) {
		parseCommandError();
		if (_error == Printers::nJetErrorCode::COMMAND_OK) {
			printheadFromXml(xml->FirstChildElement(JET_PRINTHEAD_TAG), _printer);
			Printers::JetComms* comms = dynamic_cast<Printers::JetComms*>(_printer.comms());
			if (comms){
				printerCommsFromXml(xml->FirstChildElement(), *comms);
			}
		}
	}

	return valid;
}

/*********************************   SET CONFIG   *********************************/
JetSetConfig::JetSetConfig(Macsa::Printers::JetPrinter &printer):
	JetConfigCommand(CMD_SET_CONFIG, printer)
{}

void JetSetConfig::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		printheadToXml(_printer, &cmd);
		const Printers::JetComms* comms = dynamic_cast<const Printers::JetComms*>(_printer.comms());
		if (comms){
			printerCommsToXml(*comms, &cmd);
		}
	}
}

bool JetSetConfig::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		//ToDo: check errors  (Server side)
	}
	return valid;
}

void JetSetConfig::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		//ToDo: Add errors (Server side)
	}
}

bool JetSetConfig::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		for (const XMLElement* item = xml->FirstChildElement(JET_ERROR_TAG); item != nullptr; item = item->NextSiblingElement(JET_ERROR_TAG))
		{
			const char* configItem = item->Attribute(ITEM_ATTRIBUTE);
			const char* errorCode = item->Attribute(ERROR_CODE_ATTRIBUTE);
			if (configItem != nullptr && strlen(configItem) && errorCode != nullptr) {
				_attributes.insert(std::pair<std::string, std::string>(configItem, errorCode));
			}
		}
	}
	return valid;
}
