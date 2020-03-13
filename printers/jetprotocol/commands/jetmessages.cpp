#include "mprotocol/mcurrentmessage.h"
#include "mprotocol/mprotocol.h"

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

MSetCurrentMessage::MSetCurrentMessage(Printers::TijPrinter &printer, const std::string &filename) :
	MCommand(MSET_CURRENT_MESSAGE, printer)
{
	_filePath = filename;
}

MSetCurrentMessage::~MSetCurrentMessage()
{}

void MSetCurrentMessage::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr && _filePath.length()) {
		cmd->SetAttribute(ATTRIBUTE_BOARD_ID, 0);
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filePath.c_str());
	}
}

void MSetCurrentMessage::buildResponse()
{
	//XMLElement* cmd = newCommandNode();
	newCommandNode();
	_error = Printers::nErrorCode::SUCCESS; //TODO:
	addWindError(_error);
}

bool MSetCurrentMessage::parseRequest(const tinyxml2::XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = false;
	if  (cmd != nullptr) {
		valid = (cmd != nullptr && cmd->NoChildren());
		if (valid){
			_filePath = getTextAttribute(cmd, ATTRIBUTE_FILEPATH, "");
		}
	}
	return valid;
}

bool MSetCurrentMessage::parseResponse(const tinyxml2::XMLElement *xml)
{
	_attributes.clear();
	const XMLElement * cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
	}
	return valid;
}


