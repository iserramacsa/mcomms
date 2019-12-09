#ifndef MPROTOCOL_COMMANDS_H
#define MPROTOCOL_COMMANDS_H

#include "printer/printer.h"
#include <cstdint>
#include <string>
#include <tinyxml2.h>
#include "mprotocol.h"
#include "printer/datatypes.h"
#include "tij/tijprinter.h"

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
				MCommand(const std::string& commandName, Printers::TIJPrinter& printer);
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
				Printers::TIJPrinter& _printer;

				virtual void buildRequest() = 0;
				virtual void buildResponse() = 0;


				std::string toString(); //return current xml document in a std::string
				bool parseSingleCommand(const tinyxml2::XMLElement *root);
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
				bool isSingleCommand(const tinyxml2::XMLElement *wind, unsigned int& windId) const;


				tinyxml2::XMLElement * createChildNode(const std::string &child, tinyxml2::XMLElement **parent);
				tinyxml2::XMLElement * createTextChildNode(const std::string &child, const std::string& text, tinyxml2::XMLElement **parent);
				void addWindError(const Printers::ErrorCode& errorCode);

		};
	}
}

#endif // MPROTOCOLCOMMANDS_H
