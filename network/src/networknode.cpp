#include "network/networknode.h"
#include "network/nodeobserver.h"
#include "tcpsocket.h"
#include "udpsocket.h"

using namespace Macsa::Network;

NetworkNode::NetworkNode(const std::string &id, const std::string &address)
{
	_id = id;
	_address = address;
	_status = DISCONNECTED;
}

NetworkNode::~NetworkNode()
{
	close();
}

NetworkNode::NodeStatus_n NetworkNode::status(ISocket::nSocketType type, uint16_t port) const
{
	NetworkNode::NodeStatus_n status = NetworkNode::DISCONNECTED;
	std::vector<ISocket*>::const_iterator it = connection(type, port);
	if (it != _connections.end()) {
		status = ((*it)->status() == ISocket::CONNECTED) ? NetworkNode::CONNECTED : NetworkNode::DISCONNECTED;
	}
	return status;
}



bool NetworkNode::connect(ISocket::nSocketType type, uint16_t port)
{
	bool connected = false;
	std::vector<ISocket*>::const_iterator it = connection(type, port);

	setStatus(CONNECTING);
	if (it != _connections.end()){
		connected = ((*it)->status() >= ISocket::CONNECTED);
		if(!connected) {
			connected = (*it)->connect(_address, port);
		}
	}
	else {
		ISocket* socket = initSocket(type, port);
		if (socket != nullptr) {
			connected = socket->connect(_address, port);
		}
		if (connected) {
			addConnection(socket);
		}

	}

	setStatus(connected ? CONNECTED : DISCONNECTED);

	return connected;

}

bool NetworkNode::disconnect(uint16_t port)
{
	bool disconnected = false;
	std::vector<ISocket*>::const_iterator it = connection(ISocket::TCP_SOCKET, port);
	if (it != _connections.end()) {
		TcpSocket* socket = dynamic_cast<TcpSocket*>(*it);
		if (socket){
			disconnected = socket->close();
			removeConnection(socket);
		}
	}

	setStatus(DISCONNECTED);

	return disconnected ;
}

bool NetworkNode::addConnection(ISocket::nSocketType type, uint16_t port)
{
	AbstractSocket* asockt = nullptr;
	if (connection(type, port) == _connections.end())
	{
		asockt = dynamic_cast<AbstractSocket*>(initSocket(type, port));
		if (asockt != nullptr)
		{
			_connections.push_back(asockt);
		}
	}

	return (asockt != nullptr);
}

bool NetworkNode::addConnection(ISocket *socket)
{
	if (!exist(socket) && socket->address() == _address)
	{
		_connections.push_back(socket);
		setStatus((socket->status() == ISocket::CONNECTED) ? CONNECTED : DISCONNECTED);
		return true;
	}

	return false;
}

bool NetworkNode::removeConnection(ISocket::nSocketType type, uint16_t port)
{
	bool removed = false;

	std::vector<ISocket*>::const_iterator it = connection(type, port);

	if (it != _connections.end())
	{
		int nConns = connections();
		ISocket* socket = (*it);
		if (socket) {
			delete socket;
			_connections.erase(it);
		}
		removed = (connections() == (nConns - 1));
	}

	return removed;
}

bool NetworkNode::removeConnection(ISocket *socket)
{
	return removeConnection(socket->type(), socket->port());
}

// TODO: Remove
// ISocket *NetworkNode::socket(ISocket::nSocketType type, uint16_t port) const
// {
// 	std::vector<ISocket*>::const_iterator it = connection(type, port);
// 	if (it != _connections.end()) {
// 		return (*it);
// 	}
//
// 	return nullptr;
// }

void NetworkNode::close()
{
	while (_connections.size()) {
		ISocket* s  = _connections.back();
		delete s;
		_connections.pop_back();
	}
	while (_accessPoints.size()) {
		std::vector<ISocket*>::iterator it = _accessPoints.begin();
		delete (*it);
        _accessPoints.erase(it);
	}
}

ISocket::nSocketFrameStatus NetworkNode::sendPacket(const std::string& tx, uint16_t port, int timeout)
{
	ISocket::nSocketFrameStatus status = ISocket::FRAME_ERROR;
	std::vector<ISocket*>::const_iterator it = connection(ISocket::TCP_SOCKET, port);
	if (it != _connections.end()) {
		TcpSocket* socket = dynamic_cast<TcpSocket*>(*it);
		if (socket) {
			status = socket->send(tx, timeout);
		}
	}

	return status;
}

ISocket::nSocketFrameStatus NetworkNode::receivePacket(std::string &rx, uint16_t port, int timeout)
{
	ISocket::nSocketFrameStatus status = ISocket::FRAME_ERROR;
	std::vector<ISocket*>::const_iterator it = connection(ISocket::TCP_SOCKET, port);
	if (it != _connections.end()) {
		TcpSocket* socket = dynamic_cast<TcpSocket*>(*it);
		if (socket) {
			status = socket->receive(rx, timeout);
			if (status == ISocket::FRAME_TIMEOUT) {
				notifyTimeout();
			}
		}
	}

	return status;
}

