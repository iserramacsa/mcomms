#include "tijprintercontroller.h"
#include "mprotocol/mcommandsfactory.h"
#include "network/isocket.h"
#include "network/tcpsocket.h"

#include <iostream>

#define MPROTOCOL_PORT	9991

using namespace Macsa;
using namespace Macsa::Network;

TIJPrinterController::TIJPrinterController(const std::string &id, const std::string &address) :
	PrinterController(id, address, MPROTOCOL_PORT),
	_factory(_printer, _liveFlags)
{}

Printers::ErrorCode TIJPrinterController::getLive()
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

Printers::ErrorCode TIJPrinterController::updateStatus()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getStatusCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

TIJPrinterController::TIJPrinterStatus TIJPrinterController::printerStatus()
{
	TIJPrinterStatus status = TIJPrinterStatus::DISCONNECTED;

	if (NetworkNode::status() == NetworkNode::NodeStatus_n::CONNECTED) {
		const Macsa::Printers::Board * board = _printer.board(0);
		if (board == nullptr) {
			board = _printer.board(0);
		}
		board = _printer.board(0);
		if (board != nullptr) {
			if (board->enabled()) {
				if (board->errors().size()) {
					status = TIJPrinterStatus::WARNING; // TODO: review
				}
				else {
					status = TIJPrinterStatus::RUNNING;
					if (board->printing()){
						status = TIJPrinterStatus::PRINTING;
					}
				}
			}
			else {
				status = TIJPrinterStatus::STOPPED;
			}
		}
	}

	return status;
}

Printers::ErrorCode TIJPrinterController::updateErrorsList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getErrorsList();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateConfig()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getConfigCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::setDateTime(const time_t &dt)
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.setDateTimeCommand(dt);
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::setEnabled(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setEnabled(enabled);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TIJPrinterController::setAutoStart(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setAutoStart(enabled);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TIJPrinterController::setLowLevelOutput(bool enabled)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setLowLevelOutput(enabled);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TIJPrinterController::setCartridgeBlocked(bool blocked)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setBlocked(blocked);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TIJPrinterController::setPrintRotated(bool rotated)
{
	Printers::Board board(0, &_printer);
	if (getBaseBoard(board)){
		board.setPrintRotated(rotated);
		return changeBoardConfig(board);
	}
	return Printers::ErrorCode(Printers::PARAM_BOARD_ID_NOT_FOUND);
}

Printers::ErrorCode TIJPrinterController::updateFilesList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getAllFilesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateFontsList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getFontsCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateMessagesList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getMessagesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateImagesList()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getImagesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateFile(const std::string &filepath, bool rawMode)
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getFileContent(filepath, rawMode);
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

std::vector<std::string> TIJPrinterController::getDrives()
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

std::vector<uint8_t> TIJPrinterController::getFile(const std::string &filepath)
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

bool TIJPrinterController::send(MProtocol::MCommand* cmd, Printers::ErrorCode &err)
{
	bool success = false;
	ISocket* socket = NetworkNode::socket(ISocket::TCP_SOCKET, MPROTOCOL_PORT);
	if(socket->status() == ISocket::CONNECTED)
	{
		std::string tx = cmd->getRequest(_factory.nextId());
		if (socket->send(tx) == ISocket::FRAME_SUCCESS)
		{
			std::string resp = "";
			ISocket::nSocketFrameStatus status = socket->receive(resp);
			if(status == ISocket::FRAME_SUCCESS)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				std::cout << tx << std::endl;
				success = _factory.parseResponse(resp, err);
			}
			else {
				std::cerr << __func__ << " Receive failed: ";
				switch (status) {
					case ISocket::FRAME_SUCCESS:     std::cerr << "SUCCESS" << std::endl; break;
					case ISocket::FRAME_TIMEOUT:	 std::cerr << "TIMEOUT" << std::endl; break;
					case ISocket::FRAME_INCOMPLETED: std::cerr << "INCOMPLETED" << std::endl; break;
					case ISocket::FRAME_ERROR:		 std::cerr << "ERROR" << std::endl; break;
				}
			}
		}
	}
	return success;
}



bool TIJPrinterController::getBaseBoard(Printers::Board& board)
{
	bool valid = (_printer.board(0) != nullptr);
	if (valid) {
		board = (*_printer.board(0));
	}
	return valid;
}

Printers::ErrorCode TIJPrinterController::changeBoardConfig(const Printers::Board &board)
{
	Printers::ErrorCode error(Printers::ErrorCode_n::PARAM_BOARD_ID_NOT_FOUND);
	MProtocol::MCommand* cmd = _factory.setConfigBoard(board);
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

std::vector<std::string> TIJPrinterController::getFiles(const std::string &extension)
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

std::vector<std::string> TIJPrinterController::getFiles(const std::string &drive, const std::string &folder)
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

