#ifndef MPROTOCOL_TOOLS_H
#define MPROTOCOL_TOOLS_H

#include <string>
#include "tinyxml2.h"
#include "printer/datatypes.h"

using namespace tinyxml2;

namespace Macsa {
	namespace MProtocol {
		namespace MTools {

			namespace XML {
				int getWindId(const XMLElement* wind);
				bool isElement(const tinyxml2::XMLElement* element, const std::string& name);
				bool isSingleCommand(const tinyxml2::XMLElement* wind, const std::string& command);
				Printers::ErrorCode getWindError(const XMLElement* wind);
				void setWindError(XMLElement* wind, XMLDocument& doc, Printers::ErrorCode& error);
				XMLElement* newElement(const std::string name, XMLDocument& doc, XMLElement** parent = nullptr);
				XMLElement* newTextElement(const std::string name, const std::string content, XMLDocument& doc, XMLElement** parent = nullptr);
				XMLElement* newTextElement(const std::string name, int content, XMLDocument& doc, XMLElement** parent = nullptr);
				XMLElement* newTextElement(const std::string name, bool content, XMLDocument& doc, XMLElement** parent = nullptr);
				/*****************************************************************************************************/
				std::string textFromChild(const tinyxml2::XMLElement* parent, const std::string& childname);
				bool boolFromChild(const tinyxml2::XMLElement* parent, const std::string& childname);
				int intFromChild(const tinyxml2::XMLElement* parent, const std::string& childname);
			}

				std::string toLower(std::string& str);
				std::string toLower(const std::string& str);
				std::string toUpper(std::string& str);
				std::string toUpper(const std::string& str);

				std::string toString(double value,int precision = 1);
				std::string toString(float value, int precision = 1);
				std::string toString(bool value);

				std::string dateTime();
				time_t dateTime(const std::string &dt);

				bool boolfromString(const std::string& value);
				bool isInRange(int val, int min, int max);


		};
	}
}

#endif
