#include "tijprintermonitor.h"

using namespace Macsa;
using namespace Macsa::Network;

TijPrinterMonitor::TijPrinterMonitor(const std::string &id, const std::string &address) :
	TIJPrinterController(id, address)
{
	_th = std::thread(&TijPrinterMonitor::run, this);
}

TijPrinterMonitor::~TijPrinterMonitor()
{
	stop();
}

void TijPrinterMonitor::run()
{
	_running.store(true);

	while (_running.load()) {
		{
			std::unique_lock<std::mutex> _lck(_mutex);
			if (_cv.wait_for(_lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
				_commands.push_back(_factory.getLiveCommand());
			}
		}
		while (_commands.size()) {
			MProtocol::MCommand* cmd = (*_commands.begin());
			if(TIJPrinterController::send(cmd, _lastError)) {

			}
			delete cmd;
			_commands.pop_front();
		}

		if (isStatusChanged()) {
			TIJPrinterController::updateStatus();
		}
		if (isConfigChanged()) {
			TIJPrinterController::updateConfig();
		}
		if (isFilesChanged()) {
			TIJPrinterController::updateFilesList();
		}
		if (isFontsChanged())  {
			TIJPrinterController::updateFontsList();
		}
		//if  (userValuesChanged()){} //TODO
		if (isErrorsLogsChanged()) {
			TIJPrinterController::updateErrorsList();
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

void TijPrinterMonitor::stop()
{
	_running.store(false);
	{
		std::unique_lock<std::mutex> _lck(_mutex);
		_cv.notify_all();
	}
	_th.join();
}
