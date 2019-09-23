#ifndef ISOCKET_H
#define ISOCKET_H

#include <stdint.h>
#include <string>

#ifndef nullptr
#define nullptr NULL
#endif

#ifndef VIRTUAL_MOCK
#define VIRTUAL_MOCK
#endif


namespace Macsa {
	namespace Network {
#define BACKLOG_CONNECTIONS	5

#define MIN_IP_SIZE			7
#define IP_NUM_CHARS		4
#define DEFAULT_BUFF_SIZE	2048

#define UDP_PROTOCOL		"udp"
#define TCP_PROTOCOL		"tcp"

#define DEFAULT_TIMEOUT	10000 // 10 seconds in ms
#define NO_WAIT			0
#define WAIT_FOREVER	-1

		class ISocket
		{
			public:
				enum SocketType_n
				{
					UDP_SOCKET = 0,
					TCP_SOCKET
				};
				enum SocketStatus_n
				{
					ERROR = -1,
					UNKNOWN = 0,
					CREATED,
					INITIATED,
					BINDED,
					LISTENING,
					CONNECTED,
					READY,
				};
				enum nSocketFrameStatus
				{
					FRAME_SUCCESS = 0,
					FRAME_TIMEOUT,
					FRAME_INCOMPLETED,
					FRAME_ERROR,
				};

			public:
				ISocket(SocketType_n type) {
					_type = type;
					_port  = 0;
					_status = UNKNOWN;
				}
				virtual ~ISocket(){;}
				VIRTUAL_MOCK uint16_t port() const {return _port;}
				SocketType_n type() const {return  _type;}
				virtual std::string address() const = 0;
				virtual bool bind(uint16_t port) = 0;
				virtual bool listen() = 0;
				virtual ISocket* accept() = 0;
				virtual bool connect(const std::string& addr, uint16_t port) = 0;
				virtual bool connect(const std::string& addr, const std::string& port) = 0;
				virtual nSocketFrameStatus send(const std::string& tx, int timeout = NO_WAIT) = 0;
				virtual nSocketFrameStatus send(const std::string& tx, const std::string& dest, uint16_t port, int timeout = NO_WAIT) = 0;
				virtual nSocketFrameStatus receive(std::string& rx, int timeout = DEFAULT_TIMEOUT) = 0;
				virtual nSocketFrameStatus receive(std::string& rx, std::string& addr, int timeout = DEFAULT_TIMEOUT) = 0;
				virtual bool close() = 0;
				virtual bool enableBroadcast() = 0;
				virtual SocketStatus_n status() const {return _status;}

				bool operator == (const ISocket& other)	{return equal(other);}
				bool operator != (const ISocket& other)	{return !equal(other);}

			protected:
				uint16_t		_port;
				SocketType_n	_type;
				virtual bool init() = 0;

				bool equal(const ISocket& other) const {
					return _type == other._type &&
							_port == other._port &&
							(address().compare(other.address()) == 0);
				}

				void setStatus(SocketStatus_n status) {
					if (_status != status) {
						_status = status;
					}
				}

			private:
				SocketStatus_n	_status;

		};
	}
}

#endif //ISOCKET_H
