#include "jetprotocol/jetmessages.h"
#include "jetprotocol/jetprotocol.h"
#include "utils/base64.h"
#include <algorithm> //Vector sort

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

/*********************************   SET CURRENT MESSAGE   *********************************/
JetSetCurrentMessage::JetSetCurrentMessage(Macsa::Printers::JetPrinter &printer, unsigned int messageNumber) :
	JetCommand(CMD_MESSAGE_NUM, printer)
{
	_msgNumber = messageNumber;
}

JetSetCurrentMessage::JetSetCurrentMessage(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_MESSAGE_NUM, printer)
{
	_msgNumber = 0;
}

void JetSetCurrentMessage::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(VALUE_ATTRIBUTE, _msgNumber);
}

void JetSetCurrentMessage::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSetCurrentMessage::parseRequest(const tinyxml2::XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid) {
		_msgNumber = xml->UnsignedAttribute(VALUE_ATTRIBUTE, 0);
		_printer.messageManager().setCurrentMessage(_msgNumber);
	}
	return valid;
}

bool JetSetCurrentMessage::parseResponse(const tinyxml2::XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid) {
		parseCommandError(xml);
	}
	return valid;
}

/*********************************   SEND MESSAGE   *********************************/
JetSendMessage::JetSendMessage(Macsa::Printers::JetPrinter &printer, const Macsa::Printers::Message &message, const std::vector<char> &content, bool raw) :
	JetCommand(CMD_SEND_MESSAGE, printer),
	_message(message)
{
	_content = content;
	_raw = raw;
}

JetSendMessage::JetSendMessage(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_SEND_MESSAGE, printer),
	_message("")
{
	_content.clear();
	_raw = false;
}

void JetSendMessage::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, _message.number());
		cmd->SetAttribute(IS_XML_ATTRIBUTE, toString(_raw).c_str());
		if (!_raw){
			XMLDocument doc;
			if (doc.Parse(static_cast<char*>(_content.data()), _content.size())) {
				cmd->InsertEndChild(doc.RootElement());
			}
		}
		else {
			XMLElement* eBitmap = createChildNode(JET_BITMAP_TAG, &cmd);
			if (eBitmap) {
				const char* plainData = reinterpret_cast<const char*>(_content.data());
				int len = Base64encode_len(static_cast<int>(_content.size()));
				char* encodeData = new char[len + 1];
				if(encodeData) {
					Base64encode(encodeData, plainData, static_cast<int>(_content.size()));
					eBitmap->SetText(encodeData);
					delete[]  encodeData;
				}
			}
		}
	}
}

bool JetSendMessage::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	// ToDo - Server side
	return valid;
}

void JetSendMessage::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSendMessage::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	parseCommandError(xml);
	return valid;
}


/************************   RESET MESSAGES OF CURRENT GOUP   ************************/
JetResetCurrentGroup::JetResetCurrentGroup(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_RESET_MESSAGES, printer)
{}

bool JetResetCurrentGroup::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

bool JetResetCurrentGroup::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	parseCommandError(xml);
	return valid;
}

void JetResetCurrentGroup::buildRequest()
{
	newCommandWind();
}

void JetResetCurrentGroup::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

/******************************   GET GROUP MESSAGES   *****************************/
JetGetMessages::JetGetMessages(Macsa::Printers::JetPrinter &printer, const std::string &groupName) :
	JetCommand(CMD_GET_MESSAGES, printer)
{
	_group = groupName;
}

JetGetMessages::JetGetMessages(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_MESSAGES, printer)
{
	_group = "";
}

void JetGetMessages::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->Attribute(MESSAGE_GROUP_ATTRIBUTE, _group.c_str());
}

bool JetGetMessages::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	_group = getTextAttribute(xml, MESSAGE_GROUP_ATTRIBUTE, "");
	return valid;
}

void JetGetMessages::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	if (_error == Printers::nJetErrorCode::COMMAND_UNKOWN_ERROR)
	{
		std::vector<Printers::Message> messages = _printer.messageManager().messages(_group);
		if (messages.size()) {
			std::sort(messages.begin(), messages.end(),
					  [&](const Printers::Message& a, const Printers::Message& b){ return (a.number() > b.number()); }
			);
			for (auto& message : messages)
			{
				XMLElement* eMessage = createTextChildNode(JET_MESSAGE_TAG, message.name(), &cmd);
				eMessage->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, message.number());
			}
		}
		else
		{
			_error = Printers::nJetErrorCode::INVALID_MESSAGE_GROUP;
		}
	}
	setCommandError(_error);
}

