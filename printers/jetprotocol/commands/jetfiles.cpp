#include "jetprotocol/jetfiles.h"
#include "jetprotocol/jetprotocol.h"
#include "printer/files.h"

#include <sstream>

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

//=============		GET FILES LIST		=============//
JetGetFilesList::JetGetFilesList(Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_FILES_LIST, printer)
{

}

bool JetGetFilesList::parseResponse(const XMLElement *xml)
{
	return false;
}

bool JetGetFilesList::parseRequest(const XMLElement *xml)
{
	return false;
}

void JetGetFilesList::buildRequest()
{

}

void JetGetFilesList::buildResponse()
{

}
