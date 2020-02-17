#include "network/network.h"
#include "network/abstractsocket.h"
#include <algorithm>

using namespace Macsa::Network;

#ifdef NETWORK_VERSION_STR
int MNetwork::versionMajor() {return NETWORK_VERSION_MAJOR;}
int MNetwork::versionMinor() {return NETWORK_VERSION_MINOR;}
int MNetwork::versionPatch() {return NETWORK_VERSION_PATCH;}
std::string MNetwork::version() {return NETWORK_VERSION_STR;}
#endif

MNetwork::MNetwork(ISocket::SocketType_n rootNodeType) :
	NetworkNode("root" , new AbstractSocket(rootNodeType))
{
	_nodes.clear();
}

MNetwork::~MNetwork()
{
	while (_nodes.size()) {
		std::vector<NetworkNode*>::iterator it = _nodes.begin();
		delete (*it);
		_nodes.erase(it);
	}

//	if(_rootNode != nullptr) {
//		delete _rootNode;
//	}
}

bool MNetwork::addNewNode(NetworkNode *node)
{
	bool added = false;
	if (!exist(node)) {
		_nodes.push_back(node);
		added= true;
	}
	return added;
}

NetworkNode *MNetwork::getNodeById(const std::string &id) const
{
	for (unsigned int i = 0; i < _nodes.size(); i++) {
		if(_nodes.at(i)->id().compare(id) == 0) {
			return _nodes.at(i);
		}
	}

	return nullptr;
}

NetworkNode *MNetwork::getNode(const std::string &address) const
{
	for (unsigned int i = 0; i < _nodes.size(); i++) {
		if(_nodes.at(i)->address().compare(address) == 0) {
			return _nodes.at(i);
		}
	}

	return nullptr;
}

NetworkNode *MNetwork::getNode(unsigned int index) const
{
	NetworkNode * node = nullptr;
	if (index < _nodes.size()){
		node = _nodes.at(index);
	}
	return node;
}

int MNetwork::getNodeIdx(NetworkNode *node) const
{
	int idx = -1;

	for (unsigned int i = 0; i < _nodes.size(); i++) {
		if (_nodes.at(i) == node){
			idx = static_cast<int>(i);
			break;
		}
	}

	return idx;
}

NetworkNode::NodeStatus_n MNetwork::status() const
{
	for (unsigned int i = 0; i < _nodes.size(); i++) {
		if (_nodes.at(i)->status() == CONNECTED){
			return CONNECTED;
		}
	}
	return DISCONNECTED;
}

bool MNetwork::removeNode(NetworkNode *node)
{
	bool removed = false;
	if (node != nullptr && exist(node)) {
		for (std::vector<NetworkNode*>::iterator it = _nodes.begin(); it != _nodes.end(); it++)
		{
			if (*(*it) == *node) {
				delete (*it);
				_nodes.erase(it);
				removed = true;
				break;
			}
		}
	}

	return removed;
}

bool MNetwork::removeNode(std::string nodeId)
{
	return removeNode(find(nodeId));
}


bool MNetwork::exist(NetworkNode *node)
{
	return (findByAdrress(node->address()) != nullptr);
}

NetworkNode *MNetwork::find(const std::string& name) const
{
	NetworkNode * node = nullptr;

	if (name.length()) {
		auto found = [name](NetworkNode* n) {
			return(n->id().compare(name) == 0);
		};

		std::vector<NetworkNode*>::const_iterator it = std::find_if(_nodes.begin(), _nodes.end(), found);

		if (it != _nodes.end()) {
			node = *it;
		}
	}

	return node;
}

NetworkNode *MNetwork::findByAdrress(const std::string &address) const
{
	NetworkNode * node = nullptr;
	auto found = [&](NetworkNode* n) {
		return (n->address().compare(address) == 0);
	};

	std::vector<NetworkNode*>::const_iterator it = std::find_if(_nodes.begin(), _nodes.end(), found);

	if (it != _nodes.end()) {
		node = *it;
	}

	return node;
}
