#include "mprotocol/mcommands.h"
#include "mprotocol/mprotocol.h"
#include "mtools.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Macsa;
using namespace Macsa::MProtocol;
using namespace tinyxml2;

MCommand::MCommand(const std::string& commandName, Printers::TIJPrinter &printer):
	_printer(printer),
	_commandName(commandName)
{}

MCommand::~MCommand()
{}

std::string MCommand::getRequest(uint32_t windId)
{
	_id = windId;
	buildRequest();
	return toString();
}

std::string MCommand::getResponse()
{
	buildResponse();
	return toString();
}

void MCommand::setError(const Printers::ErrorCode &error)
{
	_error = error;
}

std::string MCommand::toString()
{
	XMLPrinter p;
	_doc.Print(&p);
	return p.CStr();
}

XMLElement *MCommand::newCommandNode()
{
	XMLElement * wind = buildNewFrame();
	XMLElement* cmd = nullptr;
	if (wind != nullptr) {
		cmd = _doc.NewElement(_commandName.c_str());
		if(cmd != nullptr) {
			wind->InsertEndChild(cmd);
		}
	}

	return cmd;
}

XMLElement *MCommand::buildNewFrame()
{
	if (_doc.RootElement() != nullptr) {
		_doc.Clear();
	}
	XMLElement* wind = _doc.NewElement(MWIND);
	int id = static_cast<int>(_id);
	wind->SetAttribute(MWIND_ID_ATTR, id);
	_doc.InsertEndChild(wind);
	return _doc.RootElement();
}

/********************************************************************************/
/*								XML Tools										*/
/********************************************************************************/
int MCommand::getWindId(const XMLElement *wind) const
{
	int id = -1;

	if (wind != nullptr && std::string(wind->Name()).compare(MWIND) == 0) {
		wind->QueryIntAttribute(MWIND_ID_ATTR, &id);
	}

	return id;
}

const XMLElement *MCommand::getCommand(const XMLElement *wind, unsigned int& windId) const
{
	const XMLElement * cmd = nullptr;
	if (wind != nullptr){
		int id = getWindId(wind);
		if (id != -1){
			windId = static_cast<unsigned int>(id);
			cmd = wind->FirstChildElement(_commandName.c_str());
		}
	}
	return cmd;
}

Printers::ErrorCode MCommand::getCommandError(const XMLElement *wind) const
{
	Printers::ErrorCode err;
	err = Printers::ErrorCode_n::UNKOWN_ERROR;
	if (wind != nullptr){
		const XMLElement* error = wind->FirstChildElement(MERROR);
		if (error != nullptr) {
			err = getTextAttribute(error, ATTRIBUTE_CODE, err.toString().c_str());
		}
	}
	return err;
}

std::string MCommand::getTextFromChildNode(const XMLElement *parent, const std::string &child, const std::string &defaultValue) const
{
	std::string text = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
			text = (node->GetText() != nullptr) ? node->GetText() : "";
		}
	}
	return text;
}

bool MCommand::getBoolFromChildNode(const XMLElement *parent, const std::string &child, bool defaultValue) const
{
	bool value = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
			value = MTools::boolfromString(node->GetText());
		}
	}
	return value;
}

int MCommand::getIntFromChildNode(const XMLElement *parent, const std::string &child, int defaultValue) const
{
	int value = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
			std::string text = node->GetText();
			if (text.length()) {
				value = std::atoi(text.c_str());
			}
		}
	}
	return value;
}

unsigned MCommand::getUnsignedFromChildNode(const XMLElement *parent, const std::string &child, unsigned defaultValue) const
{
	unsigned value = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
			std::string text = node->GetText();
			if (text.length()) {
				value = static_cast<unsigned>(std::atoi(text.c_str()));
			}
		}
	}
	return value;
}

double MCommand::getDoubleFromChildNode(const XMLElement *parent, const std::string &child, double defaultValue) const
{
	double value = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
			std::string text = node->GetText();
			if (text.length()) {
				char* pEnd;
				value = std::strtod(text.c_str(), &pEnd);
			}
		}
	}
	return value;
}

std::string MCommand::getTextAttribute(const XMLElement *element, const std::string &attribute, const std::string &defaultValue) const
{
	std::string value = defaultValue;
	if(element != nullptr && !attribute.empty()) {
		const XMLAttribute* attr = element->FindAttribute(attribute.c_str());
		if (attr != nullptr) {
			value = attr->Value();
		}
	}
	return value;
}

bool MCommand::getBoolAttribute(const XMLElement *element, const std::string &attribute, bool defaultValue) const
{
	std::string def = MTools::toString (defaultValue);
	return MTools::boolfromString (getTextAttribute(element, attribute, def));
}

XMLElement *MCommand::createChildNode(const std::string &child, XMLElement **parent)
{
	XMLElement * node = (*parent)->FirstChildElement(child.c_str());
	if (node == nullptr){
		node = _doc.NewElement(child.c_str());
		if (parent != nullptr && *parent != nullptr){
			(*parent)->InsertEndChild(node);
		}
	}

	return node;
}

XMLElement *MCommand::createTextChildNode(const std::string &child, const std::string &text, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(text.c_str());
	}
	return node;
}

XMLElement *MCommand::createBoolTextChildNode(const std::string &child, bool value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(MTools::toString(value).c_str());
	}
	return node;
}

XMLElement *MCommand::createIntTextChildNode(const std::string &child, int value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(MTools::toString(value).c_str());
	}
	return node;
}

XMLElement *MCommand::createUnsignedTextChildNode(const std::string &child, unsigned value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(MTools::toString(value).c_str());
	}
	return node;
}

XMLElement *MCommand::createDoubleTextChildNode(const std::string &child, double value, unsigned precision, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(MTools::toString(value, static_cast<int>(precision)).c_str());
	}
	return node;
}

void MCommand::addWindError(const Printers::ErrorCode &errorCode)
{
	XMLElement* wind = _doc.FirstChildElement(MWIND);
	if (wind != nullptr) {
		XMLElement* error = createChildNode(MERROR, &wind);
		if (error != nullptr) {
			error->SetAttribute(ATTRIBUTE_CODE, errorCode.toString().c_str());
			wind->InsertFirstChild(error);
		}
	}
}