ISocket::nSocketFrameStatus NetworkNode::sendDatagram(const std::string tx, uint16_t port, int timeout)
{
	ISocket::nSocketFrameStatus status = ISocket::FRAME_ERROR;
	std::vector<ISocket*>::const_iterator it = connection(ISocket::UDP_SOCKET, port);
	if (it != _connections.end()) {
		UdpSocket* socket = dynamic_cast<UdpSocket*>(*it);
		if (socket) {
			status = socket->send(tx, _address, port, timeout);
		}
	}

	return status;
}

ISocket::nSocketFrameStatus NetworkNode::receiveDatagram(std::string &rx, std::string &remoteAddr, uint16_t port, int timeout)
{
	ISocket::nSocketFrameStatus status = ISocket::FRAME_ERROR;
	std::vector<ISocket*>::const_iterator it = connection(ISocket::UDP_SOCKET, port);
	if (it != _connections.end()) {
		UdpSocket* socket = dynamic_cast<UdpSocket*>(*it);
		if (socket && socket->status() >= ISocket::BINDED) {
			status = socket->receive(rx, remoteAddr,timeout);
			if (status == ISocket::FRAME_TIMEOUT) {
				notifyTimeout();
			}
		}
	}

	return status;
}

bool NetworkNode::initServer(ISocket::nSocketType type, uint16_t port)
{
	bool success = false;

    if (accessPoint(port) == _accessPoints.end()) {
        ISocket* server = initSocket(type, port);
        if (server != nullptr) {
            if (server->bind(port)){
                if (type == ISocket::TCP_SOCKET) {
                    success = server->listen();
                }
                else{
                    success = true;
                }
            }

            if (success) {
                _accessPoints.push_back(server);
            }
            else {
                delete server;
            }
        }
	}

	return success;
}

ISocket * NetworkNode::accept(uint16_t port)
{
	AbstractSocket* client = nullptr;

    std::vector<ISocket*>::const_iterator it = accessPoint(port);
    if (it != _accessPoints.end() && (*it)->type() == ISocket::TCP_SOCKET) {
		TcpSocket* svr = dynamic_cast<TcpSocket*>(*it);
		if (svr != nullptr) {
			client = dynamic_cast<AbstractSocket*>(svr->accept());
		}
	}

	return client;
}

bool NetworkNode::stopServer(ISocket::nSocketType type, uint16_t port)
{
    bool success = false;

    std::vector<ISocket*>::const_iterator it = accessPoint(port);
    if (it != _accessPoints.end() && (*it)->type() == type) {
        AbstractSocket* svr = dynamic_cast<AbstractSocket*>(*it);
        if (svr != nullptr) {
            delete svr;
            _accessPoints.erase(it);
            success = true;
        }
    }

	return success;
}

ISocket *NetworkNode::initSocket(ISocket::nSocketType type, uint16_t port)
{
	if (type == ISocket::TCP_SOCKET) {
		return new TcpSocket(port);
	}
	else {
		return new UdpSocket(port);
	}
}

bool NetworkNode::equal(const NetworkNode &other)
{
	bool equal = false;
	if  (_address == other.address()) {
		if (_connections.size() == other._connections.size()) {
			if (_connections.size()){
				for (unsigned int i = 0; i < _connections.size(); i++) {
					ISocket* mySocket = _connections.at(i);
					ISocket* otherSocket = other._connections.at(i);
					if(mySocket != nullptr && otherSocket != nullptr){
						equal  = (*mySocket == *otherSocket);
						if (!equal) {
							break;
						}
					}
				}
			}
			else{
				equal = true;
			}
		}
	}

	return equal;
}

std::vector<ISocket*>::const_iterator NetworkNode::accessPoint(uint16_t port) const
{
    std::vector<ISocket*>::const_iterator it;
    for (it = _accessPoints.begin(); it != _accessPoints.end(); it++) {
        if ((*it)->port() == port) {
            break;
        }
    }
    return it;
}

std::vector<ISocket*>::const_iterator NetworkNode::find(const std::vector<ISocket *>& list, ISocket::nSocketType type, uint16_t port) const
{
	std::vector<ISocket*>::const_iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		if ((*it)->type() == type && (*it)->port() == port) {
			break;
		}
	}
	return it;
}

void NetworkNode::setStatus(const NodeStatus_n &status)
{
	NodeStatus_n current = _status;
	if (checkStatus() == CONNECTED) {
		_status = CONNECTED;
	}
	else {
		_status = status;
	}

	if (current != _status){
		notifyStatusChanged(_status);
	}

}

NetworkNode::NodeStatus_n NetworkNode::checkStatus() const
{
	NodeStatus_n status = DISCONNECTED;

	for (unsigned int i = 0; i < _connections.size(); i++) {
		ISocket * s = _connections.at(i);
		if (s->status() == ISocket::CONNECTED) {
			status = CONNECTED;
			break;
		}
	}

	return status;
}
