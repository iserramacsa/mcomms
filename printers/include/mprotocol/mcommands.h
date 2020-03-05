#ifndef MACSA_MPROTOCOL_COMMANDS_H
#define MACSA_MPROTOCOL_COMMANDS_H

#include <cstdint>
#include <string>
#include <tinyxml2.h>
#include <map>
#include "printer/datatypes.h"
#include "tij/tijprinter.h"

namespace Macsa{
	namespace MProtocol {
		///
		/// \brief The MCommand class is the base class from MProtocol command.
		/// Based on a xml structure, this interface
		///
		class MCommand
		{
			public:
				MCommand(const std::string& commandName, Printers::TijPrinter& printer);
				virtual ~MCommand();

				virtual std::string getRequest(uint32_t windId);
				virtual std::string getResponse();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml) = 0;
				virtual bool parseResponse(const tinyxml2::XMLElement*xml) = 0;

				inline std::string commandName() const{ return _commandName;}
				inline uint32_t id() const{ return _id;}
				inline Printers::ErrorCode getError() const{ return _error;}
				void setError(const Printers::ErrorCode &error);


				std::map<std::string, std::string> attributes() const;

			protected:
				uint32_t _id;
				std::map<std::string, std::string> _attributes;
				tinyxml2::XMLDocument _doc;
				Printers::ErrorCode _error;
				Printers::TijPrinter& _printer;

				virtual void buildRequest() = 0;
				virtual void buildResponse() = 0;


				std::string toString(); //return current xml document in a std::string
				tinyxml2::XMLElement * newCommandNode();

			private:
				tinyxml2::XMLElement * buildNewFrame();
				const std::string _commandName;

				int getWindId(const tinyxml2::XMLElement *wind) const;

			//Tools
			protected:
				const tinyxml2::XMLElement * getCommand(const tinyxml2::XMLElement *wind, unsigned int &windId) const;
				Printers::ErrorCode getCommandError(const tinyxml2::XMLElement *wind) const;
				std::string getTextFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, const std::string& defaultValue="") const;
				bool getBoolFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, bool defaultValue = false) const;
				int getIntFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, int defaultValue = 0) const;
				unsigned getUnsignedFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, unsigned defaultValue = 0)const;
				double getDoubleFromChildNode(const tinyxml2::XMLElement *parent, const std::string &child, double defaultValue = 0.0)const;

				std::string getTextAttribute(const tinyxml2::XMLElement *element,const std::string &attribute, const std::string &defaultValue = "") const;
				bool getBoolAttribute(const tinyxml2::XMLElement *element,const std::string &attribute, bool defaultValue = false) const;

				tinyxml2::XMLElement * createChildNode(const std::string &child, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement * createTextChildNode(const std::string &child, const std::string& text, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement * createBoolTextChildNode(const std::string &child, bool value, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement * createIntTextChildNode(const std::string &child, int value, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement * createUnsignedTextChildNode(const std::string &child, unsigned value, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement * createDoubleTextChildNode(const std::string &child, double value, unsigned precision, tinyxml2::XMLElement **parent);
				void addWindError(const Printers::ErrorCode& errorCode);

		};
	}
}

#endif // MPROTOCOLCOMMANDS_H
