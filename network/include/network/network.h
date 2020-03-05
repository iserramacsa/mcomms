#ifndef MACSA_NETWORK_MNETWORK_H
#define MACSA_NETWORK_MNETWORK_H

#include "networknode.h"
#include "network/networknotifier.h"
#include <vector>

namespace Macsa {
	namespace Network {
		class MNetwork : public NetworkNotifier, protected NetworkNode {
			public:
                MNetwork();
				virtual ~MNetwork();

				static int versionMajor();
				static int versionMinor();
				static int versionPatch();
				static std::string version();

				bool addNewNode(NetworkNode* node);
				bool removeNode(NetworkNode* node);
				bool removeNode(std::string nodeId);

				NetworkNode* getNodeById(const std::string& id) const;
                NetworkNode* getNodeByAddress(const std::string& address) const;
				NetworkNode* getNode(unsigned int index) const;
				int getNodeIdx(NetworkNode* node) const;

				virtual nNodeStatus status() const;
				virtual inline unsigned int size() const {return static_cast<unsigned int>(_nodes.size());}

			protected:
				bool exist(NetworkNode* node);
				NetworkNode* find(const std::string &name) const;
				NetworkNode* findByAddress(const std::string &address) const;

			protected:
				std::vector<NetworkNode*> _nodes;
		};
	}
}

#endif //MACSA_NETWORK_MNETWORK_H
