#ifndef  MACSA_JetProtocol_COMMANDS_MESSAGE_VALUES_H
#define  MACSA_JetProtocol_COMMANDS_MESSAGE_VALUES_H

#include "jetcommand.h"
#include <string>
#include <map>
#include "nisx/counter.h"
#include "nisx/datetime.h"

namespace Macsa {
	namespace JetProtocol {
		/**
		 * @brief The JetSetMessageVariable
		 */
		class JetSetMessageVariable : public JetCommand
		{
			public:
				JetSetMessageVariable(Printers::JetPrinter& printer, unsigned int filenum, const std::string& variable, const std::string& value);
				JetSetMessageVariable(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				unsigned int _filenum;
				std::string _variable;
				std::string _value;

				virtual void buildRequest();
				virtual void buildResponse();

		};

		/**
		 * @brief The JetSetMessageVariables
		 */
		class JetSetMessageVariables : public JetCommand
		{
			public:
				JetSetMessageVariables(Printers::JetPrinter& printer, unsigned int filenum, const std::map<std::string, std::string>& values);
				JetSetMessageVariables(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				unsigned int _filenum;
				std::map<std::string, std::string> _values;

				virtual void buildRequest();
				virtual void buildResponse();

		};

		/**
		 * @brief The JetGetMessageUserFields
		 */
		class JetGetMessageUserFields : public JetCommand
		{
			public:
				JetGetMessageUserFields(Printers::JetPrinter& printer, unsigned int filenum, const std::string& group="");
				JetGetMessageUserFields(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				unsigned int _filenum;
				std::string _group;

				virtual void buildRequest();
				virtual void buildResponse();

		};

		/**
		 * @brief The JetSetMessageUserFields
		 */
		class JetSetMessageUserFields : public JetCommand
		{
			public:
				JetSetMessageUserFields(Printers::JetPrinter& printer, unsigned int filenum, const std::map<std::string, std::string>& uiFields, const std::string& group="");
				JetSetMessageUserFields(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				unsigned int _filenum;
				std::string _group;
				std::map<std::string, std::string> _uiFields;

				virtual void buildRequest();
				virtual void buildResponse();

		};
	}
}

#endif // MACSA_JetProtocol_COMMANDS_MESSAGE_VALUES_H
