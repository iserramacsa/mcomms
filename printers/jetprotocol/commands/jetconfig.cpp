#include "jetprotocol/jetconfig.h"
#include "jetprotocol/jetprotocol.h"


using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetGetConfig::JetGetConfig(Printers::JetPrinter &printer):
	JetConfigCommand(CMD_GET_CONFIG, printer)
{}

bool JetGetConfig::parseRequest(const XMLElement *xml)
{
	return false;
}

bool JetGetConfig::parseResponse(const XMLElement *xml)
{
	return false;
}

void JetGetConfig::buildRequest()
{
}


void JetGetConfig::buildResponse()
{
}

//######################################################
//	SETCONFIG
//######################################################
JetSetConfig::JetSetConfig(Macsa::Printers::JetPrinter &printer):
	JetConfigCommand(CMD_SET_CONFIG, printer)
{}

void JetSetConfig::buildRequest()
{
}

bool JetSetConfig::parseRequest(const XMLElement *xml)
{
	return false;
}

void JetSetConfig::buildResponse()
{
}

bool JetSetConfig::parseResponse(const XMLElement *xml)
{
	return false;
}
