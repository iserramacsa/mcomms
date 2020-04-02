#include "jetprotocol/jetcommandsfactory.h"
#include "jetprotocol/jetprotocol.h"
#include "jetprotocol/jetpause.h"
#include "jetprotocol/jetsingleconfig.h"
#include "jetprotocol/jetconfig.h"
#include "jetprotocol/jetcounters.h"
#include "jetprotocol/jetfiles.h"
#include "jetprotocol/jetlogs.h"
#include "jetprotocol/jetmessages.h"
#include "jetprotocol/jetmessagevalues.h"
#include "jetprotocol/jetstatus.h"
#include "jetprotocol/jetsinglestatus.h"
#include "jetprotocol/jetoutput.h"
#include "jetprotocol/jetnisx.h"
#include "jetprotocol/jetversions.h"

using namespace tinyxml2;
using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;

#define CLOSE_WIND "</" JETWIND ">"

JetCommandsFactory::JetCommandsFactory(JetPrinter &printer) :
	_printer(printer)
{
	_doc.Clear();
}

JetCommandsFactory::~JetCommandsFactory()
{
	_doc.Clear();
}

bool JetCommandsFactory::parseResponse(const std::string &rx, JetCommand * cmd)
{
	bool valid = false;

	if (_doc.FirstChild() != nullptr) 	{
		_doc.Clear();
	}

	if (rx.length())
	{
		size_t close = rx.find(CLOSE_WIND);  //review
		if (close != rx.npos) {
			close += sizeof (CLOSE_WIND);
		}
		std::string frame = rx.substr(0, close);

		_doc.Parse(frame.c_str());
		XMLElement* wind = _doc.FirstChildElement();
		if(wind != nullptr)
		{
			valid = cmd->parseResponse(wind);
		}
	}

	return valid;
}

bool JetCommandsFactory::parseRequest(const std::string &frame, JetCommand** cmd)
{
	bool valid = false;

	if (_doc.FirstChild() != nullptr) 	{
		_doc.Clear();
	}

	if (frame.length())
	{
		if (_doc.Parse(frame.c_str())) {
			XMLElement* wind = _doc.FirstChildElement();
			*cmd = getCommand(wind);
			if (cmd != nullptr){
				valid = (*cmd)->parseRequest(wind);
			}
		}
	}

	return valid;
}

JetCommand *JetCommandsFactory::getCounters()
{
	return new JetGetCounters(_printer);
}

JetCommand *JetCommandsFactory::getSSCC()
{
	return new JetGetSSCC(_printer);
}

JetCommand *JetCommandsFactory::getStatus()
{
	return new JetGetStatus(_printer);
}

JetCommand *JetCommandsFactory::getDateTime()
{
	return new JetGetDatetime(_printer);
}

JetCommand *JetCommandsFactory::getPrinterLogs(time_t from, time_t to, Printers::JetLogType type)
{
	return new JetErrorsLogs(_printer, from, to, type);
}

JetCommand *JetCommandsFactory::getPause()
{
	return new JetGetPause(_printer);
}

JetCommand *JetCommandsFactory::setCounters(std::map<unsigned int, unsigned int> counters)
{
	return  new JetSetCounters(_printer, counters);
}

JetCommand *JetCommandsFactory::resetCounters()
{
	return new JetResetCounters(_printer);
}

JetCommand *JetCommandsFactory::getUSBMessages()
{
	return new JetGetUSBFiles(_printer);
}

JetCommand *JetCommandsFactory::getFiles()
{
	return new JetGetFilesList(_printer);
}

JetCommand *JetCommandsFactory::getVersions()
{
	return new JetGetVersions(_printer);
}

JetCommand *JetCommandsFactory::getFonts()
{
	return new JetGetFonts(_printer);
}

JetCommand *JetCommandsFactory::setCurrentMessage(unsigned int messageNumber)
{
	return new JetSetCurrentMessage(_printer, messageNumber);
}

JetCommand *JetCommandsFactory::sendMessage(const Message &message, const std::vector<char> &content, bool raw)
{
	return new JetSendMessage(_printer, message,  content,  raw);
}

JetCommand *JetCommandsFactory::resetMessagesGroup()
{
	return new JetResetCurrentGroup(_printer);
}