bool JetGetMessages::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	_group = getTextAttribute(xml, MESSAGE_GROUP_ATTRIBUTE, "");
	parseCommandError(xml);
	if (_error == Printers::nJetErrorCode::COMMAND_OK) {
		_attributes.clear();
		_attributes.insert(std::pair<std::string, std::string>(MESSAGE_GROUP_ATTRIBUTE, _group));
		if (!_printer.messageManager().groupExist(_group)) {
			_printer.messageManager().addNewGroup(_group);
		}
		Printers::JetMessagesGroup* group = _printer.messageManager().group(_group);
		if (group){
			group->clear();
			for (const XMLElement* eMessage = xml->FirstChildElement(JET_MESSAGE_TAG);
				 eMessage != nullptr; eMessage = eMessage->NextSiblingElement(JET_MESSAGE_TAG))
			{
				const char * text = eMessage->GetText();
				if (text){
					std::string name = text;
					unsigned int num = eMessage->UnsignedAttribute(MESSAGE_NUMBER_ATTRIBUTE);
					group->addMessage(name, num);
				}
			}
		}
	}
	return valid;
}

/******************************   CREATE MESSAGES GROUP   *****************************/
JetCreateMessagesGroup::JetCreateMessagesGroup(Macsa::Printers::JetPrinter &printer, const std::string &groupName) :
	JetCommand(CMD_CREATE_MESSAGE_GROUP, printer)
{
	_group = groupName;
}

JetCreateMessagesGroup::JetCreateMessagesGroup(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_CREATE_MESSAGE_GROUP, printer)
{
	_group = "";
}

void JetCreateMessagesGroup::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->Attribute(MESSAGE_GROUP_ATTRIBUTE, _group.c_str());
}

bool JetCreateMessagesGroup::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	_group = getTextAttribute(xml, NAME_ATTRIBUTE, "");
	return valid;
}

void JetCreateMessagesGroup::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	cmd->Attribute(NAME_ATTRIBUTE, _group.c_str());
	setCommandError(_error);
}

bool JetCreateMessagesGroup::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	_group = getTextAttribute(xml, NAME_ATTRIBUTE, "");
	parseCommandError(xml);
	return valid;
}

/******************************   SEND MESSAGES TO GROUP   *****************************/
JetSendMessageGroup::JetSendMessageGroup(Macsa::Printers::JetPrinter &printer,
										 const std::string &groupName,
										 const Macsa::Printers::Message &message,
										 const std::vector<char> &content, bool raw) :
	JetCommand(CMD_SEND_MESSAGE_TO_GROUP, printer),
	_message(message)
{
	_group = groupName;
	_content = content;
	_raw = raw;
}

JetSendMessageGroup::JetSendMessageGroup(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_SEND_MESSAGE_TO_GROUP, printer),
	_message("")
{
	_group = "";
	_content.clear();
	_raw = false;
}

void JetSendMessageGroup::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		cmd->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, _message.number());
		cmd->SetAttribute(IS_XML_ATTRIBUTE, toString(_raw).c_str());
		cmd->SetAttribute(NAME_ATTRIBUTE, _group.c_str());
		if (!_raw){
			XMLDocument doc;
			if (doc.Parse(static_cast<char*>(_content.data()), _content.size())) {
				cmd->InsertEndChild(doc.RootElement());
			}
		}
		else {
			XMLElement* eBitmap = createChildNode(JET_BITMAP_TAG, &cmd);
			if (eBitmap) {
				const char* plainData = reinterpret_cast<const char*>(_content.data());
				int len = Base64encode_len(static_cast<int>(_content.size()));
				char* encodeData = new char[len + 1];
				if(encodeData) {
					Base64encode(encodeData, plainData, static_cast<int>(_content.size()));
					eBitmap->SetText(encodeData);
					delete[]  encodeData;
				}
			}
		}
	}
}

bool JetSendMessageGroup::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	// ToDo - Server side
	return valid;
}

void JetSendMessageGroup::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSendMessageGroup::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	parseCommandError(xml);
	return valid;
}


/******************************   DELETE MESSAGES GROUP   *****************************/
JetDeleteMessagesGroup::JetDeleteMessagesGroup(Macsa::Printers::JetPrinter &printer, const std::string &groupName) :
	JetCommand(CMD_DELETE_MESSAGE_GROUP, printer)
{
	_group = groupName;
}

JetDeleteMessagesGroup::JetDeleteMessagesGroup(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_DELETE_MESSAGE_GROUP, printer)
{
	_group = "";
}

void JetDeleteMessagesGroup::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->Attribute(MESSAGE_GROUP_ATTRIBUTE, _group.c_str());
}

bool JetDeleteMessagesGroup::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	_group = getTextAttribute(xml, NAME_ATTRIBUTE, "");
	return valid;
}

void JetDeleteMessagesGroup::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	cmd->Attribute(NAME_ATTRIBUTE, _group.c_str());
	setCommandError(_error);
}

bool JetDeleteMessagesGroup::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	_group = getTextAttribute(xml, NAME_ATTRIBUTE, "");
	parseCommandError(xml);
	return valid;
}
