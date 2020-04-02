#include "jetprotocol/jetnisx.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;
using namespace tinyxml2;

//=============		Get NisX Message		=============//
JetGetNisxMessage::JetGetNisxMessage(Macsa::Printers::JetPrinter &printer, unsigned int msgNum) :
	JetCommand(CMD_GET_NISX_MESSAGE, printer)
{
	_msgNum = msgNum;
}

JetGetNisxMessage::~JetGetNisxMessage()
{}

void JetGetNisxMessage::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, _msgNum);
	}
}

bool JetGetNisxMessage::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	_msgNum	= xml->UnsignedAttribute(MESSAGE_NUMBER_ATTRIBUTE, 0);
	return valid;
}

void JetGetNisxMessage::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		Message msg = _printer.messageManager().message(_msgNum);
		if (msg.name().length()) {
			cmd->SetText(msg.content().c_str());
		}
		else {
			_error = nJetErrorCode::MESSAGE_NUMBER_NOT_FOUND;
		}
		setCommandError(_error);
	}
}

bool JetGetNisxMessage::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
		if (_error == nJetErrorCode::COMMAND_OK) {
			_msgNum	= xml->UnsignedAttribute(MESSAGE_NUMBER_ATTRIBUTE, 0);
			Message msg = _printer.messageManager().message(_msgNum);
			if (msg.name().length()) {
				const XMLNode* nisx = xml->FirstChild();
				XMLPrinter p;
				p.VisitEnter(nisx);
				const char* content = p.CStr();
				if (content && strlen(content) > 0){
					msg.setContent(content);
					_printer.messageManager().setMessageContent(msg);
				}
			}
		}
	}
	return valid;
}

//=============		Set Nisx element		=============//
JetSetNisxElement::JetSetNisxElement(JetPrinter &printer, const std::string &name, const std::string &content) :
	JetCommand(CMD_SET_NISX_MESSAGE, printer)
{
	_name = name;
	_content = content;
}

JetSetNisxElement::~JetSetNisxElement()
{}

void JetSetNisxElement::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd ->SetAttribute(FILENAME_ATTRIBUTE, _name.c_str());
		cmd->SetText(_content.c_str());
	}
}

bool JetSetNisxElement::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid){
		parseCommandError();
	}
	return valid;
}

void JetSetNisxElement::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSetNisxElement::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
	}
	return valid;
}
