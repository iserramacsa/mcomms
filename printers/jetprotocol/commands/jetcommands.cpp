#include "jetprotocol/jetcommands.h"
#include "jetprotocol/jetprotocol.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetCommand::JetCommand(const std::string& commandName, Printers::JetPrinter &printer):
	_printer(printer),
	_commandName(commandName)
{
	_attributes.clear();
}

JetCommand::~JetCommand()
{}

std::string JetCommand::getRequest()
{
	buildRequest();
	return toString();
}

std::string JetCommand::getResponse()
{
	buildResponse();
	return toString();
}

void JetCommand::setError(const Printers::ErrorCode &error)
{
	_error = error;
}

std::map<std::string, std::string> JetCommand::attributes() const
{
    return _attributes;
}

std::string JetCommand::toString()
{
    XMLPrinter p;
    _doc.Print(&p);
    return p.CStr();
}

XMLElement *JetCommand::newCommandWind()
{
	if (_doc.RootElement() != nullptr) {
		_doc.Clear();
	}
	XMLElement* wind = _doc.NewElement(JETWIND);
	wind->SetAttribute(COMMAND_ATTRIBUTE, _commandName.c_str());
	_doc.InsertEndChild(wind);
	return _doc.RootElement();
}

/********************************************************************************/
/*								XML Tools										*/
/********************************************************************************/
std::string JetCommand::getTextFromChildNode(const XMLElement *parent, const std::string &child, const std::string &defaultValue) const
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

bool JetCommand::getBoolFromChildNode(const XMLElement *parent, const std::string &child, bool defaultValue) const
{
	bool value = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
//			value = MTools::boolfromString(node->GetText());
		}
	}
	return value;
}

int JetCommand::getIntFromChildNode(const XMLElement *parent, const std::string &child, int defaultValue) const
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

unsigned JetCommand::getUnsignedFromChildNode(const XMLElement *parent, const std::string &child, unsigned defaultValue) const
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

double JetCommand::getDoubleFromChildNode(const XMLElement *parent, const std::string &child, double defaultValue) const
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

std::string JetCommand::getTextAttribute(const XMLElement *element, const std::string &attribute, const std::string &defaultValue) const
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

bool JetCommand::getBoolAttribute(const XMLElement *element, const std::string &attribute, bool defaultValue) const
{
	//std::string def = MTools::toString (defaultValue);
	//return MTools::boolfromString (getTextAttribute(element, attribute, def));
	return false;
}

XMLElement *JetCommand::createChildNode(const std::string &child, XMLElement **parent)
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

XMLElement *JetCommand::createTextChildNode(const std::string &child, const std::string &text, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(text.c_str());
	}
	return node;
}

XMLElement *JetCommand::createBoolTextChildNode(const std::string &child, bool value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
//		node->SetText(MTools::toString(value).c_str());
	}
	return node;
}

XMLElement *JetCommand::createIntTextChildNode(const std::string &child, int value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
//		node->SetText(MTools::toString(value).c_str());
	}
	return node;
}

XMLElement *JetCommand::createUnsignedTextChildNode(const std::string &child, unsigned value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
//		node->SetText(MTools::toString(value).c_str());
	}
	return node;
}

XMLElement *JetCommand::createDoubleTextChildNode(const std::string &child, double value, unsigned precision, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
//		node->SetText(MTools::toString(value, static_cast<int>(precision)).c_str());
	}
	return node;
}

void JetCommand::addWindError(const Printers::ErrorCode &errorCode)
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

