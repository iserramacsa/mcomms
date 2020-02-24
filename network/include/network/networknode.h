#ifndef MACSA_NETWORK_NETWORK_NODE_H
#define MACSA_NETWORK_NETWORK_NODE_H

#include <vector>
#include <string>
#include "isocket.h"
#include "nodeobserver.h"


namespace Macsa {
	namespace Network {
		///
		/// \brief The NetworkNode class. TODO: add definition
		///
		class NetworkNode {
			public:
				enum NodeStatus_n{
					DISCONNECTED = 0,
					CONNECTING,
					CONNECTED
				};

			public:
				///
				/// \brief NetworkNode constructor withoout a default connection
				/// \param id: Node identifier
				/// \param address: Ip address of network node
				///
				explicit NetworkNode(const std::string& id, const std::string& address = "");

				///
				/// \brief NetworkNode constructor with a default connection
				/// \param id: Node identifier
				/// \param connection: Default connection
				///
				// explicit NetworkNode(const std::string& id, ISocket* connection);

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
				/// \return CONNECTED if the socket exist and is connected, CONNECTING if node is trying to
				/// reconnect to remote device. If socket is not connected yet or if maximum reconnections
				/// attempted socket status will return DISCONNECTED.
				///
				virtual NodeStatus_n status(ISocket::SocketType_n type, uint16_t port) const;

				///
				/// \brief getter for connections
				/// \return number of stored connections
				///
				virtual inline int connections() const { return static_cast<int>(_connections.size()); }

				//Client side methods
				///
				/// \brief Socket connection method. If the socket is not stored in the internal connections,
				/// the socket will be build and connect. If the connection were successfull, the socket will
				/// be added to the connections list, otherwise the socket will be deleted.
				/// \param type: Socket type
				/// \param port: port to connect
				/// \return true if the socket returns connected, otherwise returns false
				///
				virtual bool connect(ISocket::SocketType_n type, uint16_t port);

				///
				/// \brief Socket disconnection method. Disconnects and removes a stored tcp connection
				///	with port param.
				/// \param port: Port of the connection
				/// \return true if connection exist and is disconnected
				///
				virtual bool disconnect(uint16_t port);

				///
				/// \brief Closes the node. Closes all the internal connections and access points
				///
				virtual void close();

				///
				/// \brief Send a frame with stored connected tcp connection.
				/// \param tx: Message to send.
				/// \param port: port of the connection.
				/// \param timeout: send timeout. Zero by default.
				/// \return Socket frame transmision status.
				///
				virtual ISocket::nSocketFrameStatus sendPacket(const std::string& tx, uint16_t port, int timeout = NO_WAIT);

				///
				/// \brief Receive a frame of stored connected tcp connection.
				/// \param Rx: Message received.
				/// \param port: port of the connection.
				/// \param timeout: recieve timeout. 10 seconds by default.
				/// \return Socket frame transmision status.
				///
				virtual ISocket::nSocketFrameStatus receivePacket(std::string& rx, uint16_t port, int timeout = DEFAULT_TIMEOUT);

				///
				/// \brief Send a datagram with stored connected udp connection.
				/// \param tx: Message to send.
				/// \param port: port of the connection.
				/// \param timeout: send timeout. Zero by default.
				/// \return Socket frame transmision status.
				///
				virtual ISocket::nSocketFrameStatus sendDatagram(const std::string tx, uint16_t port, int timeout = NO_WAIT);

				///
				/// \brief Receive a datagram of binded udp connection.
				/// \param Rx: Message received.
				/// \param remoteAddr: Remote address of received datagram
				/// \param port: port of the connection.
				/// \param timeout: recieve timeout. 10 seconds by default.
				/// \return Socket frame transmision status.
				///
				virtual ISocket::nSocketFrameStatus receiveDatagram(std::string& rx, std::string &remoteAddr, uint16_t port, int timeout = DEFAULT_TIMEOUT);

				///
				/// \brief getter for access points
				/// \return number of active servers (Access point)
				///
				virtual inline int accessPoints() const { return static_cast<int>(_accessPoints.size()); }


				//TODO
				/* ¿¿ Needed ?? */ // ISocket* socket(ISocket::SocketType_n type, uint16_t port) const;

				//Connections list Methods
				///
				/// \brief Creates a new socket and adds in the connections list.
				/// \param type: Type of the socket to create.
				/// \param port: Port to connect the socket.
				/// \return true if the connection doesn't exist and can be created and added successfully.
				///
				bool addConnection(ISocket::SocketType_n type, uint16_t port);
				///
				/// \brief Aadds the socket connection in the connections list.
				/// \param connection: valid socket to add.
				/// \return true if the connection doesn't exist and can be added successfully.
				///
				bool addConnection(ISocket* connection);

