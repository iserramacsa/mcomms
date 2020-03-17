#include "jetprotocol/jetmessages.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetSetCurrentMessage::JetSetCurrentMessage(Macsa::Printers::JetPrinter &printer, const std::string &filename) :
	JetCommand(CMD_SEND_MESSAGE, printer)
{
	//_filePath = filename;
}

JetSetCurrentMessage::~JetSetCurrentMessage()
{}

void JetSetCurrentMessage::buildRequest()
{
}

void JetSetCurrentMessage::buildResponse()
{
}

bool JetSetCurrentMessage::parseRequest(const tinyxml2::XMLElement *xml)
{
	return false;
}

bool JetSetCurrentMessage::parseResponse(const tinyxml2::XMLElement *xml)
{
	return false;
}


