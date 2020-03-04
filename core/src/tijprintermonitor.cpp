#include "tijprintermonitor.h"
#include "mprotocol/mprotocol.h"
#include "mprotocol/mfiles.h"

using namespace Macsa;
using namespace Macsa::Network;

TijPrinterMonitor::TijPrinterMonitor(const std::string &id, const std::string &address) :
	TijController(id, address)
{
	_deleteAfterSend = false;
	_running.store(false);
}

TijPrinterMonitor::~TijPrinterMonitor()
{
	stop();
}

bool TijPrinterMonitor::connect()
{
	bool connected = PrinterController::connect();
	if (connected) {
		start();
	}
	return connected;
}

bool TijPrinterMonitor::disconnect()
{
	bool disconnected = PrinterController::disconnect();
	if (NetworkNode::status() == DISCONNECTED) {
		stop();
	}
	return disconnected;
}

#include <iostream>

void TijPrinterMonitor::run()
{
	_running.store(true);

	while (_running.load()) {
		{
			std::unique_lock<std::mutex> _lck(_mutex);
			if (_cv.wait_for(_lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
				_commands.push_back(_factory.getLiveCommand());
			} else if (_running.load() == false){
				break;
			}
		}
		while (_commands.size()) {
			MProtocol::MCommand* cmd = (*_commands.begin());
			send(cmd);
			delete cmd;
			_commands.pop_front();
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

}

bool TijPrinterMonitor::send(MProtocol::MCommand *cmd, Printers::ErrorCode &)
{
	ulong numCommands = _commands.size();
	_commands.push_back(cmd);
	{
		std::unique_lock<std::mutex> _lck(_mutex);
		_cv.notify_one();
	}
	return ((_commands.size() - numCommands) > 0);
}

bool TijPrinterMonitor::send(MProtocol::MCommand *cmd)
{
	bool success = false;

	success = TijController::send(cmd, _lastError);
	if (!success) {
		std::cout << __FUNCTION__ << " Send command " << cmd->commandName() << " failed" << std::endl;
	}

	return success;
}

void TijPrinterMonitor::start()
{
	if (_running.load()) {
		stop();
	}
	_th = std::thread(&TijPrinterMonitor::run, this);
}

void TijPrinterMonitor::stop()
{
	if (_running.load()){
		_running.store(false);
		{
			std::unique_lock<std::mutex> _lck(_mutex);
			_cv.notify_all();
		}
		_th.join();
	}
}
