#include "clientmanager.h"

ClientManager::ClientManager(uint16_t port) :
	Network::MNetwork (Network::ISocket::TCP_SOCKET)
{
	_rootNode->socket()->blind(port)
}

ClientManager::~ClientManager()
{}

