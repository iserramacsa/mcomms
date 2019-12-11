#include "tijprintercontroller.h"
#include "mprotocol/mcommandsfactory.h"
#include "network/tcpsocket.h"

#define MPROTOCOL_PORT	9991

using namespace Macsa;
using namespace Macsa::Network;

TijPrinterController::TijPrinterController(const std::string &id, const std::string &address) :
	Network::NetworkNode(id, address),
	_factory(_printer)
{
	_running.store(false);
	addConnection(ISocket::TCP_SOCKET, MPROTOCOL_PORT);
}

TijPrinterController::~TijPrinterController()
{}

bool TijPrinterController::connect()
{
	TcpSocket* socket = dynamic_cast<TcpSocket*>(NetworkNode::socket(ISocket::TCP_SOCKET, MPROTOCOL_PORT));
	if (socket != nullptr){
		socket->connect(address(), MPROTOCOL_PORT);
		return (socket->status() == ISocket::CONNECTED);
	}
	else {
		return false;
	}
}

bool TijPrinterController::disconnect()
{
	TcpSocket* socket = dynamic_cast<TcpSocket*>(NetworkNode::socket(ISocket::TCP_SOCKET, MPROTOCOL_PORT));
	if (socket != nullptr){
		socket->close();
		return (socket->status() == ISocket::UNKNOWN);
	}
	else{
		return false;
	}
}

time_t TijPrinterController::getDateTime()
{
	time_t dt = _printer.dateTime();
//	if(send(_factory.getLiveCommand()->getRequest())) { //TODO
//		dt = _printer.dateTime();
//	}

	return dt;
}

bool TijPrinterController::setDateTime(tm dt)
{
	time_t datetime = mktime(&dt);
	_printer.setDateTime(datetime);
	MProtocol::MCommand* cmd = _factory.setDateTimeCommand();
	if(send(cmd)) {

	}
}


bool TijPrinterController::send(MProtocol::MCommand* cmd)
{
	bool success = false;
	ISocket* socket = NetworkNode::socket(ISocket::TCP_SOCKET, MPROTOCOL_PORT);
	if(socket->status() == ISocket::CONNECTED)
	{
		//TODO check for new command iface funtionality ¿ getRequest or getResponse?
		if (socket->send(cmd->getRequest(_factory.nextId())) == ISocket::FRAME_SUCCESS)
		{
			std::string resp = "";
			if(socket->receive(resp) == ISocket::FRAME_SUCCESS)
			{
//				success = _factory.parse(resp, cmd); //Refactor
			}
		}
	}
	return success;
}
