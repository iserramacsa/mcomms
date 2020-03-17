﻿#ifndef MACSA_XML_COMMANDS_H
#define MACSA_XML_COMMANDS_H

#include <cstdint>
#include <string>
#include <tinyxml2.h>

namespace Macsa{
	///
	/// \brief XMLCommand
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

			std::string toString(); //return current xml document in a std::string

			std::string toLower(std::string &str) const;
			std::string toLower(const std::string &str) const;
			std::string toUpper(std::string &str) const;
			std::string toUpper(const std::string &str) const;

			virtual bool strToBool(const std::string& str) const;

			virtual std::string toString(bool val) const;
			virtual std::string toString(int value) const;
			virtual std::string toString(unsigned int value) const;
			virtual std::string toString(float value, int precision) const;
			virtual std::string toString(double value, int precision) const;

		protected:
			tinyxml2::XMLDocument _doc;
	};
}

#endif // MACSA_XML_COMMANDS_H
