#include "jetprotocol/jetsingleconfig.h"
#include "jetprotocol/jetprotocol.h"


using namespace Macsa::JetProtocol;
using namespace tinyxml2;
/************************   BASSE CLASS   ************************/
JetSingleSetConfigBase::JetSingleSetConfigBase(const std::string command, Macsa::Printers::JetPrinter &printer):
	JetCommand(command, printer)
{}

void JetSingleSetConfigBase::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSingleSetConfigBase::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
	}
	return valid;
}

/************************   SET PRINT DIRECTION   ************************/
JetSetPrintDirection::JetSetPrintDirection(Macsa::Printers::JetPrinter &printer, Macsa::Printers::PrintDirection direction) :
	JetSingleSetConfigBase(CMD_SET_PRINT_DIR, printer)
{
	_direction = direction;
}

JetSetPrintDirection::JetSetPrintDirection(Macsa::Printers::JetPrinter &printer) :
	JetSingleSetConfigBase(CMD_SET_PRINT_DIR, printer)
{
	_direction = Printers::nPrintDirection::PRINTDIR_RL;
}

void JetSetPrintDirection::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(VALUE_ATTRIBUTE, _direction());
	}
}

bool JetSetPrintDirection::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		unsigned int dir = xml->UnsignedAttribute(VALUE_ATTRIBUTE, static_cast<unsigned>(Printers::nPrintDirection::PRINTDIR_LR));
		_printer.setPrintDir(static_cast<Printers::nPrintDirection>(dir));
	}
	return valid;
}


/************************   SET BITMAP INVERTED   ************************/
JetSetBitmapInverted::JetSetBitmapInverted(Macsa::Printers::JetPrinter &printer, bool inverted):
	JetSingleSetConfigBase(CMD_SET_PRINT_INVERT, printer)
{
	_inverted = inverted;
}

JetSetBitmapInverted::JetSetBitmapInverted(Macsa::Printers::JetPrinter &printer):
	JetSingleSetConfigBase(CMD_SET_PRINT_INVERT, printer)
{
	_inverted = false;
}

void JetSetBitmapInverted::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(VALUE_ATTRIBUTE, toString(_inverted).c_str());
	}
}

bool JetSetBitmapInverted::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		_printer.setBitmapInverted(strToBool(getTextAttribute(xml, VALUE_ATTRIBUTE, "false")));
	}
	return valid;
}

/************************   SET BITMAP INVERTED   ************************/
JetSetPrintheadEnabled::JetSetPrintheadEnabled(Macsa::Printers::JetPrinter &printer, Macsa::Printers::PHEnableMode mode):
	JetSingleSetConfigBase(CMD_SET_PRINTHEAD_ENABLE, printer)
{
	_mode = mode;
}

JetSetPrintheadEnabled::JetSetPrintheadEnabled(Macsa::Printers::JetPrinter &printer):
	JetSingleSetConfigBase(CMD_SET_PRINTHEAD_ENABLE, printer)
{
	_mode = Printers::nPHEnableMode::ENABLE_BOTH;
}

void JetSetPrintheadEnabled::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(VALUE_ATTRIBUTE, _mode());
	}
}

bool JetSetPrintheadEnabled::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		unsigned int mode = xml->UnsignedAttribute(VALUE_ATTRIBUTE, static_cast<unsigned>(Printers::nPHEnableMode::ENABLE_BOTH));
		_mode = static_cast<Printers::nPHEnableMode>(mode);
	}
	return valid;
}

/************************   SET PRINT SPEED   ************************/
JetSetPrintSpeed::JetSetPrintSpeed(Macsa::Printers::JetPrinter &printer, unsigned int speed) :
	JetSingleSetConfigBase(CMD_SET_PRINT_SPEED, printer)
{
	_speed = speed;
}

JetSetPrintSpeed::JetSetPrintSpeed(Macsa::Printers::JetPrinter &printer) :
	JetSingleSetConfigBase(CMD_SET_PRINT_SPEED, printer)
{
	_speed = 0;
}

void JetSetPrintSpeed::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(VALUE_ATTRIBUTE, _speed);
	}
}

bool JetSetPrintSpeed::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		_speed = xml->UnsignedAttribute(VALUE_ATTRIBUTE, 0);
		_printer.printhead(0).encoder().setFixedSpeed(_speed); // ¿?
	}
	return valid;
}

/************************   SET PRINT DELAY   ************************/
JetSetPrintDelay::JetSetPrintDelay(Macsa::Printers::JetPrinter &printer, unsigned int delay) :
	JetSingleSetConfigBase(CMD_SET_PRINT_DELAY, printer)
{
	_delay = delay;
}

