#ifndef MACSA_PRINTER_JET_COMMS_H
#define MACSA_PRINTER_JET_COMMS_H

#include "printer/printer.h"
#include "printer/board.h"

#define DEFAULT_TIJ_TCP_PORT	9991

namespace Macsa {
	namespace Printers {
		class Ethernet
		{
			public:
				Ethernet();
				Ethernet(const Ethernet& eth);
				~Ethernet();
				bool setAddress(const std::string& addr);
				bool setAddress(const uint32_t& addr);
				bool setGateway(const uint32_t& gw);
				bool setGateway(const std::string& gw);
				bool setNetmask(const std::string& mask);
				bool setNetmask(const uint32_t& mask);
				bool setMacAddress(const std::string& mac);

				void setDhcp(bool enable);
				void setHostname(const std::string& hostname);
				void setTcpPort(uint16_t port);


				std::string address() const;
				std::string macAddress() const;
				std::string gateway() const;
				std::string netmask() const;
				bool dhcp() const;
				std::string hostname() const;
				uint16_t tcpPort() const;

				inline bool operator == (const Ethernet& other) const {return compare(other);}
				inline bool operator != (const Ethernet& other) const {return !compare(other);}
				inline void operator = (const Ethernet& other) {return copy(other);}

			private:
				std::string _address;
				std::string _mask;
				std::string _gateway;
				std::string _mac;
				bool _dhcp;
				//??
				std::string _hostname;
				uint16_t _tcpPort;


				bool validIp(const std::string& ip) const;
				std::string ipFromU32(const uint32_t& ip) const;
				bool validMacAddress(const std::string& mac) const;
				inline bool isInRange(int val, int min, int max) const;

				void copy(const Ethernet& other);
				bool compare(const Ethernet& other) const;

		};


		class BlueTooth
		{
			public:
				BlueTooth();
				~BlueTooth();

				std::string name() const;
				void setName(const std::string &name);

				std::string pass() const;
				void setPass(const std::string &pass);

				bool visible() const;
				void setVisible(bool visible);

				inline bool operator == (const BlueTooth& other) const {return compare(other);}
				inline bool operator != (const BlueTooth& other) const {return !compare(other);}
				inline void operator = (const BlueTooth& other) {return copy(other);}

			private:
				std::string _name;
				std::string _pass;
				bool _visible;

				void copy (const BlueTooth& other);
				bool compare(const BlueTooth& other) const;
		};

		class JetComms : public PrinterComms{
			public:
				int ethernetIfaces() const;
				Ethernet * ethernetIface(int iface);
				const Ethernet * ethernetIface(int iface) const;

				int setEthernetIface(const std::string& addr, const std::string& mask, const std::string& gw, const std::string hw = "", uint16_t tcpPort = DEFAULT_TIJ_TCP_PORT);
				int setEthernetIface(const Ethernet * ethAdapter);

				BlueTooth* bluetooth();
				const BlueTooth* bluetooth() const;

				void setBluetooth(const BlueTooth& bluetooth);
				void setBluetooth(const std::string& device, const std::string& pass, bool visible);

				inline bool operator == (const JetComms& other) const {return  compare(other);}
				inline bool operator != (const JetComms& other) const {return !compare(other);}
				inline void operator = (const JetComms& other) {return copy(other);}

			private:
				std::vector<Ethernet> _ifaces;
				BlueTooth _bluetooth;

				bool compare(const JetComms& other) const;
				void copy (const JetComms& other);
				std::vector<Ethernet>::iterator getEthAdapter(const std::string & addr, const std::string & mac);

		};
	}
}

#endif
