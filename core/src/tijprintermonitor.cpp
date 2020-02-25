#include "tijprintermonitor.h"
#include "mprotocol/mprotocol.h"
#include "mprotocol/mfiles.h"

using namespace Macsa;
using namespace Macsa::Network;

TijPrinterMonitor::TijPrinterMonitor(const std::string &id, const std::string &address) :
	TijController(id, address)
{
	_deleteAfterSend = false;
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
			if(TijController::send(cmd, _lastError)) {

				// TODO: Add observers and callbacks
//				if (cmd->commandName() == MSTATUS) {
//					statusChanged.emit();
//				}
//				if (cmd->commandName() == MCONFIG_GET) {
//					configChanged.emit();
//				}
//				if (cmd->commandName() == MFILES_GET) {
//					MProtocol::MGetFilesList* files = dynamic_cast<MProtocol::MGetFilesList*>(cmd);
//					if (files->filter().find(NISX_FILTER) != std::string::npos){
//						filesChanged.emit();
//					}
//					if (files->filter().find(FONTS_FILTER) != std::string::npos){
//						fontsChanged.emit();
//					}
//				}
//				// TODO: Add user values changed
////				uvChanged;
//				if (cmd->commandName() == MERRORS_LOGS) {
//					errorsListChanged.emit();
//				}
			}
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
		//if  (userValuesChanged()){} //TODO
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

void TijPrinterMonitor::stop()
{
	_running.store(false);
	{
		std::unique_lock<std::mutex> _lck(_mutex);
		_cv.notify_all();
	}
	_th.join();
}
