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

#if defined (MSERVER)
	#define access	private
#elif defined (MCLIENT)
	#define access	public
#else
	#define access	public
#endif


namespace Macsa{
	namespace MProtocol {
		class MGetFilesList;
		class MGetStatus;
		class MLive;
		class MGetConfig;
		class MSetConfig;
		class MUpdate;

		class MCommandBase
		{
			public:
				MCommandBase(Printers::Printer& printer);
				virtual ~MCommandBase();
				std::string toString();
				virtual std::string commandName() const = 0;
				virtual bool parse(const tinyxml2::XMLElement*) = 0;

			protected:
				uint32_t _id;
				Printers::Printer& _printer;
				tinyxml2::XMLDocument _doc;

				VIRTUAL_MOCK tinyxml2::XMLElement* getWind();
				VIRTUAL_MOCK tinyxml2::XMLElement* setWind(tinyxml2::XMLElement **cmd, MErrorCode error = MErrorCode());
				VIRTUAL_MOCK const tinyxml2::XMLElement *getWindNode(const tinyxml2::XMLElement*);
				VIRTUAL_MOCK bool isNoChildrenSingleNode(const tinyxml2::XMLElement* wind, const std::string& nodeName);
				VIRTUAL_MOCK std::string dateTime() const;
				VIRTUAL_MOCK tinyxml2::XMLElement* textElement(const std::string& name, const std::string& content, tinyxml2::XMLElement** parentNode = nullptr);
				virtual void build() = 0;
				VIRTUAL_MOCK tinyxml2::XMLError QueryStringAttribute(const tinyxml2::XMLElement *element, const std::string& attr, std::string& value);
				VIRTUAL_MOCK inline bool isElement(const tinyxml2::XMLElement* element, const std::string& name);
				VIRTUAL_MOCK tinyxml2::XMLElement* newElement(const std::string& name, tinyxml2::XMLElement** parentNode = nullptr);

				VIRTUAL_MOCK bool valid(const tinyxml2::XMLElement *wind); //Check error response

			private:
				VIRTUAL_MOCK inline uint32_t nextId() const;
		};
	}
}

#endif // MPROTOCOLCOMMANDS_H
