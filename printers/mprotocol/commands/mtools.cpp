#include "mtools.h"
#include <sstream>

using namespace Macsa::MProtocol;

XMLElement *MTools::newElement(const std::string name, XMLDocument &doc, XMLElement **parent)
{
	XMLElement* element = doc.NewElement(name.c_str());
	if(element != nullptr) {
		if(parent != nullptr && *parent != nullptr){
			(*parent)->InsertEndChild(element);
		}
	}

	return element;
}

XMLElement *MTools::newTextElement(const std::string name, const std::string content, XMLDocument &doc, XMLElement **parent)
{
	XMLElement* element = newElement(name, doc, parent);
	if(element != nullptr){
		element->SetText(content.c_str());
	}
	return element;
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

