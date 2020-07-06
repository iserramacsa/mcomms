#include "jet/jetmonitor.h"
#include "jetprotocol/jetprotocol.h"
#include <iostream>


using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Network;

JetMonitor::JetMonitor(const std::string &id, const std::string &address) :
	JetController(id, address)
{
	_running.store(false);
	_maxReconnections = 30;
	_reconnections = 0;
}

JetMonitor::~JetMonitor()
{
	stop();
}

bool JetMonitor::connect()
{
	bool connected = PrinterController::connect();
	if (connected) {
		initPrinter();
		start();
	}
	return connected;
}

bool JetMonitor::disconnect()
{
	bool disconnected = PrinterController::disconnect();
	if (NetworkNode::status() == DISCONNECTED) {
		stop();
	}
	return disconnected;
}

void JetMonitor::run()
{
	_running.store(true);

	while (_running.load() && _reconnections < _maxReconnections) {
		{
			std::unique_lock<std::mutex> _lck(_mLoop);
			if (_cv.wait_for(_lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
				const std::lock_guard<std::mutex>lock(_mCommands);
				_commands.push_back(_factory.getStatus());
			} else if (_running.load() == false){
				break;
			}
		}
		while (_commands.size()) {
			JetProtocol::JetCommand* cmd = nullptr;
			{
				const std::lock_guard<std::mutex>lock(_mCommands);
				cmd = (*_commands.begin());
			}
			if (cmd){
				sendCmd(cmd);
			}
			{
				const std::lock_guard<std::mutex>lock(_mCommands);
				_commands.pop_front();
			}
		}
	}
	_reconnections = 0;

}

bool JetMonitor::send(XMLCommand *cmd)
{
	ulong numCommands = _commands.size();
	{
		const std::lock_guard<std::mutex>lock(_mCommands);
		_commands.push_back(dynamic_cast<JetProtocol::JetCommand*>(cmd));
	}
	{
		std::unique_lock<std::mutex> _lck(_mLoop);
		_cv.notify_one();
	}
	return ((_commands.size() - numCommands) > 0);
}

bool JetMonitor::sendCmd(Macsa::JetProtocol::JetCommand *cmd)
{
	bool success = false;

	success = JetController::send(cmd);
	if (!success) {
		std::cout << __FUNCTION__ << " Send command " << cmd->commandName() << " failed" << std::endl;
		std::cout << "        reason: " << std::flush;
		switch (_lastSentStatus) {
			case nFrameStatus::FRAME_TIMEOUT:		std::cout << "FRAME_TIMEOUT" 	 << std::endl; _reconnections++; break;
			case nFrameStatus::FRAME_INCOMPLETED:	std::cout << "FRAME_INCOMPLETED" << std::endl; break;
			case nFrameStatus::FRAME_ERROR:			std::cout << "FRAME_ERROR"		 << std::endl; _reconnections++; break;
			default: break;
		}
		PrinterController::reconnect();
	}
	else {
		_reconnections = 0;
	}

	return success;
}

void JetMonitor::checkCommand(const std::string &command, const std::map<std::string, std::string> &attributes)
{
	JetController::checkCommand(command, attributes);
	if (command.length())
	{
		if (command == CMD_SET_COUNTERS) {
			getCounters();
			return;
		}
		else if (command == CMD_RESET_COUNTERS) {
			getCounters();
			return;
		}
		else if (command == CMD_GET_USB_MSG) {
			return;
		}
		else if (command == CMD_GET_FILES_LIST) {
			updateMessageGroups();
			return;
		}
		else if (command == CMD_RESET_MESSAGES) {
			getMessagesGroup(_printer.messageManager().currentGroup());
			return;
		}
		else if (command == CMD_CREATE_MESSAGE_GROUP) {
			getFiles();
			return;
		}
		else if (command == CMD_DELETE_MESSAGE_GROUP) {
			getFiles();
			return;
		}
		else if (command == CMD_SET_PAUSE) {
			getPause();
			return;
		}
		else if (command == CMD_SET_DATETIME){
			getDateTime();
			return;
		}
		else if (command == CMD_INC_SSCC){
			getSSCC();
			return;
		}
		else if (command == CMD_SET_PRINT_DIR) {
			// Get Print Dir by Attribute?
			return;
		}
		else if (command == CMD_SET_PRINT_INVERT){
			// Get Print Inverted by attribute?
			return;
		}
		else if (command == CMD_SET_PRINT_SPEED){
			getPrintSpeed();
			return;
		}
		else if (command == CMD_SET_PRINT_DELAY){
			getPrintDelay();
			return;
		}
		else if (command == CMD_SET_HOR_RESOLUTION ) {
			getHorizontalResolution();
			return;
		}
		else if (command == CMD_SET_CONFIG) {
			getConfig();
			return;
		}
		else if (command == CMD_RESET_INK_ALARM){
			// ???
			return;
		}
//		else if (command == CMD_GET_NISX_MESSAGE)
//			return;
//		else if (command == CMD_SET_NISX_MESSAGE)
//			return;
	}
}

void JetMonitor::updateMessageGroups()
{
	std::vector<std::string> groups = _printer.messageManager().groups();
	for (std::vector<std::string>::const_iterator it = groups.begin(); it != groups.end(); it++) {
		getMessagesGroup(*it);
	}
}

void JetMonitor::start()
{
	if (_running.load()) {
		stop();
	}
	_th = std::thread(&JetMonitor::run, this);
}

void JetMonitor::stop()
{
	if (_running.load()){
		_running.store(false);
		{
			std::unique_lock<std::mutex> _lck(_mLoop);
			_cv.notify_all();
		}
		_th.join();
	}
}
