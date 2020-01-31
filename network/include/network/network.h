#ifndef MNETWORK_H
#define MNETWORK_H

#include "networknode.h"
#include <vector>

namespace Macsa {
	namespace Network {
		class MNetwork : public NetworkNode {
			public:
				MNetwork(ISocket::SocketType_n rootNodeType = ISocket::TCP_SOCKET);
                                virtual ~MNetwork();

#ifdef NETWORK_VERSION_STR
				static int versionMajor();
				static int versionMinor();
				static int versionPatch();
				static std::string version();
#endif

				bool addNewNode(NetworkNode* node);
				bool removeNode(NetworkNode* node);
				bool removeNode(std::string nodeId);

				NetworkNode* getNodeById(const std::string& id) const;
				NetworkNode* getNode(const std::string& address) const;
				NetworkNode* getNode(unsigned int index) const;
				int getNodeIdx(NetworkNode* node) const;
				virtual NodeStatus_n status() const;
				virtual unsigned int size() const {return static_cast<unsigned int>(_nodes.size());}


			protected:
				bool exist(NetworkNode* node);
				NetworkNode* find(const std::string &name) const;
				NetworkNode* findByAdrress(const std::string &address) const;

			protected:
				std::vector<NetworkNode*> _nodes;
				NetworkNode* _rootNode;
		};
	}
}

#endif //MNETWORK_H