JetCommand *JetCommandsFactory::getMessagesGroup(const std::string& group)
{
	return new JetGetMessages(_printer, group);
}

JetCommand *JetCommandsFactory::createMessageGroup(const std::string &group)
{
	return new JetCreateMessagesGroup(_printer, group);
}

JetCommand *JetCommandsFactory::sendMessageGroup(const std::string& group, const Printers::Message& message, const std::vector<char> &content, bool raw)
{
	return new JetSendMessageGroup(_printer, group, message, content, raw);
}

JetCommand *JetCommandsFactory::deleteMessageGroup(const std::string &group)
{
	return new JetDeleteMessagesGroup(_printer, group);
}

JetCommand *JetCommandsFactory::setMessageVariable(unsigned int filenum, const std::string &variable, const std::string &value)
{
	return new JetSetMessageVariable(_printer, filenum, variable, value);
}

JetCommand *JetCommandsFactory::setMessageVariables(unsigned int filenum, const std::map<std::string, std::string> &values)
{
	return new JetSetMessageVariables(_printer, filenum, values);
}

JetCommand *JetCommandsFactory::getUserInputs(unsigned int filenum, const std::string& group)
{
	return new JetGetMessageUserFields(_printer, filenum, group);
}

JetCommand *JetCommandsFactory::setUserInputs(unsigned int filenum, const std::map<std::string, std::string>& uiFields, const std::string& group)
{
	return new JetSetMessageUserFields(_printer, filenum, uiFields, group);
}

JetCommand *JetCommandsFactory::setPause(bool pause)
{
	return new JetSetPause(_printer, pause);
}

JetCommand *JetCommandsFactory::setDateTime(const time_t &datetime)
{
	return new JetSetDatetime(_printer, datetime);
}

JetCommand *JetCommandsFactory::incrementSSCC()
{
	return new JetIncrementSSCC(_printer);
}

JetCommand *JetCommandsFactory::setOutput(const Printers::JetIO& output)
{
	return new JetSetOutput(_printer, output);
}

JetCommand *JetCommandsFactory::setPrintDirection(PrintDirection dir)
{
	return new JetSetPrintDirection(_printer, dir);
}

JetCommand *JetCommandsFactory::setPrintBitmapInverted(bool inverted)
{
	return new JetSetBitmapInverted(_printer, inverted);
}

JetCommand *JetCommandsFactory::setPrintheadEnabled(PHEnableMode mode)
{
	return new JetSetPrintheadEnabled(_printer, mode);
}

JetCommand *JetCommandsFactory::setPrintSpeed(unsigned int speed)
{
	return new JetSetPrintSpeed(_printer, speed);
}

JetCommand *JetCommandsFactory::setPrintDelay(unsigned int delay)
{
	return new JetSetPrintDelay(_printer, delay);
}

JetCommand *JetCommandsFactory::setHorizontalResolution(unsigned int resolution)
{
	return new JetSetHorizontalResolution(_printer, resolution);
}

JetCommand *JetCommandsFactory::setConfig(JetPrinter &printer)
{
	return new JetSetConfig(printer);
}

JetCommand *JetCommandsFactory::getPrintSpeed()
{
	return new JetGetPrintSpeed(_printer);
}

JetCommand *JetCommandsFactory::getPrintDelay()
{
	return new JetGetPrintDelay(_printer);
}

JetCommand *JetCommandsFactory::getHorizontalResolution()
{
	return new JetGetHorizontalResolution(_printer);
}

JetCommand *JetCommandsFactory::getConfig()
{
	return new JetGetConfig(_printer);
}

JetCommand *JetCommandsFactory::resetInkAlarm()
{
	return  new JetResetInkAlarm(_printer);
}

JetCommand *JetCommandsFactory::getNisXMessage(unsigned int msgNum)
{
	return new JetGetNisxMessage(_printer, msgNum);
}

JetCommand *JetCommandsFactory::setNisXElement(const std::string &filename, const std::string &content)
{
	return new JetSetNisxElement(_printer, filename, content);
}

