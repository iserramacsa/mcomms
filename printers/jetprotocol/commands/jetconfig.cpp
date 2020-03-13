#include "jetprotocol/jetconfig.h"
#include "jetprotocol/jetprotocol.h"


using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetGetConfig::JetGetConfig(Printers::JetPrinter &printer):
	JetConfigCommand(CMD_GET_CONFIG, printer)
{}

bool JetGetConfig::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	return valid;
}

bool JetGetConfig::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
	}
	return valid;
}

void JetGetConfig::buildRequest()
{
	newCommandNode();
}


void JetGetConfig::buildResponse()
{
	XMLElement* cmd = newCommandNode();

	generalConfigToXml(_printer, &cmd);

	addWindError(_error);
}

//######################################################
//	SETCONFIG
//######################################################
JetSetConfig::JetSetConfig(Macsa::Printers::JetPrinter &printer):
	JetConfigCommand(MCONFIG_SET, printer)
{}

void JetSetConfig::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	generalConfigToXml(_printer, &cmd);
}

bool JetSetConfig::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	return valid;
}

void JetSetConfig::buildResponse()
{
	newCommandNode();
	addWindError(_error);
}

bool JetSetConfig::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	if  (valid) {
		_error = getCommandError(xml);
	}
	return valid;
}
