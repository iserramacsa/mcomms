#include "tijprintercontroller.h"
#include "mprotocol/mprotocol.h"
#include "mprotocol/mcommandsfactory.h"
#include "network/networknode.h"
#include "tijobserver.h"

#include <iostream>

#define MPROTOCOL_PORT	9991

using namespace Macsa;
using namespace Macsa::Network;

TijController::TijController(const std::string &id, const std::string &address) :
	PrinterController(id, address, MPROTOCOL_PORT),
	_deleteAfterSend(true),
	_factory(_printer, _liveFlags)
{}

Printers::ErrorCode TijController::getLive()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getLiveCommand();
	if (cmd) {
		if (send(cmd, error) && error == Printers::ErrorCode_n::SUCCESS) {
			if (_liveFlags.statusChanged)
				std::cout << "statusChanged" << std::endl;
			if (_liveFlags.configChanged)
				std::cout << "configChanged" << std::endl;
			if (_liveFlags.filesChanged)
				std::cout << "filesChanged" << std::endl;
			if (_liveFlags.fontsChanged)
				std::cout << "fontsChanged" << std::endl;
			if (_liveFlags.errorsLogChanged)
				std::cout << "errorsLogChanged" << std::endl;
			if (_liveFlags.userValueChanged)
				std::cout << "userValueChanged" << std::endl;
			if (_liveFlags.isInError)
				std::cout << "isInError" << std::endl;
		}
	}
	return error;
}

Printers::ErrorCode TijController::updateStatus()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getStatusCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

TijController::TijPrinterStatus TijController::printerStatus()
{
	TijPrinterStatus status = TijPrinterStatus::DISCONNECTED;

	if (NetworkNode::status() == NetworkNode::NodeStatus_n::CONNECTED) {
		const Macsa::Printers::Board * board = _printer.board(0);
		if (board == nullptr) {
			board = _printer.board(0);
		}
		board = _printer.board(0);
		if (board != nullptr) {
			if (board->enabled()) {
				if (board->errors().size()) {
					status = TijPrinterStatus::WARNING; // TODO: review
				}
				else {
					status = TijPrinterStatus::RUNNING;
					if (board->printing()){
						status = TijPrinterStatus::PRINTING;
					}
				}
			}
			else {
				status = TijPrinterStatus::STOPPED;
			}
		}
	}

	return status;
}