				///
				/// \brief Remove the specified type and port connection if exist
				/// \param type: Type of the socket to remove.
				/// \param port: Port to connect the socket.
				/// \return true if the connection exist and is removed
				///
				bool removeConnection(ISocket::SocketType_n type, uint16_t port);
				///
				/// \brief Remove the specified socket connection if exist
				/// \param connection: socket related wth the connection
				/// \return true if the connection exist and is removed
				///
				bool removeConnection(ISocket* connection);


				bool attach(NodeObserver* observer);
				bool detach(NodeObserver* observer);

				//Operators
				virtual inline bool operator == (const NetworkNode& other){ return  equal(other); }
				virtual inline bool operator != (const NetworkNode& other){ return !equal(other); }

			protected:
				std::vector<ISocket*> _connections;
				std::vector<ISocket*> _accessPoints;
				std::string _id;
				std::string _address;
				std::vector<NodeObserver*> _observers;

				//Server control methods
				///
				/// \brief Initialize a socket of specified type in the specified port. In case of tcp sockets
				/// the socket will be binded and start listening for new connections. The nwee socket will be added
				/// as an acces point of the current node.
				/// \param type. Type of the specified socket to initialize as a listening socket
				/// \param port. Port to bind the specified socket.
				/// \return true if the initialization was succesfull.
				///
				virtual bool initServer(ISocket::SocketType_n type, uint16_t port);

				///
				/// \brief accept method for tcp initialized server on specified port
				/// \param port of the tcp server to accept new connections
				/// \return a pointer to a socket of the connected client
				///
				virtual ISocket* accept(uint16_t port);

				///
				/// \brief Close the socket stored in accessPoints vector and removes from the vector.
				/// This method deletes the stored socket.
				/// \param type: Type of the specified server to close.
				/// \param port: Port of the specified socket to close.
				/// \return true if the access point exist and is closed and deleted.
				///
				virtual bool stopServer(ISocket::SocketType_n type, uint16_t port);

				//Notifiers
				virtual void notifyConnected() const;
				virtual void notifyDisconnected() const;


				//Socket helpers
				///
				/// \brief Initialize a socket of the specified type, asociated to the specified port
				/// \param type: Type of the socket to create
				/// \param port: Port where the socket have to associate.
				/// \return new TcpSocket or UdpSocket depending on the type.
				///
				virtual ISocket* initSocket(ISocket::SocketType_n type, uint16_t port);

				//Helpers
				///
				/// \brief equal method. Check if other node is the same as this
				/// \param other. Refence to other node.
				/// \return true if other is the same as this
				///
				bool equal(const NetworkNode& other);

				///
				/// \brief exist. Helper method to check if the specified socket is not null and stored in the connections vector.
				/// \param sock. Pointer to ISocket to check.
				/// \return true if the socket is not null and stored in the connections vector, otherwise return false;
				///
				inline bool exist(const ISocket* sock) const { return (sock != nullptr && (connection(sock->type(), sock->port()) != _connections.end()));}
				///
				/// \brief connection. Helper method to find in the connections vector
				/// \param type: Specified socket type
				/// \param port: Specified socket port
				/// \return const iterator in connections vector
				///
				inline std::vector<ISocket*>::const_iterator connection(ISocket::SocketType_n type, uint16_t port) const {return find(_connections, type, port);}
				///
				/// \brief accessPoint. Helper method to find in the accessPoints vector
				/// \param type: Specified server type
				/// \param port: Specified server port
				/// \return const iterator in accessPoints vector
				///
				inline std::vector<ISocket*>::const_iterator accessPoint(uint16_t port) const;

				///
				/// \brief find. Generic find algorithm
				/// \param list: Vector to look for a socket
				/// \param type: Specified socket type
				/// \param port: Specified socket port
				/// \return const iterator in the specified vector
				///
				std::vector<ISocket*>::const_iterator find(const std::vector<ISocket*>& list, ISocket::SocketType_n type, uint16_t port) const;

				///
				/// \brief Access method to observers vector
				/// \param id: Id to the expected observer
				/// \return const_iterator to observer on observers vector
				///
				std::vector<NodeObserver*>::const_iterator observer(unsigned id) const;
				///
				/// \brief Overloaded access method to observers vector
				/// \param id: Id to the expected observer
				/// \return const_iterator to observer on observers vector
				///
				std::vector<NodeObserver*>::iterator observer(unsigned id);

				///
				/// \brief checkStatus. Helper method to loop over the connections and creates a simplified node status
				/// \return CONNECTED if at least one connection is connected, otherwise returns DISCONNECTED
				///
				NodeStatus_n checkStatus() const;

			private:
				// hidden constructors
				NetworkNode(){}
				NetworkNode(const NetworkNode&){}
		};
	}
}


#endif //MACSA_NETWORK_NETWORK_NODE_H
