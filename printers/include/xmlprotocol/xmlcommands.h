#ifndef MACSA_XML_COMMANDS_H
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

			virtual std::string getRequest(uint32_t id = 0) = 0;
			virtual std::string getResponse() = 0;
			virtual bool parseRequest(const tinyxml2::XMLElement* xml) = 0;
			virtual bool parseResponse(const tinyxml2::XMLElement*xml) = 0;

			std::string getTextFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, const std::string& defaultValue="") const;
			bool        getBoolFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, bool defaultValue = false) const;
			bool		getBoolFromChildNodeAttribute(const tinyxml2::XMLElement *parent, const std::string &child, const std::string &attribute, bool defaultValue = false) const;
			int         getIntFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, int defaultValue = 0) const;
			unsigned    getUnsignedFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, unsigned defaultValue = 0)const;
			unsigned    getUnsignedFromChildNodeAttribute(const tinyxml2::XMLElement *parent, const std::string &child, const std::string &attribute, unsigned defaultValue = 0)const;
			double      getDoubleFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, double defaultValue = 0.0)const;
			std::string getTextFromChildNodeAttribute(const tinyxml2::XMLElement *parent, const std::string &child, const std::string &attribute, const std::string & defaultValue = "")const;


			std::string getTextAttribute(const tinyxml2::XMLElement *element,const std::string &attribute, const std::string &defaultValue = "") const;
			bool        getBoolAttribute(const tinyxml2::XMLElement *element,const std::string &attribute, bool defaultValue = false) const;

			std::string  getChildAttribute(const tinyxml2::XMLElement *element, const std::string &child, const std::string &attribute, const std::string &defaultValue = "") const;
			int			 getChildAttribute(const tinyxml2::XMLElement *element, const std::string &child, const std::string &attribute, int defaultValue = 0) const;
			unsigned int getChildAttribute(const tinyxml2::XMLElement *element, const std::string &child, const std::string &attribute, unsigned int defaultValue = 0) const;
			double		 getChildAttribute(const tinyxml2::XMLElement *element, const std::string &child, const std::string &attribute, double defaultValue = 0, int precision = 0) const;
			bool		 getChildAttribute(const tinyxml2::XMLElement *element, const std::string &child, const std::string &attribute, bool defaultValue = false) const;


			tinyxml2::XMLElement * createChildNode(const std::string &child, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createTextChildNode(const std::string &child, const std::string& text, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createBoolTextChildNode(const std::string &child, bool value, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createIntTextChildNode(const std::string &child, int value, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createUnsignedTextChildNode(const std::string &child, unsigned value, tinyxml2::XMLElement **parent);
			tinyxml2::XMLElement * createDoubleTextChildNode(const std::string &child, double value, unsigned precision, tinyxml2::XMLElement **parent);

			virtual std::string toString(); //return current xml document in a std::string

			std::string toLower(std::string &str) const;
			std::string toLower(const std::string &str) const;
			std::string toUpper(std::string &str) const;
			std::string toUpper(const std::string &str) const;

			virtual bool strToBool(const std::string& str) const;

			virtual std::string toString(bool val) const;
			virtual std::string toString(int value) const;
			virtual std::string toString(unsigned int value) const;
			virtual std::string toString(uint64_t value) const;
			virtual std::string toString(float value, int precision) const;
			virtual std::string toString(double value, int precision) const;

		protected:
			tinyxml2::XMLDocument _doc;

			virtual void buildRequest() = 0;
			virtual void buildResponse() = 0;
	};
}

#endif // MACSA_XML_COMMANDS_H
