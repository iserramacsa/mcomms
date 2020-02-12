#ifndef INETWORK_NODE_H
#define INETWORK_NODE_H

#include <vector>
#include <string>
#include "isocket.h"

namespace Macsa {
	namespace Network {
		///
		/// \brief The NetworkNode clas. This class allow to control a socket as a network node and
		/// add or remove connections related with the node with multiple sockets.
		///
		class NetworkNode {
			public:
				enum NodeStatus_n{
					DISCONNECTED = 0,
					CONNECTED
				};

			public:
				explicit NetworkNode(const std::string& id, const std::string& address);
				explicit NetworkNode(const std::string& id, ISocket* connection);
				virtual ~NetworkNode();

				std::string id()	  const {return _id.c_str();}
				std::string address() const {return _address;}
                virtual NodeStatus_n status() const;
                bool addConnection(ISocket::SocketType_n type, uint16_t port);
				bool addConnection(ISocket* socket);
                bool removeConnection(ISocket::SocketType_n type, uint16_t port);
                bool removeConnection(ISocket* socket);
                ISocket* socket(ISocket::SocketType_n type, uint16_t port) const;
                void close();

				virtual bool operator == (const NetworkNode& other);
				virtual bool operator != (const NetworkNode& other);

			protected:
				NetworkNode(){} // Hidde default constructor
				NetworkNode(const NetworkNode&){} // Hidde copy constructor

				std::vector<ISocket*> _connections;
				std::string _id;
				std::string _address;

				bool equal(const NetworkNode& other);
				bool exist(ISocket* socket);
                ISocket* find(ISocket::SocketType_n type, uint16_t port) const;
                std::vector<ISocket*>::iterator socket(ISocket::SocketType_n type, uint16_t port);
				NodeStatus_n checkStatus() const;
		};
	}
}

#endif //INETWORK_NODE_H
