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
Ethernet::Ethernet()
{}

Ethernet::Ethernet(const Ethernet &eth)
{
	copy(eth);
}

Ethernet::~Ethernet()
{}

std::string Ethernet::id() const
{
	return _id;
}

void Ethernet::setId(const std::string &id)
{
	_id = id;
}

void Ethernet::setAddress(const std::string &addr, IpVersion version, std::string netmask)
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

void Ethernet::setGateway(const std::string &gw, IpVersion version)
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

void Ethernet::setNetmask(const std::string &addr, const std::string &mask)
{
	for (auto & address : _addresses){
		if (address.address() == addr) {
			address.setNetmask(mask);
			break;
		}
	}
}

void Ethernet::setDNS(const std::string &addr, IpVersion version)
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

std::vector<IpAddress> Ethernet::addresses() const
{
	return _addresses;
}

std::vector<IpAddress> Ethernet::gateways() const
{
	return _gateways;
}

std::vector<IpAddress> Ethernet::dns() const
{
	return _dns;
}


bool Ethernet::connected() const
{
	return _connected;
}

void Ethernet::setConnected(bool connected)
{
	_connected = connected;
}

void Ethernet::copy(const Ethernet &other)
{
	_addresses.clear();
	_gateways.clear();
	_dns.clear();

	_addresses = other._addresses;
	_gateways  = other._gateways;
	_dns  = other._dns;
	_connected = other._connected;
}

bool Ethernet::compare(const Ethernet &other) const
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

Ethernet *JetComms::ethernetIface(const std::string &iface)
{
	std::vector<Ethernet>::iterator it = getEthAdapter(iface);
	if (it != _ifaces.end()) {
		return &(*it);
	}
	return nullptr;
}

const Ethernet *JetComms::ethernetIface(const std::string& iface) const
{
	std::vector<Ethernet>::const_iterator it = getEthAdapter(iface);
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

void JetComms::setEthernetIface(const Ethernet *ethAdapter)
{
	if (ethAdapter != nullptr) {
		std::vector<Ethernet>::iterator it = getEthAdapter(ethAdapter->id());

		if (it == _ifaces.end()){
			Ethernet eth = (*ethAdapter);
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

std::vector<Ethernet>::iterator JetComms::getEthAdapter(const std::string &id)
{
	for (std::vector<Ethernet>::iterator it = _ifaces.begin(); it != _ifaces.end(); it++) {
		if (it->id().compare(id) == 0) {
			return it;
		}
	}

	return _ifaces.end();
}
std::vector<Ethernet>::const_iterator JetComms::getEthAdapter(const std::string &id) const
{
	for (std::vector<Ethernet>::const_iterator it = _ifaces.begin(); it != _ifaces.end(); it++) {
		if (it->id().compare(id) == 0) {
			return it;
		}
	}

	return _ifaces.end();
}

