#include "mprotocol/merrorslogs.h"
#include "mprotocol/mprotocol.h"
#include "mtools.h"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

using namespace Macsa;
using namespace Macsa::MProtocol;

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

MErrorsLogs::MErrorsLogs(Macsa::Printers::TIJPrinter &printer) :
	MCommand(MERRORS_LOGS, printer)
{}

void MErrorsLogs::buildRequest()
{
	newCommandNode();
}

void MErrorsLogs::buildResponse()
{
	XMLElement* cmd = newCommandNode();
	_error = Printers::ErrorCode_n::SUCCESS;
	std::vector<Printers::Error> list = _printer.errorsLog();
	for (std::vector<Printers::Error>::const_iterator err = list.begin(); err != list.end(); err++) {
		addNewItem(*err, &cmd);
	}
	addWindError(_error);
}


bool MErrorsLogs::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	return valid;
}

bool MErrorsLogs::parseResponse(const XMLElement *xml)
{
	bool valid = false;
	const XMLElement * cmd = getCommand(xml, _id);
	if (cmd != nullptr)
	{
		std::vector<Printers::Error> log;
		_error = getCommandError(xml);
		const XMLElement* item = cmd->FirstChildElement(MERRORS_LOGS_ITEM);
		while (item != nullptr) {
			Printers::Error err;
			if (parseItem(item, err)) {
				log.push_back(err);
			}
			item = item->NextSiblingElement(MERRORS_LOGS_ITEM);
		}
		_printer.setErrorsLog(log);

	}
	return valid;
}
// #define MERRORS_LOGS_BOARD_ATTR			"BoardId"
// #define MERRORS_LOGS_TSTAMP_ATTR			"When"
// #define MERRORS_LOGS_TYPE_ATTR		    "Type"
// #define MERRORS_LOGS_PRIO_ATTR		    "Priority"
// #define MERRORS_LOGS_CODE_ATTR		    "ErrorCode"
void MErrorsLogs::addNewItem(const Printers::Error &error, XMLElement **parent)
{
	XMLElement* item = createChildNode(MERRORS_LOGS_ITEM, parent);
	if (item != nullptr) {
		item->SetAttribute(MERRORS_LOGS_BOARD_ATTR, MTools::toString(error.boardId()).c_str());
		item->SetAttribute(MERRORS_LOGS_TSTAMP_ATTR, _printer.formatedDateTime(error.timestamp()).c_str());
		item->SetAttribute(MERRORS_LOGS_TYPE_ATTR, error.type().toString().c_str());
		item->SetAttribute(MERRORS_LOGS_PRIO_ATTR, MTools::toString(error.priority()).c_str());
		item->SetAttribute(MERRORS_LOGS_CODE_ATTR, error.code().toString().c_str());
	}
}

bool MErrorsLogs::parseItem(const XMLElement *item, Printers::Error &error)
{
	error.clear();
	if (item != nullptr) {
		error.setBoardId(item->UnsignedAttribute(MERRORS_LOGS_BOARD_ATTR, 0));
		error.setTimestamp(_printer.dateTimeFromString(getTextAttribute(item, MERRORS_LOGS_TSTAMP_ATTR, "")));
		error.setType(getTextAttribute(item, MERRORS_LOGS_TYPE_ATTR, error.type().toString()));
		error.setPriority(item->UnsignedAttribute(MERRORS_LOGS_PRIO_ATTR, 0));
		error.setCode(getTextAttribute(item, MERRORS_LOGS_CODE_ATTR, error.code().toString()));
	}

	return (error.type() != Printers::ErrorType_n::INVALID);
}
