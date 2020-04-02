#include "jet/jetcomms.h"

#include <sstream>
#include <algorithm>

using namespace Macsa::Printers;

// ========== IP Address  ===========//
IpAddress::IpAddress(const std::string& address, IpVersion version) :
	_address(address),
	_version(version())
{
	_netmask = "";
}

IpAddress::IpAddress(const IpAddress &other) :
	_address(other._address),
	_version(other._version())
{
	_netmask = other._netmask;
}

std::string IpAddress::address() const
{
	return _address;
}

IpVersion IpAddress::version() const
{
	return _version;
}

std::string IpAddress::netmask() const
{
	return _netmask;
}

void IpAddress::setNetmask(const std::string &netmask)
{
	_netmask = netmask;
}

void IpAddress::copy(const IpAddress &other)
{
	if (_address == other._address && _version == other._version){
		_netmask = other._netmask;
	}
}

bool IpAddress::compare(const IpAddress &other) const
{
	if (_address != other._address)		{ return false;}
	if (_version() != other._version()) { return false;}
	if (_netmask != other._netmask)		{ return false;}

	return true;
}

// ========== Ethernet  ===========//
JetEthernet::JetEthernet()
{}

JetEthernet::JetEthernet(const JetEthernet &eth)
{
	copy(eth);
}

JetEthernet::~JetEthernet()
{}

std::string JetEthernet::id() const
{
	return _id;
}

void JetEthernet::setId(const std::string &id)
{
	_id = id;
}

void JetEthernet::setAddress(const std::string &addr, IpVersion version, std::string netmask)
{
	bool exist = false;
	for (auto & address : _addresses){
		if (address.address() == addr) {
			address.setNetmask(netmask);
			exist = true;
			break;
		}
	}

	if(!exist) {
		IpAddress address(addr, version);
		address.setNetmask(netmask);
		_addresses.push_back(address);
	}
}

void JetEthernet::setGateway(const std::string &gw, IpVersion version)
{
	bool exist = false;
	for (auto & gateway : _gateways){
		if (gateway.address() == gw) {
			exist = true;
			break;
		}
	}

	if(!exist) {
		IpAddress gateway(gw, version);
		_gateways.push_back(gateway);
	}
}

void JetEthernet::setNetmask(const std::string &addr, const std::string &mask)
{
	for (auto & address : _addresses){
		if (address.address() == addr) {
			address.setNetmask(mask);
			break;
		}
	}
}

void JetEthernet::setDNS(const std::string &addr, IpVersion version)
{
	bool exist = false;
	for (auto & dns : _dns){
		if (dns.address() == addr) {
			exist = true;
			break;
		}
	}

	if(!exist) {
		IpAddress dns(addr, version);
		_dns.push_back(dns);
	}
}

std::vector<IpAddress> JetEthernet::addresses() const
{
	return _addresses;
}

std::vector<IpAddress> JetEthernet::gateways() const
{
	return _gateways;
}

std::vector<IpAddress> JetEthernet::dns() const
{
	return _dns;
}


bool JetEthernet::connected() const
{
	return _connected;
}

void JetEthernet::setConnected(bool connected)
{
	_connected = connected;
}

void JetEthernet::copy(const JetEthernet &other)
{
	_addresses.clear();
	_gateways.clear();
	_dns.clear();

	_addresses = other._addresses;
	_gateways  = other._gateways;
	_dns  = other._dns;
	_connected = other._connected;
}

bool JetEthernet::compare(const JetEthernet &other) const
{
	if (_addresses != other._addresses) { return false; }
	if (_gateways != other._gateways) { return false; }
	if (_dns != other._dns) { return false; }

	return (_connected == other._connected);
}

// ========== PrinterComms  ===========//
int JetComms::ethernetIfaces() const
{
	return static_cast<int>(_ifaces.size());
}

JetEthernet *JetComms::ethernetIface(const std::string &iface)
{
	std::vector<JetEthernet>::iterator it = getEthAdapter(iface);
	if (it != _ifaces.end()) {
		return &(*it);
	}
	return nullptr;
}

const JetEthernet *JetComms::ethernetIface(const std::string& iface) const
{
	std::vector<JetEthernet>::const_iterator it = getEthAdapter(iface);
	if (it != _ifaces.end()) {
		return &(*it);
	}
	return nullptr;
}

std::vector<std::string> JetComms::ifaces() const
{
	std::vector<std::string> eths;
	for ( auto& eth : _ifaces) {
		eths.push_back(eth.id());
	}
	return eths;
}

void JetComms::setEthernetIface(const JetEthernet *ethAdapter)
{
	if (ethAdapter != nullptr) {
		std::vector<JetEthernet>::iterator it = getEthAdapter(ethAdapter->id());

		if (it == _ifaces.end()){
			JetEthernet eth = (*ethAdapter);
			_ifaces.push_back(eth);
		}
		else {
			*it = *ethAdapter;
		}
	}

}

bool JetComms::compare(const JetComms &other) const
{
	return (_ifaces == other._ifaces);
}

void JetComms::copy(const JetComms &other)
{
	_ifaces.clear();
	_ifaces = other._ifaces;
}

std::vector<JetEthernet>::iterator JetComms::getEthAdapter(const std::string &id)
{
	for (std::vector<JetEthernet>::iterator it = _ifaces.begin(); it != _ifaces.end(); it++) {
		if (it->id().compare(id) == 0) {
			return it;
		}
	}

	return _ifaces.end();
}
std::vector<JetEthernet>::const_iterator JetComms::getEthAdapter(const std::string &id) const
{
	for (std::vector<JetEthernet>::const_iterator it = _ifaces.begin(); it != _ifaces.end(); it++) {
		if (it->id().compare(id) == 0) {
			return it;
		}
	}

	return _ifaces.end();
}

