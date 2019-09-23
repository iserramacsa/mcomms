#ifndef MCOMMAND_MOCK_H
#define MCOMMAND_MOCK_H
#include <string>
#include "mprotocol/mcommands.h"
#include <gmock/gmock.h>

using namespace Macsa::MProtocol;

class MCommandMock : public MCommandBase
{
	public:
		MCommandMock(Macsa::Printers::Printer& printer);
		virtual ~MCommandMock();

//		MOCK_CONST_METHOD0 (commandName, std::string());
//		MOCK_METHOD1(parse, bool(const tinyxml2::XMLElement*));
//		MOCK_METHOD0(getWind, tinyxml2::XMLElement*());
//		MOCK_METHOD2(setWind, tinyxml2::XMLElement*(tinyxml2::XMLElement **, MErrorCode));
//		MOCK_METHOD1(getWindNode, const tinyxml2::XMLElement*(const tinyxml2::XMLElement*));
//		MOCK_METHOD2(isNoChildrenSingleNode, bool(const tinyxml2::XMLElement*, const std::string&));
//		MOCK_CONST_METHOD0(datetime, std::string());
//		MOCK_METHOD3(textElement, tinyxml2::XMLElement*(const std::string&, const std::string&, tinyxml2::XMLElement**));
//		MOCK_METHOD0(build, void());
//		MOCK_METHOD3(QueryStringAttribute, tinyxml2::XMLError(const tinyxml2::XMLElement *, const std::string&, std::string&));
//		MOCK_METHOD2(isElement, bool(const tinyxml2::XMLElement*, const std::string&));
//		MOCK_METHOD2(newElement, tinyxml2::XMLElement*(const std::string &, tinyxml2::XMLElement **));
//		MOCK_METHOD1(valid, bool(const tinyxml2::XMLElement *));


		virtual std::string commandName() const;
		virtual bool parse(const tinyxml2::XMLElement*);
		virtual tinyxml2::XMLElement* getWind();
		virtual tinyxml2::XMLElement* setWind(tinyxml2::XMLElement **cmd, MErrorCode error = MErrorCode(MErrorCode::Success));
		virtual const tinyxml2::XMLElement *getWindNode(const tinyxml2::XMLElement*);
		virtual bool isNoChildrenSingleNode(const tinyxml2::XMLElement* wind, const std::string& nodeName);
		virtual std::string dateTime() const;
		virtual tinyxml2::XMLElement* textElement(const std::string& name, const std::string& content, tinyxml2::XMLElement** parentNode = nullptr);
		virtual void build();
		virtual tinyxml2::XMLError QueryStringAttribute(const tinyxml2::XMLElement *element, const std::string& attr, std::string& value);
		virtual bool isElement(const tinyxml2::XMLElement* element, const std::string& name);
		virtual tinyxml2::XMLElement* newElement(const std::string& name, tinyxml2::XMLElement** parentNode = nullptr);
		virtual bool valid(const tinyxml2::XMLElement *wind); //Check error response
				tinyxml2::XMLDocument* doc();
				uint32_t id(){return _id;}

};

#endif //MCOMMAND_MOCK_H
