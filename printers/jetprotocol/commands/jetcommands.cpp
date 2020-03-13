#include "jetprotocol/jetcommands.h"
#include "jetprotocol/jetprotocol.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetCommand::JetCommand(const std::string& commandName, Printers::JetPrinter &printer):
	_printer(printer),
	_commandName(commandName)
{
	_attributes.clear();
}

JetCommand::~JetCommand()
{}

std::string JetCommand::getRequest()
{
	buildRequest();
	return toString();
}

std::string JetCommand::getResponse()
{
	buildResponse();
	return toString();
}

void JetCommand::setError(const Printers::ErrorCode &error)
{
	_error = error;
}

std::map<std::string, std::string> JetCommand::attributes() const
{
    return _attributes;
}

std::string JetCommand::toString()
{
    XMLPrinter p;
    _doc.Print(&p);
    return p.CStr();
}

XMLElement *JetCommand::newCommandWind()
{
	if (_doc.RootElement() != nullptr) {
		_doc.Clear();
	}
	XMLElement* wind = _doc.NewElement(JETWIND);
	wind->SetAttribute(COMMAND_ATTRIBUTE, _commandName.c_str());
	_doc.InsertEndChild(wind);
	return _doc.RootElement();
}


//void JetCommand::addWindError(const Printers::ErrorCode &errorCode)
//{
//	XMLElement* wind = _doc.FirstChildElement(MWIND);
//	if (wind != nullptr) {
//		XMLElement* error = createChildNode(MERROR, &wind);
//		if (error != nullptr) {
//			error->SetAttribute(ATTRIBUTE_CODE, errorCode.toString().c_str());
//			wind->InsertFirstChild(error);
//		}
//	}
//}

