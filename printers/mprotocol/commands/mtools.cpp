#include "mtools.h"
#include "mprotocol/mprotocol.h"
#include <iomanip>
#include <sstream>

using namespace Macsa::MProtocol;

int MTools::XML::getWindId(const XMLElement *wind)
{
	int id = -1;
	if (isElement(wind, MWIND)) {
		wind->QueryIntAttribute(MWIND_ID_ATTR, &id);
	}

	return id;
}

bool MTools::XML::isElement(const XMLElement *element, const std::string &name)
{
	return (element != nullptr && element->ToElement() != nullptr && name.compare(element->Name()) == 0);
}

bool MTools::XML::isSingleCommand(const XMLElement *wind, const std::string &command)
{
	if (isElement(wind, MWIND)) {
		const XMLElement *cmd = wind->FirstChildElement(command.c_str());
		return (cmd != nullptr && cmd->NoChildren());
	}
	return false;
}

Macsa::Printers::ErrorCode MTools::XML::getWindError(const XMLElement *wind)
{
	//<ERROR Code="Error Code"/>
	Printers::ErrorCode err;
	err = Printers::ErrorCode_n::UNKOWN_ERROR;

	if (isElement(wind, MWIND)) {
		const XMLElement* windError = wind->FirstChildElement(MERROR);
		std::string errorcode = windError->Attribute(MERROR_CODE_ATTR, err.toString().c_str());
		err = errorcode;
	}

	return err;
}

void MTools::XML::setWindError(XMLElement *wind, XMLDocument &doc, Macsa::Printers::ErrorCode &error)
{
	if (isElement(wind, MWIND)) {
		XMLElement* windError = doc.NewElement(MERROR);
		windError->SetAttribute(MERROR_CODE_ATTR, error.toString().c_str());
		wind->InsertFirstChild(windError);
	}
}


XMLElement *MTools::XML::newElement(const std::string name, XMLDocument &doc, XMLElement **parent)
{
	XMLElement* element = doc.NewElement(name.c_str());
	if(element != nullptr) {
		if(parent != nullptr && *parent != nullptr){
			(*parent)->InsertEndChild(element);
		}
	}

	return element;
}

XMLElement *MTools::XML::newTextElement(const std::string name, const std::string content, XMLDocument &doc, XMLElement **parent)
{
	XMLElement* element = newElement(name, doc, parent);
	if(element != nullptr){
		element->SetText(content.c_str());
	}
	return element;
}

XMLElement *MTools::XML::newTextElement(const std::string name, int content, XMLDocument &doc, XMLElement **parent)
{
	XMLElement* element = newElement(name, doc, parent);
	if(element != nullptr){
		element->SetText(content);
	}
	return element;
}

XMLElement *MTools::XML::newTextElement(const std::string name, bool content, XMLDocument &doc, XMLElement **parent)
{
	XMLElement* element = newElement(name, doc, parent);
	if(element != nullptr){
		element->SetText(toString(content).c_str());
	}
	return element;
}

std::string MTools::XML::textFromChild(const XMLElement *parent, const std::string &childname)
{
	std::string text = "";
	if (parent)
	{
		const XMLElement * child = parent->FirstChildElement(childname.c_str());
		if (child)
		{
			text = child->GetText();
		}
	}
	return text;
}

bool MTools::XML::boolFromChild(const XMLElement *parent, const std::string &childname)
{
	std::string val = textFromChild(parent, childname);
	return boolfromString(val);
}

int MTools::XML::intFromChild(const XMLElement *parent, const std::string &childname)
{
	std::string val = textFromChild(parent, childname);
	if (val.length()){
		int i = atoi(val.c_str());
		return i;
	}
	return 0;
}

std::string MTools::toLower(std::string &str)
{
	for (std::string::iterator c = str.begin(); c != str.end(); c++){
		*c = static_cast<char>(std::tolower(*c));
	}
	return str;
}

std::string MTools::toLower(const std::string &str)
{
	std::string s = str;
	for (std::string::iterator c = s.begin(); c != s.end(); c++){
		*c = static_cast<char>(std::tolower(*c));
	}
	return s;
}

std::string MTools::toUpper(std::string &str)
{
	for (std::string::iterator c = str.begin(); c != str.end(); c++){
		*c = static_cast<char>(std::toupper(*c));
	}
	return str;
}

std::string MTools::toUpper(const std::string &str)
{
	std::string s = str;
	for (std::string::iterator c = s.begin(); c != s.end(); c++){
		*c = static_cast<char>(std::toupper(*c));
	}
	return s;
}

std::string MTools::toString(double value, int precision)
{
	std::stringstream s;
	s.precision(precision);
	s << std::fixed << value;
	return s.str();
}

std::string MTools::toString(float value, int precision)
{
	std::stringstream s;
	s.precision(precision);
	s << std::fixed << value;
	return s.str();
}

std::string MTools::toString(bool value)
{
	return (value ? "true" : "false");
}

bool MTools::boolfromString(const std::string &value)
{
	return (toLower(value).compare("true") == 0);
}

bool MTools::isInRange(int val, int min, int max)
{
	return ((val >= min) && (val <= max));
}


std::string MTools::dateTime()
{
	time_t t1 = ::time(nullptr);
	struct tm *t2 = localtime(&t1);

	std::stringstream dt;
	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_mday;
	dt <<  std::setfill ('0') << std::setw(2) << (t2->tm_mon + 1);
	dt <<  std::setfill ('0') << std::setw(4) << (t2->tm_year + 1900);

	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_hour;
	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_min;
	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_sec;

	return dt.str();
}

time_t MTools::dateTime(const std::string &dt)
{
	time_t rawtime;
	struct tm * timeInfo;

	time(&rawtime);
	timeInfo = localtime(&rawtime);

	if (dt.length() == 14)
	{
		timeInfo->tm_mday = std::atoi(dt.substr(0, 2).c_str());
		timeInfo->tm_mon  = std::atoi(dt.substr(2, 2).c_str()) - 1;
		timeInfo->tm_year = std::atoi(dt.substr(4, 4).c_str()) - 1900;
		timeInfo->tm_hour = std::atoi(dt.substr(8, 2).c_str());
		timeInfo->tm_min  = std::atoi(dt.substr(10, 2).c_str());
		timeInfo->tm_sec  = std::atoi(dt.substr(12, 2).c_str());
		return mktime(timeInfo);
	}
	return rawtime;
}
