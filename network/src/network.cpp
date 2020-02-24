#include "network/network.h"
#include "abstractsocket.h"
#include <algorithm>

#define ROOT_NODE_ID    "root"

using namespace Macsa::Network;

int MNetwork::versionMajor() {return NETWORK_VERSION_MAJOR;}
int MNetwork::versionMinor() {return NETWORK_VERSION_MINOR;}
int MNetwork::versionPatch() {return NETWORK_VERSION_PATCH;}
std::string MNetwork::version() {return NETWORK_VERSION_STR;}

MNetwork::MNetwork() :
    NetworkNode(ROOT_NODE_ID)
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
		if(_nodes.at(i)->id() == id) {
			return _nodes.at(i);
		}
	}

	return nullptr;
}

NetworkNode *MNetwork::getNodeByAddress(const std::string &address) const
{
	for (unsigned int i = 0; i < _nodes.size(); i++) {
		if(_nodes.at(i)->address() == address) {
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
	return (findByAddress(node->address()) != nullptr);
}

NetworkNode *MNetwork::find(const std::string& name) const
{
	NetworkNode * node = nullptr;

	if (name.length()) {
		auto found = [name](NetworkNode* n) {
			return(n->id() == name);
		};

		std::vector<NetworkNode*>::const_iterator it = std::find_if(_nodes.begin(), _nodes.end(), found);

		if (it != _nodes.end()) {
			node = *it;
		}
	}

	return node;
}

NetworkNode *MNetwork::findByAddress(const std::string &address) const
{
	NetworkNode * node = nullptr;
	auto found = [&](NetworkNode* n) {
		return (n->address() == address);
	};

	std::vector<NetworkNode*>::const_iterator it = std::find_if(_nodes.begin(), _nodes.end(), found);

	if (it != _nodes.end()) {
		node = *it;
	}

	return node;
}
