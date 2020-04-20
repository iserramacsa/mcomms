#include "jetprotocol/jetsinglestatus.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

/************************   GET SSCC   ************************/
JetGetSSCC::JetGetSSCC(Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_SSCC, printer)
{}

void JetGetSSCC::buildRequest()
{
	newCommandWind();
}

bool JetGetSSCC::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetSSCC::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	setCommandError(_error);
	if (cmd) {
		cmd->SetAttribute(VALUE_ATTRIBUTE, XMLCommand::toString(_printer.sscc()).c_str());
	}
}

bool JetGetSSCC::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	parseCommandError(xml);
	if (valid) {
		uint64_t value = static_cast<uint64_t>(xml->Int64Attribute(VALUE_ATTRIBUTE, static_cast<int64_t>(_printer.sscc())));
		_printer.setSscc(value);
	}
	return valid;
}

/************************   INCREMENT SSCC   ************************/
JetIncrementSSCC::JetIncrementSSCC(Printers::JetPrinter &printer) :
	JetCommand(CMD_INC_SSCC, printer)
{}

void JetIncrementSSCC::buildRequest()
{
	newCommandWind();
}

bool JetIncrementSSCC::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetIncrementSSCC::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetIncrementSSCC::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	parseCommandError(xml);
	return valid;
}

/************************   GET DATETIME   ************************/
JetGetDatetime::JetGetDatetime(Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_DATETIME, printer)
{}

void JetGetDatetime::buildRequest()
{
	newCommandWind();
}

bool JetGetDatetime::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetDatetime::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetGetDatetime::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	parseCommandError(xml);
	if (valid) {
		std::string dt = getTextAttribute(xml, VALUE_ATTRIBUTE, _printer.formatedDateTime());
		_printer.setDateTime(dt);
	}
	return valid;
}

/************************   SET DATETIME   ************************/
JetSetDatetime::JetSetDatetime(Printers::JetPrinter &printer, time_t datetime) :
	JetCommand(CMD_SET_DATETIME, printer)
{
	_time = datetime;
}

JetSetDatetime::JetSetDatetime(Printers::JetPrinter &printer) :
	JetCommand(CMD_SET_DATETIME, printer)
{
	_time = time(nullptr);
}

void JetSetDatetime::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(VALUE_ATTRIBUTE, _printer.formatedDateTime(_time).c_str());
}

bool JetSetDatetime::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		std::string dt = getTextAttribute(xml, VALUE_ATTRIBUTE, _printer.formatedDateTime());
		_printer.setDateTime(dt);
	}
	setCommandError(_error);
	return valid;
}

void JetSetDatetime::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSetDatetime::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	parseCommandError(xml);
	return valid;
}

