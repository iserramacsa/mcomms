#ifndef MACSA_JETPROTOCOL_COMMAND_H
#define MACSA_JETPROTOCOL_COMMAND_H

#include <map>
#include "jet/jetprinter.h"
#include "xmlprotocol/xmlcommands.h"

namespace Macsa{
	namespace JetProtocol {
		///
		/// \brief The JetCommand class is the base class from jet protocol command.
		/// Based on a xml structure, this interface
		///
		class JetCommand : protected XMLCommand
		{
			public:
				JetCommand(const std::string& commandName, Printers::JetPrinter& printer);
				virtual ~JetCommand();

				virtual std::string getRequest();
				virtual std::string getResponse();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml) = 0;
				virtual bool parseResponse(const tinyxml2::XMLElement*xml) = 0;

				inline std::string commandName() const{ return _commandName;}
				inline Printers::JetErrorCode getError() const{ return _error;}
				void setError(const Printers::JetErrorCode &error);

				std::map<std::string, std::string> attributes() const;

			protected:
				std::map<std::string, std::string> _attributes;
				Printers::JetErrorCode _error;
				Printers::JetPrinter& _printer;

				virtual void buildRequest() = 0;
				virtual void buildResponse() = 0;

				tinyxml2::XMLElement * newCommandWind();
				bool isValidWind(const tinyxml2::XMLElement* xml);

				void setCommandError(const Printers::JetErrorCode &errorCode);
				void parseCommandError();

				virtual std::string toString(bool val) const;

			private:
				const std::string _commandName;
		};
	}
}

#endif // MACSA_JETPROTOCOL_COMMAND_H
