#include "tijprintercontroller.h"
#include "mprotocol/mcommandsfactory.h"
#include "network/isocket.h"
#include "network/tcpsocket.h"

#define MPROTOCOL_PORT	9991

using namespace Macsa;
using namespace Macsa::Network;

TIJPrinterController::TIJPrinterController(const std::string &id, const std::string &address) :
	PrinterController(id, address, MPROTOCOL_PORT),
	_factory(_printer)
{}

#include <iostream>
Printers::ErrorCode TIJPrinterController::getLive()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getLiveCommand();
	if (cmd) {
		if (send(cmd, error) && error == Printers::ErrorCode_n::SUCCESS) {
			_liveFlags = _factory.liveFlags();
		}
		std::cout << "statusChanged:    " << _liveFlags.statusChanged << std::endl;
		std::cout << "configChanged:    " << _liveFlags.configChanged << std::endl;
		std::cout << "filesChanged:     " << _liveFlags.filesChanged << std::endl;
		std::cout << "fontsChanged:     " << _liveFlags.fontsChanged << std::endl;
		std::cout << "errorsLogChanged: " << _liveFlags.errorsLogChanged << std::endl;
		std::cout << "userValueChanged: " << _liveFlags.userValueChanged << std::endl;
		std::cout << "isInError:        " << _liveFlags.isInError << std::endl;
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

std::string TIJPrinterController::printerStatus()
{
	std::string status = "---";

	if (NetworkNode::status() == NetworkNode::NodeStatus_n::CONNECTED) {
		const Macsa::Printers::Board * board = _printer.board(0);
		if (board == nullptr) {
			updateStatus();
			board = _printer.board(0);
		}
		board = _printer.board(0);
		if (board != nullptr) {
			if (board->enabled()) {
				status = "Running";
				if (board->printing()){
					status = "Printing";
				}
			}
			else {
				status = "Stopped";
			}
		}
	}
	else {
		status = "Disconnected";
	}

	return status;
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


bool TIJPrinterController::send(MProtocol::MCommand* cmd, Printers::ErrorCode &err)
{
	bool success = false;
	ISocket* socket = NetworkNode::socket(ISocket::TCP_SOCKET, MPROTOCOL_PORT);
	if(socket->status() == ISocket::CONNECTED)
	{
		if (socket->send(cmd->getRequest(_factory.nextId())) == ISocket::FRAME_SUCCESS)
		{
			std::string resp = "";
			if(socket->receive(resp) == ISocket::FRAME_SUCCESS)
			{
				success = _factory.parse(resp, err);
			}
		}
	}
	return success;
}

