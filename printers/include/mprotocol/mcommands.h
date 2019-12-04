#ifndef MPROTOCOL_COMMANDS_H
#define MPROTOCOL_COMMANDS_H

#include "printer/printer.h"
#include <cstdint>
#include <string>
#include <tinyxml2.h>
#include "mprotocol.h"

#ifndef VIRTUAL_MOCK
	#define VIRTUAL_MOCK
#endif

namespace Macsa{
	namespace MProtocol {
		class MGetFilesList;
		class MGetStatus;
		class MLive_;
		class MGetConfig;
		class MSetConfig;
		class MUpdate;

		class MCommand
		{
			public:
				MCommand(const std::string& commandName, Printers::Printer& printer);
				virtual ~MCommand();

				virtual std::string getRequest(uint32_t windId);
				virtual std::string getResponse();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml) = 0;
				virtual bool parseResponse(const tinyxml2::XMLElement*xml) = 0;


				inline std::string commandName() const{ return _commandName;}
				inline uint32_t id() const{ return _id;}
				inline Printers::ErrorCode getError() const{ return _error;}

			protected:
				uint32_t _id;
				tinyxml2::XMLDocument _doc;
				Printers::ErrorCode _error;
				Printers::Printer& _printer;

				virtual void buildRequest() = 0;
				virtual void buildResponse() = 0;


				std::string toString(); //return current xml document in a std::string
				tinyxml2::XMLElement * buildNewFrame();
				bool parseSingleCommand(const tinyxml2::XMLElement *root);

			private:
				const std::string _commandName;
				VIRTUAL_MOCK inline uint32_t nextId() const; //ToDo: Move to factory

		};
	}
}

#endif // MPROTOCOLCOMMANDS_H
