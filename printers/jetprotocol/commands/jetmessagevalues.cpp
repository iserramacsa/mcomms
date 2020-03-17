#include "jetprotocol/jetmessagevalues.h"
#include "jetprotocol/jetprotocol.h"

#include <sstream>

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;


JetMessageNumber::JetMessageNumber(Printers::JetPrinter &printer, const std::string &filename) :
	JetCommand(CMD_GET_MESSAGE_NUM, printer)
{
//	_filename = filename;
//	_userFieldsMap.clear();
//	_countersMap.clear();
	//	_datesMap.clear();
}

bool JetMessageNumber::parseRequest(const XMLElement *xml)
{
	return false;
}

bool JetMessageNumber::parseResponse(const XMLElement *xml)
{
	return false;
}

void JetMessageNumber::buildRequest()
{

}

void JetMessageNumber::buildResponse()
{

}

