#include "network/networknode.h"
#include "network/tcpsocket.h"
#include "network/udpsocket.h"

using namespace Macsa::Network;

NetworkNode::NetworkNode(const std::string &id, const std::string &address)
{
	_id = id;
	_address = address;
}

NetworkNode::NetworkNode(const std::string &id, ISocket* connection)
{
	_id = id;
	if (connection) {
		_connections.push_back(connection);
		_address = connection->address();
	}
	else {
		_address.clear();
	}
}

NetworkNode::~NetworkNode()
{
	close();
}

NetworkNode::NodeStatus_n NetworkNode::status() const
{
	return checkStatus();
}

bool NetworkNode::addConnection(ISocket::SocketType_n type, uint16_t port)
{
	AbstractSocket* asockt = nullptr;
	if (find(type, port) == nullptr)
	{
		if (type == ISocket::TCP_SOCKET)
		{
			TcpSocket* sock = new TcpSocket();
			sock->connect(_address, port);
			asockt = sock;
		}
		else
		{
			UdpSocket* sock = new UdpSocket(port);
			asockt = sock;
		}

		if (asockt != nullptr)
		{
			_connections.push_back(asockt);
		}
	}

	return (asockt != nullptr);
}

bool NetworkNode::addConnection(ISocket *socket)
{
	if (socket->address().compare(_address) == 0){
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

	std::vector<ISocket*>::iterator it = socket(type, port);

	if (it != _connections.end())
	{
		ISocket* socket = (*it);
		if (socket) {
			delete socket;
			_connections.erase(it);
		}
	}

	return removed;
}

bool NetworkNode::removeConnection(ISocket *socket)
{
	return removeConnection(socket->type(), socket->port());
}

ISocket *NetworkNode::socket(ISocket::SocketType_n type, uint16_t port) const
{
	return find(type, port);
}

void NetworkNode::close()
{
	while (_connections.size()) {
		std::vector<ISocket*>::iterator it = _connections.begin();
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

bool NetworkNode::equal(const NetworkNode &other)
{
	bool equal = false;
	if  (_address.compare(other.address()) == 0) {
		if (_connections.size() == other._connections.size()) {
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
	}

	return equal;
}

bool NetworkNode::exist(ISocket *socket)
{
	bool exist = false;
	for (unsigned int i = 0; i < _connections.size(); i++) {
		ISocket * s = _connections.at(i);
		if (s->port() == socket->port() && s->type() == socket->type()){
			exist = true;
			break;
		}
	}
	return exist;
}

ISocket *NetworkNode::find(ISocket::SocketType_n type, uint16_t port) const
{
	ISocket * sock = nullptr;
	for (unsigned int i = 0; i < _connections.size(); i++) {
		ISocket * s = _connections.at(i);
		if (s->port() == port && s->type() == type){
			sock = s;
			break;
		}
	}
	return sock;
}

std::vector<ISocket*>::iterator NetworkNode::socket(ISocket::SocketType_n type, uint16_t port)
{
	std::vector<ISocket*>::iterator it;
	for (it = _connections.begin(); it != _connections.end(); it++) {
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
