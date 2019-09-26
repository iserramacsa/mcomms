#ifndef MPROTOCOL_TOOLS_H
#define MPROTOCOL_TOOLS_H

#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace Macsa {
	namespace MProtocol {
		namespace MTools {

				XMLElement* newElement(const std::string name, XMLDocument& doc, XMLElement** parent = nullptr);
				XMLElement* newTextElement(const std::string name, const std::string content, XMLDocument& doc, XMLElement** parent = nullptr);

				std::string toLower(std::string& str);
				std::string toLower(const std::string& str);
				std::string toUpper(std::string& str);
				std::string toUpper(const std::string& str);

				std::string toString(double value,int precision = 1);
				std::string toString(float value, int precision = 1);
				std::string toString(bool value);

				bool boolfromString(const std::string& value);
				bool isInRange(int val, int min, int max);
		};
	}
}

#endif
