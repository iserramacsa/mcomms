#include "jetprotocol/jetcounters.h"
#include "jetprotocol/jetprotocol.h"

#include <iostream>

using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;
using namespace tinyxml2;

//=============		Get Counters		=============//
JetGetCounters::JetGetCounters(JetPrinter &printer) :
	JetCommand(CMD_GET_COUNTERS, printer)
{}

JetGetCounters::~JetGetCounters()
{}

void JetGetCounters::buildRequest()
{
	newCommandWind();
}

bool JetGetCounters::parseRequest(const tinyxml2::XMLElement *xml)
{
	return isValidWind(xml);
}

bool JetGetCounters::parseResponse(const tinyxml2::XMLElement *xml)
{
	bool valid = isValidWind(xml);

	if (valid) {
		parseCommandError(xml);
		if (_error == nJetErrorCode::COMMAND_OK) {
			JetMessagesManager& manager = _printer.messageManager();
			std::vector<Message> messages = manager.messages(manager.currentGroup());
			std::map<unsigned int,unsigned int> counters;
			for (const XMLElement* eCounter = xml->FirstChildElement(JET_COUNTER_ITEM);
				 eCounter != nullptr; eCounter = eCounter->NextSiblingElement(JET_COUNTER_ITEM))
			{
				if (eCounter->FindAttribute(MESSAGE_ATTRIBUTE)){
					unsigned int num = eCounter->UnsignedAttribute(MESSAGE_ATTRIBUTE);
					unsigned int cnt = eCounter->UnsignedAttribute(VALUE_ATTRIBUTE);
					counters.insert(std::pair<unsigned int, unsigned int>(num, cnt));
				}
			}
			if (messages.size() == counters.size()) {
				for (std::vector<Message>::iterator mit = messages.begin(); mit != messages.end(); mit++) {
					std::map<unsigned int,unsigned int>::const_iterator cnt = counters.find(mit->number());
					if (cnt == counters.end()) {
						std::cout << "Invalid messages number" << std::endl;
						return  valid;
					}
					else {
						mit->setCounter(cnt->second);
					}
				}
				for (std::vector<Message>::const_iterator it = messages.begin(); it != messages.end(); it++) {
					manager.setMessageCounter(it->number(), it->counter());
				}
			}
			else {
				std::cout << "Invalid messages list" << std::endl;
			}
		}
	}

	return valid;
}

void JetGetCounters::buildResponse()
{
	XMLElement * cmd = newCommandWind();
	if (cmd) {
		JetMessagesManager& manager = _printer.messageManager();
		std::vector<Message> messages = manager.messages(manager.currentGroup());
		for (std::vector<Message>::const_iterator message = messages.begin(); message != messages.end(); message++) {
			XMLElement* item = createChildNode(JET_COUNTER_ITEM, &cmd);
			if (item) {
				item->SetAttribute(MESSAGE_ATTRIBUTE, message->number());
				item->SetAttribute(VALUE_ATTRIBUTE, message->counter());
			}
		}
		setCommandError(nJetErrorCode::COMMAND_OK);
	}
}

//=============		Set Counters		=============//
JetSetCounters::JetSetCounters(JetPrinter &printer, std::map<unsigned int, unsigned int> counters) :
	JetCommand(CMD_SET_COUNTERS, printer)
{
	_counters = counters;
}

JetSetCounters::JetSetCounters(JetPrinter &printer) :
	JetCommand(CMD_SET_COUNTERS, printer)
{
	_counters.clear();
}

JetSetCounters::~JetSetCounters()
{}

void JetSetCounters::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	if (cmd) {
		for (auto& msg : _counters) {
			XMLElement* eMsgCounter = createChildNode(JET_COUNTER_ITEM_UPPERCASE, &cmd);
			if (eMsgCounter) {
				eMsgCounter->SetAttribute(MESSAGE_ATTRIBUTE, msg.first);
				eMsgCounter->SetAttribute(VALUE_ATTRIBUTE, msg.second);
			}
		}
	}
}

bool JetSetCounters::parseRequest(const tinyxml2::XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		JetMessagesManager& manager = _printer.messageManager();
		std::vector<Message> messages = manager.messages(manager.currentGroup());
		std::map<unsigned int,unsigned int> counters;
		for (const XMLElement* eCounter = xml->FirstChildElement(JET_COUNTER_ITEM_UPPERCASE);
			 eCounter != nullptr; eCounter = eCounter->NextSiblingElement(JET_COUNTER_ITEM_UPPERCASE))
		{
			if (eCounter->FindAttribute(MESSAGE_ATTRIBUTE)){
				unsigned int num = eCounter->UnsignedAttribute(MESSAGE_ATTRIBUTE);
				unsigned int cnt = eCounter->UnsignedAttribute(VALUE_ATTRIBUTE);
				counters.insert(std::pair<unsigned int, unsigned int>(num, cnt));
			}
		}
		if (messages.size() == counters.size()) {
			for (std::vector<Message>::iterator mit = messages.begin(); mit != messages.end(); mit++) {
				std::map<unsigned int,unsigned int>::const_iterator cnt = counters.find(mit->number());
				if (cnt == counters.end()) {

					std::cout << "Invalid messages number" << std::endl;
					return  valid;
				}
				else {
					mit->setCounter(cnt->second);
				}
			}
			for (std::vector<Message>::const_iterator it = messages.begin(); it != messages.end(); it++) {
				manager.setMessageCounter(it->number(), it->counter());
			}
		}
		else {
			std::cout << "Invalid messages list" << std::endl;
		}
	}
	return valid;
}

void JetSetCounters::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSetCounters::parseResponse(const tinyxml2::XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError(xml);
	}
	return valid;
}

//=============		Reset Counters		=============//
JetResetCounters::JetResetCounters(JetPrinter &printer) :
	JetCommand(CMD_RESET_COUNTERS, printer)
{}

JetResetCounters::~JetResetCounters()
{}

void JetResetCounters::buildRequest()
{
	newCommandWind();
}

bool JetResetCounters::parseRequest(const tinyxml2::XMLElement *xml)
{
	return isValidWind(xml);
}

void JetResetCounters::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetResetCounters::parseResponse(const tinyxml2::XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError(xml);
	}
	return valid;
}
