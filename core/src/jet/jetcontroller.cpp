#include "jet/jetcontroller.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Printers;
using namespace Macsa::Network;
using namespace Macsa::JetProtocol;

#define TRACE_TX 1
#define TRACE_RX 1

#if TRACE_TX || TRACE_RX
#include <iostream>
#endif

JetController::JetController(const std::string& id, const std::string& address) :
	PrinterController(id, address, JET_PROTOCOL_TCP_PORT),
	_factory(_printer)
{}

JetController::~JetController()
{}

void JetController::initPrinter()
{
	getConfig();
	getStatus();
	getFiles();
	getFonts();
	getPrinterLogs(0, _printer.dateTime());
}

/**********  Status related commands  **********/
bool JetController::getCounters()
{
	return send(_factory.getCounters());
}

bool JetController::getSSCC()
{
	return send(_factory.getSSCC());
}

bool JetController::getStatus()
{
	return send(_factory.getStatus());
}

bool JetController::getDateTime()
{
	return send(_factory.getDateTime());
}

bool JetController::getPrinterLogs(time_t from, time_t to, JetLogType type)
{
	return send(_factory.getPrinterLogs(from, to, type));
}

bool JetController::getPause()
{
	return send(_factory.getPause());
}

bool JetController::setCounters(std::map<unsigned int, unsigned int>& counters)
{
	return send(_factory.setCounters(counters));
}

bool JetController::resetCounters()
{
	return send(_factory.resetCounters());
}

/**********  Files related commands  **********/
bool JetController::getUSBMessages()
{
	return send(_factory.getUSBMessages());
}

bool JetController::getFiles()
{
	return send(_factory.getFiles());
}

bool JetController::getVersions()
{
	return send(_factory.getVersions());
}

bool JetController::getFonts()
{
	return send(_factory.getFonts());
}

/**********  Messages Groups related commands  **********/
bool JetController::setCurrentMessage(unsigned int messageNumber)
{
	return send(_factory.setCurrentMessage(messageNumber));
}

bool JetController::sendMessage(const Printers::Message& message, const std::vector<char> &content, bool raw)
{
	return send(_factory.sendMessage(message, content, raw));
}

bool JetController::resetMessagesGroup()
{
	return send(_factory.resetMessagesGroup());
}

bool JetController::getMessagesGroup(const std::string& group)
{
	return send(_factory.getMessagesGroup(group));
}

bool JetController::createMessageGroup(const std::string& group)
{
	return send(_factory.createMessageGroup(group));
}

bool JetController:: sendMessageGroup(const std::string& group, const Printers::Message &message, const std::vector<char> &content, bool raw)
{
	return send(_factory.sendMessageGroup(group, message, content, raw));
}

bool JetController::deleteMessageGroup(const std::string& group)
{
	return send(_factory.deleteMessageGroup(group));
}

bool JetController::setMessageVariable(unsigned int filenum, const std::string& variable, const std::string& value)
{
	return send(_factory.setMessageVariable(filenum, variable, value));
}

bool JetController::setMessageVariables(unsigned int filenum, const std::map<std::string, std::string>& values)
{
	return send(_factory.setMessageVariables(filenum, values));
}

bool JetController::getUserInputs(unsigned int filenum, const std::string& group)
{
	return send(_factory.getUserInputs(filenum, group));
}

bool JetController::setUserInputs(unsigned int filenum, const std::map<std::string, std::string>& uiFields, const std::string& group)
{
	return send(_factory.setUserInputs(filenum, uiFields, group));
}

/**********  Config related commands  **********/
bool JetController::setPause(bool pause)
{
	return send(_factory.setPause(pause));
}

bool JetController::incrementSSCC()
{
	return send(_factory.incrementSSCC());
}

bool JetController::setDateTime(const time_t &datetime)
{
	return send(_factory.setDateTime(datetime));
}

bool JetController::setOutput(const Printers::JetIO& output)
{
	return send(_factory.setOutput(output));
}

bool JetController::setPrintDirection(Printers::PrintDirection dir)
{
	return send(_factory.setPrintDirection(dir));
}

bool JetController::setPrintBitmapInverted(bool inverted)
{
	return send(_factory.setPrintBitmapInverted(inverted));
}

bool JetController::setPrintSpeed(unsigned int speed)
{
	return send(_factory.setPrintSpeed(speed));
}

bool JetController::setPrintDelay(unsigned int delay)
{
	return send(_factory.setPrintDelay(delay));
}

bool JetController::setHorizontalResolution(unsigned int resolution)
{
	return send(_factory.setHorizontalResolution(resolution));
}

bool JetController::setConfig(Printers::JetPrinter &printer)
{
	return send(_factory.setConfig(printer));
}

bool JetController::getPrintSpeed()
{
	return send(_factory.getPrintSpeed());
}

bool JetController::getPrintDelay()
{
	return send(_factory.getPrintDelay());
}

