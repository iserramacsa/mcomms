#include "jetprotocol/jetpause.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;
using namespace tinyxml2;

/***************  Get Pause  ***************/
JetGetPause::JetGetPause(JetPrinter &printer) :
	JetCommand(CMD_GET_PAUSE, printer)
{}

JetGetPause::~JetGetPause()
{}

bool JetGetPause::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid) {
		parseCommandError();
		const XMLAttribute* value = xml->FindAttribute(VALUE_ATTRIBUTE);
		if (value != nullptr) {
			bool paused = strToBool(value->Value());
			_printer.setPause(paused);
		}
	}
	return valid;
}

bool JetGetPause::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid) {
		parseCommandError();
	}
	return valid;
}

void JetGetPause::buildRequest()
{
	newCommandWind();
}

void JetGetPause::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(VALUE_ATTRIBUTE, toString(_printer.paused()).c_str());
	setCommandError(_error);
}

/***************  Set Pause  ***************/
JetSetPause::JetSetPause(JetPrinter &printer, bool pause) :
	JetCommand(CMD_SET_PAUSE, printer)
{
	_pause = pause;
}

JetSetPause::JetSetPause(JetPrinter &printer) :
	JetCommand(CMD_SET_PAUSE, printer)
{
	_pause = false;
}

void JetSetPause::buildRequest()
{
	XMLElement * cmd = newCommandWind();
	cmd->SetAttribute(VALUE_ATTRIBUTE, _pause);
}

bool JetSetPause::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid){
		const XMLAttribute* value = xml->FindAttribute(VALUE_ATTRIBUTE);
		if (value != nullptr) {
			bool paused = strToBool(value->Value());
			_printer.setPause(paused);
		}
	}
	return valid;
}

void JetSetPause::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSetPause::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid){
		parseCommandError();
	}
	return valid;
}
