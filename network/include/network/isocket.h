#ifndef MACSA_NETWORK_ISOCKET_H
#define MACSA_NETWORK_ISOCKET_H

#include <stdint.h>
#include <vector>
#include <string>
#include <sstream>

namespace Macsa {
	namespace Network {
#define BACKLOG_CONNECTIONS	5

#define MIN_IP_SIZE			7
#define IP_NUM_CHARS		4
#define DEFAULT_BUFF_SIZE	1024

#define UDP_PROTOCOL		"udp"
#define TCP_PROTOCOL		"tcp"

#define DEFAULT_TIMEOUT	10000 // 10 seconds in ms
#define NO_WAIT			0
#define WAIT_FOREVER	-1

		class InetAddr
		{
			public:
				InetAddr(const std::string& name, const std::string& add) {
					_name = name;
					_address = add;
					_ipv4 = fromString(add);
				}
				InetAddr(const std::string& name, uint32_t ipv4) {
					_name = name;
					_ipv4 = ipv4;
					_address = fromIpv4(ipv4);
				}

				inline std::string name() const { return _name;}
				inline uint32_t toIpv4() { return _ipv4;}
				inline std::string toString() { return _address;}

			private:
				InetAddr(){}
				std::string _name;
				std::string _address;
				uint32_t	_ipv4;
				uint32_t fromString(const std::string& ip) {
					size_t pos = std::string::npos;
					uint32_t ipv4 = 0;
					for (int i = 0; i < 4; i++) {
						size_t dot = ip.find_last_of(".", pos - 1);
						std::string sbyte = ip.substr(dot + 1, pos - (dot + 1));
						if (sbyte.length()) {
							uint8_t byte = ::atoi(sbyte.c_str());
							ipv4 += (byte << (8 * i));
						}
						pos = dot;
					}
					return ipv4;
				}
				std::string fromIpv4(uint32_t ipv4) {
					std::stringstream addr;
					for (int i = 3; i >= 0; i--) {
						uint8_t byte = static_cast<uint8_t>((ipv4 >> (8 * i)) & (0xFF));
						addr << std::to_string(byte);
						if (i){
							addr << ".";
						}
					}
					return addr.str();
				}
		};

		class ISocket
		{
			public:
				enum nSocketType
				{
					UDP_SOCKET = 0,
					TCP_SOCKET
				};
				enum nSocketStatus
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
				ISocket(nSocketType type) {
					_type = type;
					_port  = 0;
					_status = UNKNOWN;
				}
				virtual ~ISocket(){;}
				virtual inline uint16_t port() const {return _port;}
				virtual inline nSocketType type() const {return  _type;}
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
				virtual nSocketStatus status() const {return _status;}
				virtual std::vector<InetAddr> localAddress() const = 0;

				bool operator == (const ISocket& other)	{return equal(other);}
				bool operator != (const ISocket& other)	{return !equal(other);}

			protected:
				uint16_t		_port;
				nSocketType	_type;
				virtual bool init() = 0;

				bool equal(const ISocket& other) const {
					return _type == other._type &&
							_port == other._port &&
							(address() == other.address());
				}

				void setStatus(nSocketStatus status) {
					if (_status != status) {
						_status = status;
					}
				}

			private:
				nSocketStatus	_status;

		};
	}
}

#endif //MACSA_NETWORK_ISOCKET_H