JetCommand *JetCommandsFactory::getCommand(XMLElement *eCmd)
{
	std::string command = eCmd->Attribute(COMMAND_ATTRIBUTE, "");
	if (command.length()){
		if (command == CMD_GET_COUNTERS)
			return new JetGetCounters(_printer);
		else if (command == CMD_GET_SSCC)
			return new JetGetSSCC(_printer);
		else if (command == CMD_GET_STATUS)
			return new JetGetStatus(_printer);
		else if (command == CMD_GET_DATETIME)
			return new JetGetDatetime(_printer);
		else if (command == CMD_GET_LOGS)
			return new JetErrorsLogs(_printer);
		else if (command == CMD_GET_PAUSE)
			return new JetGetPause(_printer);
		else if (command == CMD_SET_COUNTERS)
			return new JetSetCounters(_printer);
		else if (command == CMD_RESET_COUNTERS)
			return new JetResetCounters(_printer);
		else if (command == CMD_GET_USB_MSG)
			return new JetGetUSBFiles(_printer);
		else if (command == CMD_GET_FILES_LIST)
			return new JetGetFilesList(_printer);
		else if (command == CMD_GET_PRINTER_VERSIONS)
			return new JetGetVersions(_printer);
		else if (command == CMD_GET_INSTALLED_FONTS)
			return new JetGetFonts(_printer);
		else if (command == CMD_MESSAGE_NUM)
			return new JetSetCurrentMessage(_printer);
		else if (command == CMD_SEND_MESSAGE)
			return new JetSendMessage(_printer);
		else if (command == CMD_RESET_MESSAGES)
			return new JetResetCurrentGroup(_printer);
		else if (command == CMD_GET_MESSAGES)
			return new JetGetMessages(_printer);
		else if (command == CMD_CREATE_MESSAGE_GROUP)
			return new JetCreateMessagesGroup(_printer);
		else if (command == CMD_SEND_MESSAGE_TO_GROUP)
			return new JetSendMessageGroup(_printer);
		else if (command == CMD_DELETE_MESSAGE_GROUP)
			return new JetDeleteMessagesGroup(_printer);
		else if (command == CMD_SET_MESSAGE_VARIABLE)
			return new JetSetMessageVariable(_printer);
		else if (command == CMD_SET_MESSAGE_VARIABLES)
			return new JetSetMessageVariables(_printer);
		else if (command == CMD_GET_MESSAGE_USER_FIELD)
			return new JetGetMessageUserFields(_printer);
		else if (command == CMD_SET_MESSAGE_USER_FIELD)
			return new JetSetMessageUserFields(_printer);
		else if (command == CMD_SET_PAUSE)
			return new JetSetPause(_printer);
		else if (command == CMD_SET_DATETIME)
			return new JetSetDatetime(_printer);
		else if (command == CMD_INC_SSCC)
			return new JetIncrementSSCC(_printer);
		else if (command == CMD_SET_OUTPUT)
			return new JetSetOutput(_printer);
		else if (command == CMD_SET_PRINT_DIR)
			return new JetSetPrintDirection(_printer);
		else if (command == CMD_SET_PRINT_INVERT)
			return new JetSetBitmapInverted(_printer);
		else if (command == CMD_SET_PRINTHEAD_ENABLE)
			return new JetSetPrintheadEnabled(_printer);
		else if (command == CMD_SET_PRINT_SPEED)
			return new JetSetPrintSpeed(_printer);
		else if (command == CMD_SET_PRINT_DELAY)
			return new JetSetPrintDelay(_printer);
		else if (command == CMD_SET_HOR_RESOLUTION )
			return new JetSetHorizontalResolution(_printer);
		else if (command == CMD_SET_CONFIG)
			return new JetSetConfig(_printer);
		else if (command == CMD_GET_PRINT_SPEED)
			return new JetGetPrintSpeed(_printer);
		else if (command == CMD_GET_PRINT_DELAY)
			return new JetGetPrintDelay(_printer);
		else if (command == CMD_GET_HOR_RESOLUTION )
			return new JetGetHorizontalResolution(_printer);
		else if (command == CMD_GET_CONFIG)
			return new JetGetConfig(_printer);
		else if (command == CMD_RESET_INK_ALARM)
			return new JetResetInkAlarm(_printer);
		else if (command == CMD_GET_NISX_MESSAGE)
			return new JetGetNisxMessage(_printer);
		else if (command == CMD_SET_NISX_MESSAGE)
			return new JetSetNisxElement(_printer);
	}

	return nullptr;
}
