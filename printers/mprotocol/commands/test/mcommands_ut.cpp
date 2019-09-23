#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mprotocol/mcommands.h"
#include "printer/printer.h"
#include "mcommandmock.h"

using namespace Macsa::MProtocol;
using namespace Macsa::Printers;
using namespace tinyxml2;

class MCommandsUT: public ::testing::Test {
	public:
		MCommandsUT( ) {
			// initialization code here
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
			_cmd = new MCommandMock(_printer);
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
			try {
				if(_cmd != nullptr) {
					delete _cmd;
				}

			} catch (std::exception e) {
				std::cout << __PRETTY_FUNCTION__ << " exception: " << e.what() << std::endl;
			}
		}

		~MCommandsUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}
		// put in any custom data members that you need

		bool isEquivalentElement(const XMLElement* e1, const XMLElement* e2)
		{
			bool equivalent = false;

			if (e1 == nullptr || e2 == nullptr){
				std::cout << "One of the elements is null" << std::endl;
				return equivalent;
			}

			std::string name = e1->Name();
			equivalent = (name.compare(e2->Name()) == 0);

			if(equivalent){
				//Attributes
				const XMLAttribute* attr1 = e1->FirstAttribute();
				const XMLAttribute* attr2 = e2->FirstAttribute();
				for (; (attr1 != nullptr && attr2 != nullptr); attr1=attr1->Next(), attr2=attr2->Next())
				{
					equivalent &= (isEquivalentAttributte(attr1, attr2));
					if(!equivalent) {
						break;
					}
				}
				if(equivalent){
					equivalent &= (attr1 == nullptr && attr2 == nullptr);
					if(!equivalent){
						std::cout << "Elements differs on number of attributes" << std::endl;
					}
				}
				//Childs
				if(equivalent){
					const XMLNode* child1 = e1->FirstChild();
					const XMLNode* child2 = e2->FirstChild();
					if (child1 !=  nullptr || child2 != nullptr)
					{
						while (equivalent == true && child1 != nullptr && child2 != nullptr)
						{
							if (dynamic_cast<const XMLElement*>(child1) != nullptr && dynamic_cast<const XMLElement*>(child2) != nullptr)
							{
								equivalent &= isEquivalentElement(dynamic_cast<const XMLElement*>(child1), dynamic_cast<const XMLElement*>(child2));
							}
							else if (dynamic_cast<const XMLElement*>(child1) == nullptr && dynamic_cast<const XMLElement*>(child2) == nullptr)
							{
								std::string value = e1->FirstChild()->Value();
								equivalent &= (value.compare(e2->FirstChild()->Value()) == 0);
							}
							else {
								equivalent = false;
								std::cout << "Elements differs on childs type" << std::endl;
								break;
							}

							child1 = child1->NextSibling();
							child2 = child2->NextSibling();
						}

						if(equivalent){
							equivalent &= (child1 == nullptr && child2 == nullptr);
							if(!equivalent){
								std::cout << "Elements differs on number of childs" << std::endl;
							}
						}
					}
				}
			}
			else {
				std::cout << "Elements difers on name: " << e1->Name() << " - " << e2->Name()<< std::endl;
			}

			return equivalent;
		}

		bool isEquivalentAttributte(const XMLAttribute* a1, const XMLAttribute* a2)
		{
			std::string name = a1->Name();
			std::string val = a1->Value();
			bool equivalent = (name.compare(a2->Name()) == 0 && val.compare(a2->Value()) == 0);

			if(!equivalent) {
				if (name.compare(a2->Name()) != 0) {
					std::cout << "Elements attribute differs on name: " << a1->Name() << " - " << a2->Name()<< std::endl;
				}
				else if (val.compare(a2->Value()) != 0) {
					std::cout << "Elements attribute differs on value: " << a1->Value() << " - " << a2->Value()<< std::endl;
				}
			}

			return equivalent;
		}

	protected:
		MCommandMock * _cmd;
		Macsa::Printers::Printer _printer;
};

TEST_F(MCommandsUT, setupTeardown)
{
	EXPECT_TRUE(_cmd->doc() != nullptr);
}

TEST_F(MCommandsUT, getCommandName_returnsMcommandMock)
{
	EXPECT_EQ(_cmd->commandName(), "MCommandMock");
}