JetSetPrintDelay::JetSetPrintDelay(Macsa::Printers::JetPrinter &printer) :
	JetSingleSetConfigBase(CMD_SET_PRINT_DELAY, printer)
{
	_delay = 0;
}

void JetSetPrintDelay::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(VALUE_ATTRIBUTE, _delay);
	}
}

bool JetSetPrintDelay::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		_delay = xml->UnsignedAttribute(VALUE_ATTRIBUTE, 0);
		_printer.printhead(0).setPrintDelay(_delay); // ¿?
	}
	return valid;
}

/************************   SET HOR. RESOLUTION   ************************/
JetSetHorizontalResolution::JetSetHorizontalResolution(Macsa::Printers::JetPrinter &printer, unsigned int hres) :
	JetSingleSetConfigBase(CMD_SET_HOR_RESOLUTION, printer)
{
	_hres = hres;
}

JetSetHorizontalResolution::JetSetHorizontalResolution(Macsa::Printers::JetPrinter &printer) :
	JetSingleSetConfigBase(CMD_SET_HOR_RESOLUTION, printer)
{
	_hres = 180;
}

void JetSetHorizontalResolution::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(VALUE_ATTRIBUTE, _hres);
	}
}

bool JetSetHorizontalResolution::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		_hres = xml->UnsignedAttribute(VALUE_ATTRIBUTE, 0);
		_printer.printhead(0).sethorizontalResolution(_hres); // ¿?
	}
	return valid;
}

/************************   GET PRINT SPEED   ************************/
JetGetPrintSpeed::JetGetPrintSpeed(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_PRINT_SPEED, printer)
{}

void JetGetPrintSpeed::buildRequest()
{
	newCommandWind();
}

bool JetGetPrintSpeed::parseRequest(const tinyxml2::XMLElement* xml)
{
	return isValidWind(xml);
}
void JetGetPrintSpeed::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	setCommandError(_error);
	cmd->SetAttribute(VALUE_ATTRIBUTE, _printer.printhead(0).encoder().fixedSpeed());
}

bool JetGetPrintSpeed::parseResponse(const tinyxml2::XMLElement*xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
		unsigned int value = xml->UnsignedAttribute(VALUE_ATTRIBUTE, 0);
		_printer.printhead(0).encoder().setFixedSpeed(value);
	}
	return valid;
}

/************************   GET PRINT DELAY   ************************/
JetGetPrintDelay::JetGetPrintDelay(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_PRINT_DELAY, printer)
{}

void JetGetPrintDelay::buildRequest()
{
	newCommandWind();
}

bool JetGetPrintDelay::parseRequest(const tinyxml2::XMLElement* xml)
{
	return isValidWind(xml);
}
void JetGetPrintDelay::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	setCommandError(_error);
	cmd->SetAttribute(VALUE_ATTRIBUTE, _printer.printhead(0).printDelay());
}

bool JetGetPrintDelay::parseResponse(const tinyxml2::XMLElement*xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
		unsigned int value = xml->UnsignedAttribute(VALUE_ATTRIBUTE, 0);
		_printer.printhead(0).setPrintDelay(value);
	}
	return valid;
}

/************************   GET PRINT DELAY   ************************/
JetGetHorizontalResolution::JetGetHorizontalResolution(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_HOR_RESOLUTION, printer)
{}

void JetGetHorizontalResolution::buildRequest()
{
	newCommandWind();
}

bool JetGetHorizontalResolution::parseRequest(const tinyxml2::XMLElement* xml)
{
	return isValidWind(xml);
}
void JetGetHorizontalResolution::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	setCommandError(_error);
	cmd->SetAttribute(VALUE_ATTRIBUTE, _printer.printhead(0).horizontalResolution());
}

bool JetGetHorizontalResolution::parseResponse(const tinyxml2::XMLElement*xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
		unsigned int value = xml->UnsignedAttribute(VALUE_ATTRIBUTE, 0);
		_printer.printhead(0).sethorizontalResolution(value);
	}
	return valid;
}

/************************   RESET INK ALARM   ************************/
JetResetInkAlarm::JetResetInkAlarm(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_RESET_INK_ALARM, printer)
{}

void JetResetInkAlarm::buildRequest()
{
	newCommandWind();
}

bool JetResetInkAlarm::parseRequest(const tinyxml2::XMLElement* xml)
{
	return isValidWind(xml);
}
void JetResetInkAlarm::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetResetInkAlarm::parseResponse(const tinyxml2::XMLElement*xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
	}
	return valid;
}
