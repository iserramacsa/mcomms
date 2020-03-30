#ifndef MACSA_MPROTOCOL_COMMANDS_H
#define MACSA_MPROTOCOL_COMMANDS_H

#include <cstdint>
#include <string>
#include <tinyxml2.h>
#include <map>
#include "tij/datatypes.h"
#include "tij/tijprinter.h"
#include "xmlprotocol/xmlcommands.h"

namespace Macsa{
	namespace MProtocol {
		///
		/// \brief The MCommand class is the base class from MProtocol command.
		/// Based on a xml structure.
		///
		class MCommand : public XMLCommand
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
				Printers::ErrorCode _error;
				Printers::TijPrinter& _printer;

				virtual void buildRequest() = 0;
				virtual void buildResponse() = 0;

				tinyxml2::XMLElement * newCommandNode();

			protected:
				Printers::ErrorCode getCommandError(const tinyxml2::XMLElement *wind) const;
				const tinyxml2::XMLElement *getCommand(const tinyxml2::XMLElement *wind, unsigned int &windId) const;

				void addWindError(const Printers::ErrorCode& errorCode);

			private:
				tinyxml2::XMLElement * buildNewFrame();
				const std::string _commandName;

				int getWindId(const tinyxml2::XMLElement *wind) const;

		};
	}
}

#endif // MPROTOCOLCOMMANDS_H
