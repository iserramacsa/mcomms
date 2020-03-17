#ifndef MPROTOCOL_TOOLS_H
#define MPROTOCOL_TOOLS_H

#include <string>
#include "tinyxml2.h"
#include "tij/datatypes.h"

using namespace tinyxml2;

namespace Macsa {
	namespace MProtocol {
		namespace MTools {
				std::string toLower(std::string& str);
				std::string toLower(const std::string& str);
				std::string toUpper(std::string& str);
				std::string toUpper(const std::string& str);

				std::string toString(double value,int precision = 1);
				std::string toString(float value, int precision = 1);
				std::string toString(bool value);
				std::string toString(int value);
				std::string toString(unsigned value);

				inline const char* toCString(double value,int precision = 1) { return toString(value, precision).c_str(); }
				inline const char* toCString(float value, int precision = 1) { return toString(value, precision).c_str(); }
				inline const char* toCString(bool value)     { return toString(value).c_str(); }
				inline const char* toCString(int value)      { return toString(value).c_str(); }
				inline const char* toCString(unsigned value) { return toString(value).c_str(); }

				bool boolfromString(const std::string& value);
				bool isInRange(int val, int min, int max);
		}
	}
}

#endif
