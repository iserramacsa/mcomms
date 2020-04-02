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

		class JetEthernet
		{
			public:
				JetEthernet();
				JetEthernet(const JetEthernet& eth);
				~JetEthernet();

				std::string id() const;
				void setId(const std::string &id);

				void setAddress(const std::string& addr, IpVersion version, std::string netmask);
				void setGateway(const std::string& gw, IpVersion version);
				void setNetmask(const std::string& addr, const std::string& mask);
				void setDNS(const std::string& addr, IpVersion version);

				std::vector<IpAddress> addresses() const;
				std::vector<IpAddress> gateways() const;
				std::vector<IpAddress> dns() const;

				bool connected() const;
				void setConnected(bool connected);

				inline bool operator == (const JetEthernet& other) const {return compare(other);}
				inline bool operator != (const JetEthernet& other) const {return !compare(other);}
				inline void operator = (const JetEthernet& other) {return copy(other);}

			private:
				std::string _id;
				std::vector<IpAddress> _addresses;
				std::vector<IpAddress> _dns;
				std::vector<IpAddress> _gateways;
				bool _connected;

				void copy(const JetEthernet& other);
				bool compare(const JetEthernet& other) const;
				bool compare(const std::vector<IpAddress>& v1, const std::vector<IpAddress>& v2) const;

		};

		class JetComms : public PrinterComms{
			public:
				int ethernetIfaces() const;
				JetEthernet * ethernetIface(const std::string& iface);
				const JetEthernet * ethernetIface(const std::string& iface) const;
				std::vector<std::string> ifaces() const;

				void setEthernetIface(const JetEthernet * ethAdapter);

				inline bool operator == (const JetComms& other) const {return  compare(other);}
				inline bool operator != (const JetComms& other) const {return !compare(other);}
				inline void operator = (const JetComms& other) {return copy(other);}

			private:
				std::vector<JetEthernet> _ifaces;

				bool compare(const JetComms& other) const;
				void copy (const JetComms& other);
				std::vector<JetEthernet>::iterator getEthAdapter(const std::string & id);
				std::vector<JetEthernet>::const_iterator getEthAdapter(const std::string & id) const;
		};
	}
}

#endif
