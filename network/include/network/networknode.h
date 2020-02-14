#ifndef INETWORK_NODE_H
#define INETWORK_NODE_H

#include <vector>
#include <string>
#include "isocket.h"

namespace Macsa {
	namespace Network {
		///
		/// \brief The NetworkNode class.
		///
		class NetworkNode {
			public:
				enum NodeStatus_n{
					DISCONNECTED = 0,
					CONNECTED
				};

			public:
				///
				/// \brief NetworkNode constructor withoout a default connection
				/// \param id: Node identifier
				/// \param address: Ip address of network node
				///
				explicit NetworkNode(const std::string& id, const std::string& address);
				///
				/// \brief NetworkNode constructor with a default connection
				/// \param id: Node identifier
				/// \param connection: Default connection
				///
				explicit NetworkNode(const std::string& id, ISocket* connection);
				///
				/// \brief ~NetworkNode Destructor
				///
				virtual ~NetworkNode();

				/* Class Status getters */
				///
				/// \brief Identifier getter
				/// \return string with node identifier
				///
				inline std::string id()	  const {return _id.c_str();}
				///
				/// \brief Ip Address getter
				/// \return Address of this network node
				///
				inline std::string address() const {return _address;}
				///
				/// \brief Status of this network node. This is a unified status of the node connections
				/// \return CONNECTED if at least one connection is connected, DISCONNECTED if all connections
				///			are disconnected.
				///
				virtual NodeStatus_n status() const { return checkStatus();	}
				///
				/// \brief Simplified status of ISocket status.
				/// \param type: Socket type
				/// \param port: Socket port
				/// \return CONNECTED if the socket exist and is connected else returns DISCONNECTED.
				///
				virtual NodeStatus_n status(ISocket::SocketType_n type, uint16_t port) const;
				virtual int connections() const;
				ISocket* socket(ISocket::SocketType_n type, uint16_t port) const; //ToDo Needed??

				//Client side methods
				virtual bool connect(ISocket::SocketType_n type, uint16_t port);
				virtual bool disconnect(uint16_t port);
				virtual void close();


				//Connections list Methods
				bool addConnection(ISocket::SocketType_n type, uint16_t port);
				bool addConnection(ISocket* connection);

				bool removeConnection(ISocket::SocketType_n type, uint16_t port);
				bool removeConnection(ISocket* connection);

				//Operators
				virtual bool operator == (const NetworkNode& other);
				virtual bool operator != (const NetworkNode& other);

			protected:
				NetworkNode(){} // Hidde default constructor
				NetworkNode(const NetworkNode&){} // Hidde copy constructor

				std::vector<ISocket*> _connections;
				std::vector<ISocket*> _accessPoints;
				std::string _id;
				std::string _address;

				//Server control methods
				virtual bool initServer(uint16_t port);
				virtual ISocket* accept(uint16_t port);

				//Helpers
				bool equal(const NetworkNode& other);
				inline bool exist(const ISocket* sock) const { return (sock != nullptr && (connection(sock->type(), sock->port()) != _connections.end()));}
				inline std::vector<ISocket*>::const_iterator connection(ISocket::SocketType_n type, uint16_t port) const {return find(_connections, type, port);}
				inline std::vector<ISocket*>::const_iterator accessPoints(uint16_t port) const {return find(_accessPoints, ISocket::TCP_SOCKET, port);}

				std::vector<ISocket*>::const_iterator find(const std::vector<ISocket*>& list, ISocket::SocketType_n type, uint16_t port) const;

				NodeStatus_n checkStatus() const;
		};
	}
}

#endif //INETWORK_NODE_H
