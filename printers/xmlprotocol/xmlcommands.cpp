#include "xmlprotocol/xmlcommands.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace Macsa;
using namespace tinyxml2;

XMLCommand::XMLCommand()
{
	_doc.Clear();
}

XMLCommand::~XMLCommand()
{}

std::string XMLCommand::getTextFromChildNode(const XMLElement *parent, const std::string &child, const std::string &defaultValue) const
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

bool XMLCommand::getBoolFromChildNode(const XMLElement *parent, const std::string &child, bool defaultValue) const
{
	bool value = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
			value = strToBool(node->GetText());
		}
	}
	return value;
}

int XMLCommand::getIntFromChildNode(const XMLElement *parent, const std::string &child, int defaultValue) const
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

unsigned XMLCommand::getUnsignedFromChildNode(const XMLElement *parent, const std::string &child, unsigned defaultValue) const
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

double XMLCommand::getDoubleFromChildNode(const XMLElement *parent, const std::string &child, double defaultValue) const
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

std::string XMLCommand::getTextAttribute(const XMLElement *element, const std::string &attribute, const std::string &defaultValue) const
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

bool XMLCommand::getBoolAttribute(const XMLElement *element, const std::string &attribute, bool defaultValue) const
{
	std::string def = toString (defaultValue);
	return strToBool(getTextAttribute(element, attribute, def));
}

XMLElement *XMLCommand::createChildNode(const std::string &child, XMLElement **parent)
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

XMLElement *XMLCommand::createTextChildNode(const std::string &child, const std::string &text, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(text.c_str());
	}
	return node;
}

XMLElement *XMLCommand::createBoolTextChildNode(const std::string &child, bool value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(toString(value).c_str());
	}
	return node;
}

XMLElement *XMLCommand::createIntTextChildNode(const std::string &child, int value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(toString(value).c_str());
	}
	return node;
}

XMLElement *XMLCommand::createUnsignedTextChildNode(const std::string &child, unsigned value, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(toString(value).c_str());
	}
	return node;
}

XMLElement *XMLCommand::createDoubleTextChildNode(const std::string &child, double value, unsigned precision, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(toString(value, static_cast<int>(precision)).c_str());
	}
	return node;
}

std::string XMLCommand::toString()
{
	XMLPrinter p;
	_doc.Print(&p);
	return p.CStr();
}

std::string XMLCommand::toLower(std::string &str) const
{
	for (std::string::iterator c = str.begin(); c != str.end(); c++){
		*c = static_cast<char>(std::tolower(*c));
	}
	return str;
}

std::string XMLCommand::toLower(const std::string &str) const
{
	std::string s = str;
	for (std::string::iterator c = s.begin(); c != s.end(); c++){
		*c = static_cast<char>(std::tolower(*c));
	}
	return s;
}

std::string XMLCommand::toUpper(std::string &str) const
{
	for (std::string::iterator c = str.begin(); c != str.end(); c++){
		*c = static_cast<char>(std::toupper(*c));
	}
	return str;
}

std::string XMLCommand::toUpper(const std::string &str) const
{
	std::string s = str;
	for (std::string::iterator c = s.begin(); c != s.end(); c++){
		*c = static_cast<char>(std::toupper(*c));
	}
	return s;
}

bool XMLCommand::strToBool(const std::string &str) const
{
	return (toLower(str).compare("true") == 0);
}

std::string XMLCommand::toString(bool val) const
{
	return (val ? "true" : "false");
}

std::string XMLCommand::toString(int value) const
{
	std::stringstream s;
	s  << value;
	return s.str();
}

std::string XMLCommand::toString(unsigned int value) const
{
	std::stringstream s;
	s  << value;
	return s.str();
}

std::string XMLCommand::toString(float value, int precision) const
{
	std::stringstream s;
	s.precision(precision);
	s << std::fixed << value;
	return s.str();

}

std::string XMLCommand::toString(double value, int precision) const
{
	std::stringstream s;
	s.precision(precision);
	s << std::fixed << value;
	return s.str();

}


