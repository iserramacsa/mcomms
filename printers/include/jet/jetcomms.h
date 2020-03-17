#ifndef MACSA_PRINTER_JET_COMMS_H
#define MACSA_PRINTER_JET_COMMS_H

#include "printer/printer.h"
#include "jet/datatypes.h"

#define DEFAULT_TIJ_TCP_PORT	9991

namespace Macsa {
	namespace Printers {

		class IpAddress {
			public:
				IpAddress(const std::string& address, IpVersion version = IP_V4);
				IpAddress(const IpAddress& other);

				std::string address() const;
				IpVersion version() const;

				std::string netmask() const;
				void setNetmask(const std::string &netmask);

				inline bool operator == (const IpAddress& other) const {return compare(other);}
				inline bool operator != (const IpAddress& other) const {return !compare(other);}
				inline void operator = (const IpAddress& other) {return copy(other);}

			private:
				const std::string _address;
				const IpVersion _version;
				std::string _netmask;

				void copy(const IpAddress& other);
				bool compare(const IpAddress& other) const;
		};

		class Ethernet
		{
			public:
				Ethernet();
				Ethernet(const Ethernet& eth);
				~Ethernet();

				std::string id() const;
				void setId(const std::string &id);

				void setAddress(const std::string& addr, IpVersion version, std::string netmask);
				void setGateway(const std::string& gw, IpVersion version);
				void setNetmask(const std::string& addr, const std::string& mask);
				void setDNS(const std::string& gw, IpVersion version);

				std::vector<IpAddress> addresses() const;
				std::vector<IpAddress> gateways() const;
				std::vector<IpAddress> dns() const;

				bool connected() const;
				void setConnected(bool connected);

				inline bool operator == (const Ethernet& other) const {return compare(other);}
				inline bool operator != (const Ethernet& other) const {return !compare(other);}
				inline void operator = (const Ethernet& other) {return copy(other);}

			private:
				std::string _id;
				std::vector<IpAddress> _addresses;
				std::vector<IpAddress> _dns;
				std::vector<IpAddress> _gateways;
				bool _connected;

				void copy(const Ethernet& other);
				bool compare(const Ethernet& other) const;
				bool compare(const std::vector<IpAddress>& v1, const std::vector<IpAddress>& v2) const;

		};

		class JetComms : public PrinterComms{
			public:
				int ethernetIfaces() const;
				Ethernet * ethernetIface(const std::string& iface);
				const Ethernet * ethernetIface(const std::string& iface) const;

				void setEthernetIface(const Ethernet * ethAdapter);

				inline bool operator == (const JetComms& other) const {return  compare(other);}
				inline bool operator != (const JetComms& other) const {return !compare(other);}
				inline void operator = (const JetComms& other) {return copy(other);}

			private:
				std::vector<Ethernet> _ifaces;

				bool compare(const JetComms& other) const;
				void copy (const JetComms& other);
				std::vector<Ethernet>::iterator getEthAdapter(const std::string & id);
				std::vector<Ethernet>::const_iterator getEthAdapter(const std::string & id) const;
		};
	}
}

#endif
