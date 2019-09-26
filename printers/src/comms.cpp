#include "printer/comms.h"
#include <sstream>
#include <algorithm>

#define IP_ADDRESS_MIN_LENGTH	 7
#define IP_ADDRESS_MAX_LENGTH	15
#define IP_ADDRESS_NUM_DOTS		 3
#define MAC_ADDRESS_LENGTH		17
#define MAC_ADDRESS_NUM_COLONS	 5

using namespace Macsa::Printers;

// ========== Ethernet  ===========//
Ethernet::Ethernet()
{}

Ethernet::~Ethernet()
{}

bool Ethernet::setAddress(const std::string &addr)
{
	if(validIp(addr)){
		_address = addr;
		return true;
	}
	return false;
}

bool Ethernet::setAddress(const uint32_t &addr)
{
	std::string ip = ipFromU32(addr);
	if(validIp(ip)){
		_address = ip;
		return true;
	}
	return false;
}

bool Ethernet::setGateway(const uint32_t &gw)
{
	std::string gateway = ipFromU32(gw);
	if(validIp(gateway)){
		_gateway = gateway;
		return true;
	}
	return false;
}

bool Ethernet::setGateway(const std::string &gw)
{
	if(validIp(gw)){
		_gateway = gw;
		return true;
	}
	return false;
}

bool Ethernet::setNetmask(const std::string &mask)
{
	if(validIp(mask)){
		_mask = mask;
		return true;
	}
	return false;
}

bool Ethernet::setNetmask(const uint32_t &mask)
{
	std::string netmask = ipFromU32(mask);
	if(validIp(netmask)){
		_mask = netmask;
		return true;
	}
	return false;
}

bool Ethernet::setMacAddress(const std::string &mac)
{
	if(validMacAddress(mac)){
		_mac = mac;
		return true;
	}
	return false;
}

void Ethernet::setDhcp(bool enable)
{
	_dhcp = enable;
}

void Ethernet::setHostname(const std::string &hostname)
{
	_hostname = hostname;
}

void Ethernet::setTcpPort(uint16_t port)
{
	_tcpPort = port;
}

std::string Ethernet::address() const
{
	return _address;
}

std::string Ethernet::macAddress() const
{
	return _mac;
}

std::string Ethernet::gateway() const
{
	return _gateway;
}

std::string Ethernet::netmask() const
{
	return _mask;
}

bool Ethernet::dhcp() const
{
	return _dhcp;
}

std::string Ethernet::hostname() const
{
	return _hostname;
}

uint16_t Ethernet::tcpPort() const
{
	return _tcpPort;
}

bool Ethernet::validIp(const std::string &ip) const
{
	//Pattern 999.999.999.999
	if(isInRange(static_cast<int>(ip.length()), IP_ADDRESS_MIN_LENGTH, IP_ADDRESS_MAX_LENGTH)) {
		int ndots = 0;
		size_t dot = ip.find_first_of(".");
		while (dot != ip.npos){
			size_t next = ip.find_first_of(".", dot + 1);
			if(next != ip.npos){
				next = next - dot;
			}

			int val = std::atoi(ip.substr(dot + 1, next).c_str());
			if (!isInRange(val, 0, 255)) {
				break;
			}

			ndots++;
			dot = ip.find_first_of(".", dot + 1);
		}
		return ndots == IP_ADDRESS_NUM_DOTS;
	}
	return false;
}

std::string Ethernet::ipFromU32(const uint32_t &ip) const
{
	std::stringstream ss;

	ss << ((ip >> 24) & 0x000000FF) << ".";
	ss << ((ip >> 16) & 0x000000FF) << ".";
	ss << ((ip >>  8) & 0x000000FF) << ".";
	ss << ( ip        & 0x000000FF);

	return ss.str();
}

bool Ethernet::validMacAddress(const std::string &mac) const
{
	//Pattern 00:00:00:00:00:00
	if(mac.length() == MAC_ADDRESS_LENGTH) {
		int ncolons = 0;
		size_t colon = mac.find_first_of(":");
		bool invalid = false;
		while (colon != mac.npos){
			std::string val = mac.substr(static_cast<size_t>(ncolons* 3), 2);
			invalid |= ((isInRange(val.at(0), '0', '9') || isInRange(val.at(0), 'A', 'F') || isInRange(val.at(0), 'a', 'f')) == false);
			invalid |= ((isInRange(val.at(1), '0', '9') || isInRange(val.at(1), 'A', 'F') || isInRange(val.at(1), 'a', 'f')) == false);

			if (invalid) {
				break;
			}

			ncolons++;
			colon = mac.find_first_of(":", (colon + 1));
		}
		return ncolons == MAC_ADDRESS_NUM_COLONS;
	}

	return false;
}

bool Ethernet::isInRange(int val, int min, int max) const
{
	if (min > max){
		int tmp = max;
		max = min;
		min = tmp;
	}

	return ((val >= min) && (val <= max));
}

// ========== BlueTooth  ===========//
BlueTooth::BlueTooth()
{}

BlueTooth::~BlueTooth()
{}

std::string BlueTooth::name() const
{
	return _name;
}

void BlueTooth::setName(const std::string &name)
{
	_name = name;
}

std::string BlueTooth::pass() const
{
	return _pass;
}

void BlueTooth::setPass(const std::string &pass)
{
	_pass = pass;
}

bool BlueTooth::visible() const
{
	return _visible;
}

void BlueTooth::setVisible(bool visible)
{
	_visible = visible;
}

// ========== PrinterComms  ===========//
PrinterComms::PrinterComms()
{}

PrinterComms::~PrinterComms()
{}

int PrinterComms::ethernetIfaces() const
{
	return static_cast<int>(_ifaces.size());
}

Ethernet *PrinterComms::ethernetIface(int iface)
{
	Ethernet * eth = nullptr;
	if (iface >= 0 && static_cast<unsigned long>(iface) < _ifaces.size())
	{
		eth = &_ifaces[static_cast<unsigned long>(iface)];
	}
	return eth;
}

BlueTooth * PrinterComms::bluetooth()
{
	return &_bluetooth;
}

const Ethernet *PrinterComms::ethernetIface(int iface) const
{
	if (iface >= 0 && static_cast<unsigned long>(iface) < _ifaces.size())
	{
		return &_ifaces[static_cast<unsigned long>(iface)];
	}
	return nullptr;
}

int PrinterComms::addEthernetIface(const std::string &addr, const std::string &mask, const std::string &gw, const std::string hw)
{
	std::vector<Ethernet>::const_iterator it = std::find_if(_ifaces.begin(), _ifaces.end(), [&](const Ethernet& eth){
		return ((eth.address().compare(addr) == 0) || (eth.macAddress().compare(hw) == 0));
	});

	if (it == _ifaces.end()){
		Ethernet eth;
		eth.setAddress(addr);
		eth.setGateway(gw);
		eth.setNetmask(mask);
		eth.setMacAddress(hw);
		_ifaces.push_back(eth);
		return static_cast<int>(_ifaces.size() - 1);
	}

	return -1;
}

const BlueTooth *PrinterComms::bluetooth() const
{
	return &_bluetooth;
}
