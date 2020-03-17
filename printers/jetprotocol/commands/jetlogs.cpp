#include "jetprotocol/jetlogs.h"
#include "jetprotocol/jetprotocol.h"
//#include "mtools.h"

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

// #define MERRORS_LOGS			"GETERRORLOG"
// #define MERRORS_LOGS_ITEM			"ITEM"
// #define MERRORS_LOGS_BOARD_ATTR			"BoardId"
// #define MERRORS_LOGS_TSTAMP_ATTR	    "When"
// #define MERRORS_LOGS_TYPE_ATTR		    "Type"
// #define MERRORS_LOGS_PRIO_ATTR		    "Priority"
// #define MERRORS_LOGS_CODE_ATTR		    "ErrorCode"
/* ****************************************************
 ##   Request
 <WIND id="0">
	 <GETERRORLOG/>
 </WIND>

 ##   Response
 <WIND id="[Command Id]">
	 <ERROR Code="Error Code"/>
	 <GETERRORLOG>
		 <ITEM
			 BoardId="[Board Id]"
			 When="[Date-time]"
			 Type="[Printer Error Type]"
			 Priority="[Printer Error Priority]"
			 ErrorCode="[Printer Error Code]"/>
	 </GETERRORLOG>
 </WIND>
****************************************************** */

JetErrorsLogs::JetErrorsLogs(Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_LOGS, printer)
{

}

void JetErrorsLogs::buildRequest()
{
}

void JetErrorsLogs::buildResponse()
{
}


bool JetErrorsLogs::parseRequest(const XMLElement *xml)
{
	return false;
}

bool JetErrorsLogs::parseResponse(const XMLElement *xml)
{
	return false;
}
// #define MERRORS_LOGS_BOARD_ATTR			"BoardId"
// #define MERRORS_LOGS_TSTAMP_ATTR			"When"
// #define MERRORS_LOGS_TYPE_ATTR		    "Type"
// #define MERRORS_LOGS_PRIO_ATTR		    "Priority"
// #define MERRORS_LOGS_CODE_ATTR		    "ErrorCode"
// void MErrorsLogs::addNewItem(const Printers::Error &error, XMLElement **parent)
// {
// 	XMLElement* item = createChildNode(MERRORS_LOGS_ITEM, parent);
// 	if (item != nullptr) {
// 		item->SetAttribute(MERRORS_LOGS_BOARD_ATTR, MTools::toString(error.boardId()).c_str());
// 		item->SetAttribute(MERRORS_LOGS_TSTAMP_ATTR, _printer.formatedDateTime(error.timestamp()).c_str());
// 		item->SetAttribute(MERRORS_LOGS_TYPE_ATTR, error.type().toString().c_str());
// 		item->SetAttribute(MERRORS_LOGS_PRIO_ATTR, MTools::toString(error.priority()).c_str());
// 		item->SetAttribute(MERRORS_LOGS_CODE_ATTR, error.code().toString().c_str());
// 	}
// }
//
// bool MErrorsLogs::parseItem(const XMLElement *item, Printers::Error &error)
// {
// 	error.clear();
// 	if (item != nullptr) {
// 		error.setBoardId(item->UnsignedAttribute(MERRORS_LOGS_BOARD_ATTR, 0));
// 		error.setTimestamp(_printer.dateTimeFromString(getTextAttribute(item, MERRORS_LOGS_TSTAMP_ATTR, "")));
// 		error.setType(getTextAttribute(item, MERRORS_LOGS_TYPE_ATTR, error.type().toString()));
// 		error.setPriority(item->UnsignedAttribute(MERRORS_LOGS_PRIO_ATTR, 0));
// 		error.setCode(getTextAttribute(item, MERRORS_LOGS_CODE_ATTR, error.code().toString()));
// 	}
//
// 	return (error.type() != Printers::nErrorType::INVALID);
// }
//
