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
		class JetCommand : public XMLCommand
		{
			public:
				JetCommand(const std::string& commandName, Printers::JetPrinter& printer);
				virtual ~JetCommand() override;

				///
				/// \brief getRequest. Herited methods to get the jetCommand request
				/// with string format.
				/// \param id. Only for inheritance compatibility
				/// \return string with the request command.
				///
				virtual std::string getRequest(uint32_t id = 0) override;
				virtual std::string getResponse() override;
				virtual bool parseRequest(const tinyxml2::XMLElement* xml) = 0;
				virtual bool parseResponse(const tinyxml2::XMLElement*xml) = 0;

				inline std::string commandName() const{ return _commandName;}
				inline Printers::JetErrorCode getError() const{ return _error;}
				void setError(const Printers::JetErrorCode &error);

				const std::map<std::string, std::string> &attributes() const;

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

				virtual std::string toString() override;
				virtual std::string toString(bool val) const override;

				inline void insertAttribute(const std::string& key, const std::string& value) {_attributes.insert(std::pair<std::string, std::string>(key, value));}

			private:
				const std::string _commandName;
		};
	}
}

#endif // MACSA_JETPROTOCOL_COMMAND_H
