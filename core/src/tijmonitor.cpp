#include "tijmonitor.h"
#include "mprotocol/mprotocol.h"
#include "mprotocol/mfiles.h"

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Network;

TijMonitor::TijMonitor(const std::string &id, const std::string &address) :
	TijController(id, address)
{
	_running.store(false);
	_maxReconnections = 30;
	_reconnections = 0;
}

TijMonitor::~TijMonitor()
{
	stop();
}

bool TijMonitor::connect()
{
	bool connected = PrinterController::connect();
	if (connected) {
		start();
	}
	return connected;
}

bool TijMonitor::disconnect()
{
	bool disconnected = PrinterController::disconnect();
	if (NetworkNode::status() == DISCONNECTED) {
		stop();
	}
	return disconnected;
}

#include <iostream>

void TijMonitor::run()
{
	_running.store(true);

	while (_running.load() && _reconnections < _maxReconnections) {
		{
			std::unique_lock<std::mutex> _lck(_mLoop);
			if (_cv.wait_for(_lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
				const std::lock_guard<std::mutex>lock(_mCommands);
				_commands.push_back(_factory.getLiveCommand());
			} else if (_running.load() == false){
				break;
			}
		}
		while (_commands.size()) {
			MProtocol::MCommand* cmd = nullptr;
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

		if (isStatusChanged()) {
			TijController::updateStatus();
		}
		if (isConfigChanged()) {
			TijController::updateConfig();
		}
		if (isFilesChanged()) {
			TijController::updateFilesList();
		}
		if (isFontsChanged())  {
			TijController::updateFontsList();
		}
		if  (isUserValuesChanged()){
			TijController::updateUserValues();
		}
		if (isErrorsLogsChanged()) {
			TijController::updateErrorsList();
		}
	}
	_reconnections = 0;

}

bool TijMonitor::send(MProtocol::MCommand *cmd)
{
	ulong numCommands = _commands.size();
	{
		const std::lock_guard<std::mutex>lock(_mCommands);
		_commands.push_back(cmd);
	}
	{
		std::unique_lock<std::mutex> _lck(_mLoop);
		_cv.notify_one();
	}
	return ((_commands.size() - numCommands) > 0);
}

bool TijMonitor::sendCmd(MProtocol::MCommand *cmd)
{
	bool success = false;

	success = TijController::send(cmd);
	if (!success) {
		std::cout << __FUNCTION__ << " Send command " << cmd->commandName() << " failed" << std::endl;
		std::cout << "        reason: " << std::flush;
		switch (_lastSentStatus) {
			case nFrameStatus::FRAME_TIMEOUT: std::cout <<		"FRAME_TIMEOUT" 	 << std::endl; _reconnections++; break;
			case nFrameStatus::FRAME_INCOMPLETED: std::cout <<	"FRAME_INCOMPLETED"	 << std::endl; break;
			case nFrameStatus::FRAME_ERROR: std::cout	<<		"FRAME_ERROR"		 << std::endl; _reconnections++; break;
			default: break;
		}
		PrinterController::reconnect();
	}
	else {
		_reconnections = 0;
	}

	return success;
}

int TijMonitor::maxReconnections() const
{
	return _maxReconnections;
}

void TijMonitor::setMaxReconnections(int maxReconnections)
{
	_maxReconnections = maxReconnections;
}

void TijMonitor::start()
{
	if (_running.load()) {
		stop();
	}
	_th = std::thread(&TijMonitor::run, this);
}

void TijMonitor::stop()
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
