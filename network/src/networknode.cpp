#include "network/networknode.h"
#include "tcpsocket.h"
#include "udpsocket.h"

using namespace Macsa::Network;

NetworkNode::NetworkNode(const std::string &id, const std::string &address)
{
	_id = id;
	_address = address;
}

NetworkNode::~NetworkNode()
{
	close();
}

NetworkNode::NodeStatus_n NetworkNode::status(ISocket::SocketType_n type, uint16_t port) const
{
	NetworkNode::NodeStatus_n status = NetworkNode::DISCONNECTED;
	std::vector<ISocket*>::const_iterator it = connection(type, port);
	if (it != _connections.end()) {
		status = ((*it)->status() == ISocket::CONNECTED) ? NetworkNode::CONNECTED : NetworkNode::DISCONNECTED;
	}
	return status;
}

int NetworkNode::connections() const
{
	return static_cast<int>(_connections.size());
}

bool NetworkNode::connect(ISocket::SocketType_n type, uint16_t port)
{
	bool connected = false;
	std::vector<ISocket*>::const_iterator it = connection(type, port);

	if (it != _connections.end()){
		connected = ((*it)->status() <= ISocket::CONNECTED);
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

	return connected;

}

bool NetworkNode::disconnect(uint16_t port)
{
	bool success = false;
	std::vector<ISocket*>::const_iterator it = connection(ISocket::TCP_SOCKET, port);
	if (it != _connections.end()) {
		success = (*it)->close();
		removeConnection((*it));
	}

	return success ;
}

bool NetworkNode::addConnection(ISocket::SocketType_n type, uint16_t port)
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
	std::string address = socket->address();
	if (address == _address) {
		if (!exist(socket))
		{
			_connections.push_back(socket);
			return true;
		}
	}

	return false;
}

bool NetworkNode::removeConnection(ISocket::SocketType_n type, uint16_t port)
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

ISocket *NetworkNode::socket(ISocket::SocketType_n type, uint16_t port) const
{
	std::vector<ISocket*>::const_iterator it = connection(type, port);
	if (it != _connections.end()) {
		return (*it);
	}

	return nullptr;
}

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
		_connections.erase(it);
	}
}

bool NetworkNode::operator == (const NetworkNode &other)
{
	return equal(other);
}

bool NetworkNode::operator != (const NetworkNode &other)
{
	return !equal(other);
}

ISocket *NetworkNode::initSocket(ISocket::SocketType_n type, uint16_t port)
{
	if (type == ISocket::TCP_SOCKET)
	{
		return new TcpSocket();
	}
	else
	{
		return new UdpSocket(port);
	}
}

bool NetworkNode::initServer(uint16_t port)
{
	bool success = false;

	if (accessPoint(port) == _accessPoints.end()) {
		TcpSocket* server = new TcpSocket();
		if (server->bind(port)) {
			success = server->listen();
		}
		if (success) {
			_accessPoints.push_back(server);
		}
	}

	return success;
}

ISocket * NetworkNode::accept(uint16_t port)
{
	AbstractSocket* client = nullptr;

	std::vector<ISocket*>::const_iterator it = accessPoint(port);
	if (it != _accessPoints.end()) {
		TcpSocket* svr = dynamic_cast<TcpSocket*>(*it);
		if (svr != nullptr) {
			client = dynamic_cast<AbstractSocket*>(svr->accept());
		}
	}

	return client;
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

std::vector<ISocket*>::const_iterator NetworkNode::find(const std::vector<ISocket *>& list, ISocket::SocketType_n type, uint16_t port) const
{
	std::vector<ISocket*>::const_iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		if ((*it)->type() == type && (*it)->port() == port) {
			break;
		}
	}
	return it;
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
