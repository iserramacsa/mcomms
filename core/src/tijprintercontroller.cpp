#include "tijprintercontroller.h"
#include "mprotocol/mcommandsfactory.h"
#include "network/isocket.h"
#include "network/tcpsocket.h"

#define MPROTOCOL_PORT	9991

using namespace Macsa;
using namespace Macsa::Network;

TIJPrinterController::TIJPrinterController(const std::string &id, const std::string &address) :
	PrinterController(id, address, MPROTOCOL_PORT),
	_factory(_printer, _liveFlags)
{}

#include <iostream>
Printers::ErrorCode TIJPrinterController::getLive()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getLiveCommand();
	if (cmd) {
		if (send(cmd, error) && error == Printers::ErrorCode_n::SUCCESS) {
			std::cout << "statusChanged:    " << _liveFlags.statusChanged << std::endl;
			std::cout << "configChanged:    " << _liveFlags.configChanged << std::endl;
			std::cout << "filesChanged:     " << _liveFlags.filesChanged << std::endl;
			std::cout << "fontsChanged:     " << _liveFlags.fontsChanged << std::endl;
			std::cout << "errorsLogChanged: " << _liveFlags.errorsLogChanged << std::endl;
			std::cout << "userValueChanged: " << _liveFlags.userValueChanged << std::endl;
			std::cout << "isInError:        " << _liveFlags.isInError << std::endl;
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
//			updateStatus();
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
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.setConfigBoardEnabled(enabled);
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateFiles()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getAllFilesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateFonts()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getFontsCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateMessages()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getMessagesCommand();
	if (cmd) {
		send(cmd, error);
	}
	return error;
}

Printers::ErrorCode TIJPrinterController::updateImages()
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
		std::cout << __func__ << "  " << filepath;
		const Macsa::Printers::File* file = _printer.files()->getFile(filepath);
		if (file){
			std::cout << "  => File found" << std::endl;
			content = file->data();
		}
		else
			std::cout << "  => File NOT found" << std::endl;
	}
	return content;
}

#include <iostream>
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

