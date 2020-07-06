#include "jetprotocol/jetlogs.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

/* ****************************************************
 ##   Request
 <WIND Command="GetLogs" Type="[Query Type]" From="[From Date]" To="[To Date]"></WIND>

 ##   Response
<WIND Command="GetLogs" Code="[Cod Error]" Description="[Descripción]”>
	<LOG DateTime="[Event DateTime]" Type="[Event Type]" Message="[Message]"/>
</WIND>
****************************************************** */

JetErrorsLogs::JetErrorsLogs(Printers::JetPrinter &printer, time_t from, time_t to, Printers::JetLogType type) :
	JetCommand(CMD_GET_LOGS, printer)
{
	_from = from;
	_to = to;
	_type = type;
}

void JetErrorsLogs::buildRequest()
{
	XMLElement* cmd = newCommandWind();
	cmd->SetAttribute(TYPE_ATTRIBUTE, _type.toString().c_str());
	cmd->SetAttribute(FROM_DT_ATTRIBUTE, _printer.formatedDateTime(_from).c_str());
	cmd->SetAttribute(TO_DT_ATTRIBUTE, _printer.formatedDateTime(_to).c_str());
}

void JetErrorsLogs::buildResponse()
{
	XMLElement* cmd = newCommandWind();
	setCommandError(_error);
	std::list<Printers::LogItem> logs = _printer.logs(_from, _to);
	for (std::list<Printers::LogItem>::const_iterator it = logs.begin(); it != logs.end(); it++){
		addNewItem(*it, &cmd);
	}

}

bool JetErrorsLogs::parseItem(const XMLElement *item, Printers::LogItem &logItem)
{
	logItem.clear();
	if (item != nullptr) {
		logItem.setTimestamp(_printer.dateTimeFromString(getTextAttribute(item, DATETIME_ATTRIBUTE, "")));
		logItem.setType(getTextAttribute(item, TYPE_ATTRIBUTE, JET_LOG_TYPE_ALL));
		logItem.setMessage(getTextAttribute(item, MESSAGE_ATTRIBUTE, ""));
	}

	return (logItem.type()() != Printers::nJetLogType::LOG_TYPE_ALL);
}



bool JetErrorsLogs::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);

	if (valid) {
		_type = getTextAttribute(xml, TYPE_ATTRIBUTE, Printers::JetLogType().toString());
		_from = _printer.dateTimeFromString(getTextAttribute(xml, FROM_DT_ATTRIBUTE, "0"));
		_to = _printer.dateTimeFromString(getTextAttribute(xml, TO_DT_ATTRIBUTE, "0"));
	}

	return valid;
}

bool JetErrorsLogs::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);

	if (valid) {
		const XMLElement* item = xml->FirstChildElement(JET_LOG_TAG);
		std::list<Printers::LogItem> logs;
		while (item != nullptr) {
			Printers::LogItem log;
			if (parseItem(item, log)){
				logs.push_back(log);
			}
			item = item->NextSiblingElement(JET_LOG_TAG);
		}
		_printer.updateLogs(logs);
	}

	return valid;
}

void JetErrorsLogs::addNewItem(const Printers::LogItem &log, XMLElement **parent)
{
	XMLElement* item = createChildNode(JET_LOG_TAG, parent);
	if (item != nullptr) {
		item->SetAttribute(DATETIME_ATTRIBUTE, _printer.formatedDateTime(log.timestamp()).c_str());
		item->SetAttribute(TYPE_ATTRIBUTE, log.type().toString().c_str());
		item->SetAttribute(MESSAGE_ATTRIBUTE, log.message().c_str());
	}
}