TEST_F(MCommandsUT, isElementWithNullptr_returnsFalse)
{
	const char* mockElement = "";
	EXPECT_FALSE(_cmd->isElement(nullptr, mockElement));
}

TEST_F(MCommandsUT, isElementWithNode_returnsFalse)
{
	const char* mockElement = "MOCK_ELEMENT";
	XMLNode* node  = _cmd->doc()->NewText(mockElement);
	EXPECT_FALSE(_cmd->isElement(dynamic_cast<XMLElement*>(node), mockElement));
}

TEST_F(MCommandsUT, isElementWithIncorrectName_returnsFalse)
{
	const char* mockElement = "MOCK_ELEMENT";
	const char* notMockElement = "NOT_MOCK_ELEMENT";
	XMLElement* element  = _cmd->doc()->NewElement(mockElement);
	EXPECT_FALSE(_cmd->isElement(element, notMockElement));
}

TEST_F(MCommandsUT, isElement_returnsTrue)
{
	const char* mockElement = "MOCK_ELEMENT";
	XMLElement* element  = _cmd->doc()->NewElement(mockElement);
	EXPECT_TRUE(_cmd->isElement(element, mockElement));
}

TEST_F(MCommandsUT, newElement_returnValidElement)
{
	const char* mockElement = "MOCK_ELEMENT";
	XMLElement* mock = _cmd->newElement(mockElement);
	bool notnull = (mock != nullptr);
	EXPECT_TRUE(notnull);
	if (notnull) {
		EXPECT_TRUE(mock->ToElement() != nullptr);
		EXPECT_TRUE(std::string(mock->Name()).compare(mockElement) == 0);
	}
}

TEST_F(MCommandsUT, newNullElement_returnNullElement)
{
	const char* nullElement = "";
	XMLElement* mock = _cmd->newElement(nullElement);
	bool notnull = (mock != nullptr);
	EXPECT_FALSE(notnull);
}

TEST_F(MCommandsUT, getWind_returnEmptyWind)
{
	XMLElement* wind = _cmd->getWind();
	XMLDocument doc;
	std::string xml = _cmd->toString();

	XMLError parsed = doc.Parse(xml.c_str(), xml.length());
	EXPECT_EQ(parsed, XMLError::XML_SUCCESS);
	if(parsed == XMLError::XML_SUCCESS){
		EXPECT_TRUE(isEquivalentElement(wind, doc.RootElement()));
	}
	doc.Clear();
}

TEST_F(MCommandsUT, getWind_returnEditableWind)
{
	XMLElement* wind = _cmd->getWind();
	XMLDocument doc;
	wind->SetText("MOCKED ELEMENT");

	std::string xml = _cmd->toString();

	XMLError parsed = doc.Parse(xml.c_str(), xml.length());
	EXPECT_EQ(parsed, XMLError::XML_SUCCESS);
	if(parsed == XMLError::XML_SUCCESS){
		EXPECT_TRUE(isEquivalentElement(wind, doc.RootElement()));
	}
	doc.Clear();
}

TEST_F(MCommandsUT, setWindWithNullCmd_returnNullWind)
{
	XMLElement* nullElement = nullptr;
	XMLElement* wind = _cmd->setWind(&nullElement);
	EXPECT_TRUE(wind == nullptr);
}

TEST_F(MCommandsUT, setWindWithNullPointer_returnNullWind)
{
	XMLElement* wind = _cmd->setWind(nullptr);
	EXPECT_TRUE(wind == nullptr);
}


TEST_F(MCommandsUT, setWindWithValidCommand_returnValidWind)
{
	const char* mockElement = "MOCK_ELEMENT";
	XMLDocument doc;
	XMLElement* mock = _cmd->newElement(mockElement);
	XMLElement* wind = _cmd->setWind(&mock);

	bool validWind = (wind != nullptr);
	EXPECT_TRUE(validWind);
	if(validWind) {
		EXPECT_TRUE(std::string(wind->Name()).compare("WIND") == 0);
		XMLElement* element = wind->FirstChildElement(mockElement);
		EXPECT_TRUE(element != nullptr);

		std::string xml = _cmd->toString();
		XMLError parsed = doc.Parse(xml.c_str(), xml.length());
		EXPECT_EQ(parsed, XMLError::XML_SUCCESS);
		if(parsed == XMLError::XML_SUCCESS){
			EXPECT_TRUE(isEquivalentElement(wind, doc.RootElement()));
		}
	}
	doc.Clear();
}
