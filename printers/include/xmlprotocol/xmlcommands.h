#ifndef MACSA_XML_COMMANDS_H
#define MACSA_XML_COMMANDS_H

#include <cstdint>
#include <string>
#include <tinyxml2.h>

namespace Macsa{
	///
	/// \brief The JetCommand class is the base class from MProtocol command.
	/// Based on a xml structure, this interface
	///
	class XMLCommand
	{
		public:
			XMLCommand();
			virtual ~XMLCommand();

			std::string getTextFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, const std::string& defaultValue="") const;
			bool        getBoolFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, bool defaultValue = false) const;
			int         getIntFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, int defaultValue = 0) const;
			unsigned    getUnsignedFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, unsigned defaultValue = 0)const;
			double      getDoubleFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, double defaultValue = 0.0)const;

			std::string getTextAttribute(const tinyxml2::XMLElement *element,const std::string &attribute, const std::string &defaultValue = "") const;
			bool        getBoolAttribute(const tinyxml2::XMLElement *element,const std::string &attribute, bool defaultValue = false) const;

			tinyxml2::XMLElement * createChildNode(const std::string &child, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createTextChildNode(const std::string &child, const std::string& text, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createBoolTextChildNode(const std::string &child, bool value, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createIntTextChildNode(const std::string &child, int value, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createUnsignedTextChildNode(const std::string &child, unsigned value, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createDoubleTextChildNode(const std::string &child, double value, unsigned precision, tinyxml2::XMLElement **parent);
	};
}

#endif // MACSA_XML_COMMANDS_H
