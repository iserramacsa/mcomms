#include "jetprotocol/jetcommand.h"
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
	_error = Printers::nJetErrorCode::COMMAND_UNKOWN_ERROR;
}

JetCommand::~JetCommand()
{}

std::string JetCommand::getRequest(uint32_t)
{
	buildRequest();
	return toString();
}

std::string JetCommand::getResponse()
{
	buildResponse();
	return XMLCommand::toString();
}

void JetCommand::setError(const Printers::JetErrorCode &error)
{
	_error = error;
}

const std::map<std::string, std::string>& JetCommand::attributes() const
{
    return _attributes;
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

bool JetCommand::isValidWind(const XMLElement *xml)
{
	if (xml != nullptr && (strcmp(xml->Name(), JETWIND) == 0)) {
		const XMLAttribute* attr = xml->FindAttribute(COMMAND_ATTRIBUTE);
		if(attr != nullptr) {
			return (attr->Value() != nullptr && strcmp(attr->Value(), _commandName.c_str()) == 0);
		}
	}
	return false;
}


void JetCommand::setCommandError(const Printers::JetErrorCode &errorCode)
{
	XMLElement* wind = _doc.FirstChildElement(JETWIND);
	if (wind != nullptr) {
		wind->SetAttribute(ERROR_CODE_ATTRIBUTE, errorCode());
		wind->SetAttribute(ERROR_DESCRIPTION_ATTRIBUTE, errorCode.toString().c_str());
	}
}

void JetCommand::parseCommandError()
{
	_error = Printers::nJetErrorCode::COMMAND_UNKOWN_ERROR;
	XMLElement* wind = _doc.FirstChildElement(JETWIND);
	if (wind != nullptr) {
		const XMLAttribute* eCode = wind->FindAttribute(ERROR_CODE_ATTRIBUTE);
		if (eCode){
			unsigned int error = eCode->UnsignedValue();
			_error = static_cast<Printers::nJetErrorCode>(error);
		}
	}
}

std::string JetCommand::toString()
{
	XMLPrinter p;
	_doc.Print(&p);
	std::string command = p.CStr();
	if (_doc.RootElement() && _doc.RootElement()->NoChildren()) {
		if (!_doc.RootElement()->GetText()) {
			size_t pos = command.find_last_of("/>");
			if (pos != command.npos){
				command.replace(pos - 1, strlen("/>"), "></WIND>");
			}
		}
	}
	return command;
}

std::string JetCommand::toString(bool val) const
{
	return (val ? "True" : "False");
}