Printers::ErrorCode TijController::updateErrorsList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getErrorsList();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::updateConfig()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getConfigCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::setDateTime(const time_t &dt)
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.setDateTimeCommand(dt);
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::setEnabled(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setEnabled(enabled);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TijController::setAutoStart(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setAutoStart(enabled);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TijController::setLowLevelOutput(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setLowLevelOutput(enabled);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TijController::setCartridgeBlocked(bool blocked)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setBlocked(blocked);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TijController::setPrintRotated(bool rotated)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setPrintRotated(rotated);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TijController::updateFilesList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getAllFilesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::updateFontsList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getFontsCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::updateUserValues()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getFontsCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::updateMessagesList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getMessagesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::updateImagesList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getImagesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TijController::updateFile(const std::string &filepath, bool rawMode)
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getFileContent(filepath, rawMode);
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

std::vector<std::string> TijController::getDrives()
{
	std::vector<std::string> drives;
	if (_printer.files() != nullptr) {
		drives = _printer.files()->getDrives();
	}
	else{
		drives.clear();
	}
	return drives;
}

std::vector<uint8_t> TijController::getFile(const std::string &filepath)
{
	std::vector<uint8_t> content;
	content.clear();
	if (_printer.files() != nullptr) {
		const Macsa::Printers::File* file = _printer.files()->getFile(filepath);
		if (file){
			content = file->data();
		}
	}
	return content;
}

bool TijController::send(MProtocol::MCommand* cmd, Printers::ErrorCode &/*err*/)
{
	bool success = false;


	std::string tx = cmd->getRequest(_factory.nextId());
	_lastSentStatus = Network::NetworkNode::sendPacket(tx, MPROTOCOL_PORT);
	if (_lastSentStatus == ISocket::FRAME_SUCCESS)
	{
		std::string resp = "";
		_lastSentStatus = Network::NetworkNode::receivePacket(resp, MPROTOCOL_PORT);
		if(_lastSentStatus == ISocket::FRAME_SUCCESS)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			success = _factory.parseResponse(resp, cmd);
			if (success && cmd->getError() == Printers::ErrorCode_n::SUCCESS) {
				checkCommand(cmd->commandName(), cmd->attributes());
			}
			if (!success) {
				std::cout << __FILE__ << " " << cmd->commandName() << " failed on parse response:" << std::endl;
				std::cout << resp << std::endl;
			}
		}
		else {
			std::cout << __FILE__ << " Receive failed: ";
			switch (_lastSentStatus) {
				case ISocket::FRAME_SUCCESS:     std::cerr << "SUCCESS" << std::endl; break;
				case ISocket::FRAME_TIMEOUT:	 std::cerr << "TIMEOUT" << std::endl; break;
				case ISocket::FRAME_INCOMPLETED: std::cerr << "INCOMPLETED" << std::endl; break;
				case ISocket::FRAME_ERROR:		 std::cerr << "ERROR" << std::endl; break;
			}
		}
	}
	else {
		std::cout << __FILE__ << " Send Command failed: ";
		switch (_lastSentStatus) {
			case ISocket::FRAME_SUCCESS:     std::cerr << "SUCCESS" << std::endl; break;
			case ISocket::FRAME_TIMEOUT:	 std::cerr << "TIMEOUT" << std::endl; break;
			case ISocket::FRAME_INCOMPLETED: std::cerr << "INCOMPLETED" << std::endl; break;
			case ISocket::FRAME_ERROR:		 std::cerr << "ERROR" << std::endl; break;
		}
	}
	if(_deleteAfterSend) {
		delete cmd;
	}

	return success;
}

bool TijController::getBaseBoard(Printers::Board& board)
{
	bool valid = (_printer.board(0) != nullptr);
	if (valid) {
		board = (*_printer.board(0));
	}
	return valid;
}

Printers::ErrorCode TijController::changeBoardConfig(const Printers::Board &board)
{
	Printers::ErrorCode error(Printers::ErrorCode_n::PARAM_BOARD_ID_NOT_FOUND);
	MProtocol::MCommand* cmd = _factory.setConfigBoard(board);
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

void TijController::checkCommand(const std::string &cmd, const std::map<std::string,std::string>& attributes)
{
	if (cmd == MSTATUS || cmd == MIOSTATUS || cmd == MERRORS_GET) { // TODO: Split?
		return TijNotifier::notifyStatusChanged();
	}
	if (cmd == MCONFIG_GET) {
		return notifyConfigChanged();
	}
	if (cmd == MFILES_GET_LIST) {
		if (attributes.find(MFILES_GET_LIST_TYPE_ATTR) != attributes.end()){
			if (attributes.at(MFILES_GET_LIST_TYPE_ATTR).find(NISX_FILTER) != std::string::npos) {
				notifyFilesListChanged();
			}
			if (attributes.at(MFILES_GET_LIST_TYPE_ATTR).find(FONTS_FILTER) != std::string::npos) {
				notifyFontsChanged();
			}
		}
		return;
	}
	if (cmd == MFILES_GET) {
		if (attributes.find(MFILES_DEVICE_UNIT) != attributes.end() &&
			attributes.find(MFILES_FILE_PATH) != attributes.end())
		{
			return notifyFileChanged(attributes.at(MFILES_DEVICE_UNIT), attributes.at(MFILES_FILE_PATH));
		}
	}
	if (cmd == MMESSAGE_USER_FIELD_GET) {
		return notifyUserValuesChanged(); //Attribute filename??
	}
	if (cmd == MERRORS_LOGS) {
		return notifyErrorsLogsChanged();
	}

}

std::vector<std::string> TijController::getFiles(const std::string &extension)
{
	std::vector<std::string> files;
	if (_printer.files() != nullptr){
		files = _printer.files()->getAllFiles(extension);
	}
	else{
		files.clear();
	}
	return files;
}

std::vector<std::string> TijController::getFiles(const std::string &drive, const std::string &folder)
{
	std::vector<std::string> drives;
	if (_printer.files() != nullptr) {
		drives = _printer.files()->getFiles(drive, folder);
	}
	else{
		drives.clear();
	}
	return drives;
}