bool JetController::getHorizontalResolution()
{
	return send(_factory.getHorizontalResolution());
}

bool JetController::getConfig()
{
	return send(_factory.getConfig());
}

bool JetController::resetInkAlarm()
{
	return send(_factory.resetInkAlarm());
}

/**********  NisX related commands  **********/
bool JetController::getNisXMessage(unsigned int msgNum)
{
	return send(_factory.getNisXMessage(msgNum));
}

bool JetController::setNisXElement(const std::string& filename,  const std::string& content)
{
	return send(_factory.setNisXElement(filename, content));
}


/**********  Network methods  **********/
bool JetController::send(XMLCommand *cmd)
{
	bool success = false;
	JetCommand* jetCommand = dynamic_cast<JetCommand*>(cmd);
	if (cmd != nullptr)
	{
		std::string tx = cmd->getRequest();
#if TRACE_TX
		std::cout << __func__ << " TX: " << tx << std::endl;
#endif

		_lastSentStatus = Network::NetworkNode::sendPacket(tx, JET_PROTOCOL_TCP_PORT);
		if (_lastSentStatus == ISocket::FRAME_SUCCESS)
		{
			std::string resp = "";
			_lastSentStatus = Network::NetworkNode::receivePacket(resp, JET_PROTOCOL_TCP_PORT);
#if TRACE_RX
			std::cout << __func__ << " RX: " << resp << std::endl;
#endif
			if(_lastSentStatus == ISocket::FRAME_SUCCESS)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				success = _factory.parseResponse(resp, jetCommand);
				if (success && jetCommand->getError() == Printers::nJetErrorCode::COMMAND_OK) {
					checkCommand(jetCommand->commandName(), jetCommand->attributes());
				}
			}
		}
		delete cmd;
	}
	return success;
}

void JetController::checkCommand(const std::string &command, const std::map<std::string, std::string>& attributes)
{
	if (command.length()){
		if (command == CMD_GET_COUNTERS)
			return;
		else if (command == CMD_GET_SSCC)
			return;
		else if (command == CMD_GET_STATUS) {
			JetNotifier::notifyStatusChanged();
			return;
		}
		else if (command == CMD_GET_DATETIME) {
			JetNotifier::notifyDatetimeChanged(_printer.dateTime());
			return;
		}
		else if (command == CMD_GET_LOGS)
			return;
		else if (command == CMD_GET_PAUSE)
			return;
		else if (command == CMD_SET_COUNTERS)
			return;
		else if (command == CMD_RESET_COUNTERS)
			return;
		else if (command == CMD_GET_USB_MSG)
			return;
		else if (command == CMD_GET_FILES_LIST)
			return;
		else if (command == CMD_GET_PRINTER_VERSIONS)
			return;
		else if (command == CMD_GET_INSTALLED_FONTS)
			return;
		else if (command == CMD_MESSAGE_NUM)
			return;
		else if (command == CMD_SEND_MESSAGE)
			return;
		else if (command == CMD_RESET_MESSAGES)
			return;
		else if (command == CMD_GET_MESSAGES)
			return;
		else if (command == CMD_CREATE_MESSAGE_GROUP)
			return;
		else if (command == CMD_SEND_MESSAGE_TO_GROUP)
			return;
		else if (command == CMD_DELETE_MESSAGE_GROUP)
			return;
		else if (command == CMD_SET_MESSAGE_VARIABLE)
			return;
		else if (command == CMD_SET_MESSAGE_VARIABLES)
			return;
		else if (command == CMD_GET_MESSAGE_USER_FIELD)
			return;
		else if (command == CMD_SET_MESSAGE_USER_FIELD)
			return;
		else if (command == CMD_SET_PAUSE)
			return;
		else if (command == CMD_SET_DATETIME)
			return;
		else if (command == CMD_INC_SSCC)
			return;
		else if (command == CMD_SET_OUTPUT)
			return;
		else if (command == CMD_SET_PRINT_DIR)
			return;
		else if (command == CMD_SET_PRINT_INVERT)
			return;
		else if (command == CMD_SET_PRINT_SPEED)
			return;
		else if (command == CMD_SET_PRINT_DELAY)
			return;
		else if (command == CMD_SET_HOR_RESOLUTION )
			return;
		else if (command == CMD_SET_CONFIG){
			JetNotifier::notifyConfigChanged();
			return;
		}
		else if (command == CMD_GET_PRINT_SPEED)
			return;
		else if (command == CMD_GET_PRINT_DELAY)
			return;
		else if (command == CMD_GET_HOR_RESOLUTION )
			return;
		else if (command == CMD_GET_CONFIG)
			return;
		else if (command == CMD_RESET_INK_ALARM)
			return;
		else if (command == CMD_GET_NISX_MESSAGE)
			return;
		else if (command == CMD_SET_NISX_MESSAGE)
			return;
	}
}
