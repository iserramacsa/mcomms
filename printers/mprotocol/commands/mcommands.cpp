#include "mprotocol/mcommands.h"
#include "mprotocol/mprotocol.h"
#include "mtools.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Macsa;
using namespace Macsa::MProtocol;
using namespace tinyxml2;

MCommand::MCommand(const std::string& commandName, Printers::TIJPrinter &printer):
	_printer(printer),
	_commandName(commandName)
{}

MCommand::~MCommand()
{}

std::string MCommand::getRequest(uint32_t windId)
{
	_id = windId;
	buildRequest();
	return toString();
}

std::string MCommand::getResponse()
{
	buildResponse();
	return toString();
}

void MCommand::setError(const Printers::ErrorCode &error)
{
	_error = error;
}

std::string MCommand::toString()
{
	XMLPrinter p;
	_doc.Print(&p);
	return p.CStr();
}

XMLElement *MCommand::newCommandNode()
{
	XMLElement * wind = buildNewFrame();
	XMLElement* cmd = nullptr;
	if (wind != nullptr) {
		cmd = _doc.NewElement(_commandName.c_str());
		if(cmd != nullptr) {
			wind->InsertEndChild(cmd);
		}
	}

	return cmd;
}

bool MCommand::parseSingleCommand(const XMLElement *root)
{
	bool parsed = false;
	int id  = MTools::XML::getWindId(root);
	if(id != -1) {
		if (MTools::XML::isSingleCommand(root, _commandName.c_str())){
			_id = static_cast<uint32_t>(id);
			parsed = true;
		}
	}
	return parsed;
}

XMLElement *MCommand::buildNewFrame()
{
	if (_doc.RootElement() != nullptr) {
		_doc.Clear();
	}
	XMLElement* wind = _doc.NewElement(MWIND);
	int id = static_cast<int>(_id);
	wind->SetAttribute(MWIND_ID_ATTR, id);
	_doc.InsertEndChild(wind);
	return _doc.RootElement();
}

/********************************************************************************/
/*								XML Tools										*/
/********************************************************************************/
int MCommand::getWindId(const XMLElement *wind) const
{
	int id = -1;

	if (wind != nullptr && std::string(wind->Name()).compare(MWIND) == 0) {
		wind->QueryIntAttribute(MWIND_ID_ATTR, &id);
	}

	return id;
}

const XMLElement *MCommand::getCommand(const XMLElement *wind, unsigned int& windId) const
{
	const XMLElement * cmd = nullptr;
	if (wind != nullptr){
		int id = getWindId(wind);
		if (id != -1){
			windId = static_cast<unsigned int>(id);
			cmd = wind->FirstChildElement(_commandName.c_str());
		}
	}
	return cmd;
}

Printers::ErrorCode MCommand::getCommandError(const XMLElement *wind) const
{
	Printers::ErrorCode err;
	err = Printers::ErrorCode_n::UNKOWN_ERROR;
	if (wind != nullptr){
		const XMLElement* error = wind->FirstChildElement(MERROR);
		if (error != nullptr) {
			err = error->Attribute(MERROR_CODE_ATTR, err.toString().c_str());
		}
	}
	return err;
}

std::string MCommand::getTextFromChildNode(const XMLElement *parent, const std::string &child, const std::string &defaultValue) const
{
	std::string text = defaultValue;
	if (parent)	{
		const XMLElement * node = parent->FirstChildElement(child.c_str());
		if (node) {
			text = node->GetText();
		}
	}
	return text;
}

bool MCommand::isSingleCommand(const XMLElement *wind, unsigned int& windId) const
{
	const XMLElement* cmd = getCommand(wind, windId);
	return (cmd != nullptr && cmd->NoChildren());
}

XMLElement *MCommand::createChildNode(const std::string &child, XMLElement **parent)
{
	XMLElement * node = _doc.NewElement(child.c_str());
	if (parent != nullptr && *parent != nullptr){
		(*parent)->InsertEndChild(node);
	}

	return node;
}

XMLElement *MCommand::createTextChildNode(const std::string &child, const std::string &text, XMLElement **parent)
{
	XMLElement * node = createChildNode(child, parent);
	if (node != nullptr) {
		node->SetText(text.c_str());
	}
	return node;
}

void MCommand::addWindError(const Printers::ErrorCode &errorCode)
{
	XMLElement* wind = _doc.FirstChildElement(MWIND);
	if (wind != nullptr) {
		XMLElement* error = createChildNode(MERROR, &wind);
		if (error != nullptr) {
			error->SetAttribute(MERROR_CODE_ATTR, errorCode.toString().c_str());
			wind->InsertFirstChild(error);
		}
	}
}

