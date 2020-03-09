#include "tijcontroller.h"
#include "mprotocol/mprotocol.h"
#include "mprotocol/mcommandsfactory.h"
#include "network/networknode.h"
#include "tijobserver.h"

#include <iostream>

#define TRACE_TX 0
#define TRACE_RX 0

#define MPROTOCOL_PORT	9991

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Network;
using namespace Macsa::MProtocol;

TijController::TijController(const std::string &id, const std::string &address) :
	PrinterController(id, address, MPROTOCOL_PORT),
	_factory(_printer, _liveFlags)
{}

void TijController::getLive()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getLiveCommand;
	sendCommand(command);
}

bool TijController::updateStatus()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getStatusCommand;
	return  sendCommand(command);
}

bool TijController::updateErrorsList()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getErrorsList;
	return  sendCommand(command);
}

bool TijController::updateConfig()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getConfigCommand;
	return  sendCommand(command);
}

bool TijController::setDateTime(const time_t &dt)
{
	std::function<MCommand*(MCommandsFactory*, const time_t &)> command = &MCommandsFactory::setDateTimeCommand;
	return  sendCommand(command, dt);
}

bool TijController::setEnabled(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setEnabled(enabled);
		return changeBoardConfig(board);
	}
	return false;
}

bool TijController::setAutoStart(bool enabled)
{	
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setAutoStart(enabled);
		return changeBoardConfig(board);
	}
	return false;
}

bool TijController::setLowLevelOutput(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setLowLevelOutput(enabled);
		return changeBoardConfig(board);
	}
	return false;
}

bool TijController::setCartridgeBlocked(bool blocked)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setBlocked(blocked);
		return changeBoardConfig(board);
	}
	return false;
}

bool TijController::setPrintRotated(bool rotated)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setPrintRotated(rotated);
		return changeBoardConfig(board);
	}
	return false;
}

bool TijController::setUserMessage(const std::string &filepath)
{
	std::function<MCommand*(MCommandsFactory*, const std::string &)> command = &MCommandsFactory::setCurrentMessage;
	return  sendCommand(command, filepath);
}

bool TijController::updateFilesList()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getAllFilesCommand;
	return  sendCommand(command);
}

bool TijController::updateFontsList()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getFontsCommand;
	return  sendCommand(command);
}

bool TijController::updateUserValues()
{
//	std::function<MCommand*()> command = std::bind(&MCommandsFactory::getFontsCommand, &_factory);
//	return  requestCommand(command);
	return false;
}

bool TijController::updateMessagesList()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getMessagesCommand;
	return  sendCommand(command);
}

bool TijController::updateImagesList()
{
	std::function<MCommand*(MCommandsFactory*)> command = &MCommandsFactory::getImagesCommand;
	return  sendCommand(command);
}

bool TijController::updateFile(const std::string &filepath, bool rawMode)
{
	std::function<MCommand*(MCommandsFactory*, const std::string &, const bool&)> command = &MCommandsFactory::getFileContent;
	return  sendCommand(command, filepath, rawMode);
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

bool TijController::send(MCommand* cmd)
{
	bool success = false;

	std::string tx = cmd->getRequest(_factory.nextId());
#if TRACE_TX
	std::cout << __func__ << " TX: " << tx << std::endl;
#endif

	_lastSentStatus = Network::NetworkNode::sendPacket(tx, MPROTOCOL_PORT);
	if (_lastSentStatus == ISocket::FRAME_SUCCESS)
	{
		std::string resp = "";
		_lastSentStatus = Network::NetworkNode::receivePacket(resp, MPROTOCOL_PORT);
		if(_lastSentStatus == ISocket::FRAME_SUCCESS)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			success = _factory.parseResponse(resp, cmd);
			if (success && cmd->getError() == Printers::nErrorCode::SUCCESS) {
				checkCommand(cmd->commandName(), cmd->attributes());
			}
		}
#if TRACE_RX
		std::cout << __func__ << " RX: " << resp << std::endl;
#endif
	}
	delete cmd;
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

bool TijController::changeBoardConfig(const Printers::Board &board)
{
	std::function<MCommand*(MCommandsFactory*, const Printers::Board&)> command = &MCommandsFactory::setConfigBoard;
	return  sendCommand(command, board);
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


template<typename ... Args>
bool TijController::sendCommand(std::function<MCommand*(MCommandsFactory*, const Args& ...)>& command, const Args& ...args)
{
	bool success = false;
	std::function<MCommand*(const Args& ...)> function = std::bind(command, &_factory, args...);
	MCommand* cmd = function(args...);
	if (cmd) {
		success = send(cmd);
	}
	return success;
}
