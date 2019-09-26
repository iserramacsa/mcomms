#ifndef PRINTER_COMM_CHANELS_H
#define PRINTER_COMM_CHANELS_H

#include <string>
#include <vector>
#include <stdint.h>

namespace Macsa {
	namespace Printers {
		class Ethernet
		{
			public:
				Ethernet();
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

			private:
				std::string _name;
				std::string _pass;
				bool _visible;
		};

		class PrinterComms
		{
			public:
				PrinterComms();
				~PrinterComms();

				int ethernetIfaces() const;
				Ethernet * ethernetIface(int iface);
				const Ethernet * ethernetIface(int iface) const;

				int addEthernetIface(const std::string& addr, const std::string& mask, const std::string& gw, const std::string hw = "");

				BlueTooth* bluetooth();
				const BlueTooth* bluetooth() const;

			private:
				std::vector<Ethernet> _ifaces;
				BlueTooth _bluetooth;
		};
	}
}

#endif //PRINTER_COMM_CHANELS_H
