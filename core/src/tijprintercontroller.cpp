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

TIJPrinterController::~TIJPrinterController()
{}

Printers::ErrorCode TIJPrinterController::getLive()
{
	Printers::ErrorCode error;
	MProtocol::MCommand* cmd = _factory.getLiveCommand();
	if (cmd) {
		send(cmd, error);
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
	std::string status = "unknown";

	if (NetworkNode::status() == NetworkNode::NodeStatus_n::CONNECTED) {
		const Macsa::Printers::Board * board = _printer.board(0);
		if (board == nullptr){
			updateStatus();
		}
		if (board != nullptr) {
			if (board->enabled()) {
				status = "running";
			}
			else {
				status = "stopped";
			}
		}
	}
	else {
		status = "disconnected";
	}

	return status;
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

