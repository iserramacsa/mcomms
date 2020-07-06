#include "jetprotocol/jetmessagevalues.h"
#include "jetprotocol/jetprotocol.h"

#include <sstream>

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

/******************************   SET MESSAGES VARIABLE   *****************************/
JetSetMessageVariable::JetSetMessageVariable(Printers::JetPrinter &printer, unsigned int filenum, const std::string &variable, const std::string &value):
	JetCommand(CMD_SET_MESSAGE_VARIABLE, printer)
{
	_filenum = filenum;
	_variable = variable;
	_value = value;
}

JetSetMessageVariable::JetSetMessageVariable(Printers::JetPrinter &printer):
	JetCommand(CMD_SET_MESSAGE_VARIABLE, printer)
{
	_filenum = 0;
	_variable = "";
	_value = "";
}

void JetSetMessageVariable::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, _filenum);
	cmd->SetAttribute(NAME_ATTRIBUTE, _variable.c_str());
	cmd->SetAttribute(VALUE_ATTRIBUTE, _value.c_str());
}

bool JetSetMessageVariable::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	insertAttribute(MESSAGE_NUMBER_ATTRIBUTE, toString(xml->UnsignedAttribute(MESSAGE_NUMBER_ATTRIBUTE)));
	insertAttribute(NAME_ATTRIBUTE, getTextAttribute(xml, NAME_ATTRIBUTE));
	insertAttribute(VALUE_ATTRIBUTE, getTextAttribute(xml, VALUE_ATTRIBUTE));
	return valid;
}

void JetSetMessageVariable::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSetMessageVariable::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid){
		parseCommandError(xml);
	}
	return valid;
}

/******************************   SET MESSAGES VARIABLES   *****************************/
JetSetMessageVariables::JetSetMessageVariables(Printers::JetPrinter &printer, unsigned int filenum, const std::map<std::string, std::string>& values) :
	JetCommand(CMD_SET_MESSAGE_VARIABLES, printer)
{
	_filenum = filenum;
	_values = values;
}

JetSetMessageVariables::JetSetMessageVariables(Printers::JetPrinter &printer):
	JetCommand(CMD_SET_MESSAGE_VARIABLES, printer)
{
	_filenum = 0;
	_values.clear();
}

void JetSetMessageVariables::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, _filenum);
	for (std::map<std::string, std::string>::iterator var = _values.begin(); var != _values.end(); var++) {
		XMLElement* eVariable = createChildNode(JET_VARIABLE_TAG, &cmd);
		if (eVariable){
			eVariable->SetAttribute(NAME_ATTRIBUTE, var->first.c_str());
			eVariable->SetAttribute(VALUE_ATTRIBUTE, var->second.c_str());
		}
	}
}

bool JetSetMessageVariables::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	insertAttribute(MESSAGE_NUMBER_ATTRIBUTE, toString(xml->UnsignedAttribute(MESSAGE_NUMBER_ATTRIBUTE)));
	for (const XMLElement* eVariable = xml->FirstChildElement(JET_VARIABLE_TAG);
		 eVariable != nullptr; eVariable = eVariable->NextSiblingElement(JET_VARIABLE_TAG))
	{
		insertAttribute(getTextAttribute(xml, NAME_ATTRIBUTE), getTextAttribute(xml, VALUE_ATTRIBUTE));
	}
	return valid;
}

void JetSetMessageVariables::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
}

bool JetSetMessageVariables::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid){
		parseCommandError(xml);
	}
	return valid;
}

/******************************   GET MESSAGES USER FIELDS   *****************************/
JetGetMessageUserFields::JetGetMessageUserFields(Printers::JetPrinter &printer, unsigned int filenum, const std::string &group) :
	JetCommand(CMD_GET_MESSAGE_USER_FIELD, printer)
{
	_filenum = filenum;
	_group = group;
}

JetGetMessageUserFields::JetGetMessageUserFields(Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_MESSAGE_USER_FIELD, printer)
{
	_filenum = 0;
	_group = "";
}

void JetGetMessageUserFields::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, _filenum);
	cmd->SetAttribute(MESSAGE_GROUP_ATTRIBUTE, _group.c_str());
}

bool JetGetMessageUserFields::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	return valid;
}

void JetGetMessageUserFields::buildResponse()
{
	/*XMLElement* cmd =*/ newCommandWind();
	setCommandError(_error);
	//ToDo: Server side
}

bool JetGetMessageUserFields::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError(xml);
		if (_error == Printers::nJetErrorCode::COMMAND_OK) {
			for (const XMLElement* eUInput = xml->FirstChildElement(JET_USER_INPUT_TAG);
				 eUInput != nullptr; eUInput = eUInput->NextSiblingElement((JET_USER_INPUT_TAG))){
				insertAttribute(getTextAttribute(eUInput, NAME_ATTRIBUTE), getTextAttribute(eUInput, VALUE_ATTRIBUTE));
			}
		}
	}
	return valid;
}

/******************************   SET MESSAGES USER FIELDS   *****************************/
JetSetMessageUserFields::JetSetMessageUserFields(Printers::JetPrinter &printer, unsigned int filenum, const std::map<std::string, std::string>& uiFields, const std::string &group) :
	JetCommand(CMD_SET_MESSAGE_USER_FIELD, printer)
{
	_filenum = filenum;
	_group = group;
	_uiFields = uiFields;
}

JetSetMessageUserFields::JetSetMessageUserFields(Printers::JetPrinter &printer) :
	JetCommand(CMD_SET_MESSAGE_USER_FIELD, printer)
{
	_filenum = 0;
	_group = "";
	_uiFields.clear();
}

void JetSetMessageUserFields::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(MESSAGE_NUMBER_ATTRIBUTE, _filenum);
	cmd->SetAttribute(MESSAGE_GROUP_ATTRIBUTE, _group.c_str());
	for (auto& field : _uiFields) {
		XMLElement* eField = createChildNode(JET_USER_INPUT_TAG, &cmd);
		if (eField) {
			eField->SetAttribute(NAME_ATTRIBUTE, field.first.c_str());
			eField->SetAttribute(VALUE_ATTRIBUTE, field.second.c_str());
		}
	}
}

bool JetSetMessageUserFields::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	for (const XMLElement* eUInput = xml->FirstChildElement(JET_USER_INPUT_TAG);
		 eUInput != nullptr; eUInput = eUInput->NextSiblingElement((JET_USER_INPUT_TAG))){
		insertAttribute(getTextAttribute(eUInput, NAME_ATTRIBUTE), getTextAttribute(eUInput, VALUE_ATTRIBUTE));
	}
	return valid;
}

void JetSetMessageUserFields::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
	//ToDo: Server side
}

bool JetSetMessageUserFields::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError(xml);
	}
	return valid;
}
