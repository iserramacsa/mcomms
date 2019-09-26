#include "xmlboard.h"
#include "mtools.h"
#include <sstream>

#include "mprotocol/mprotocol.h"

using namespace Macsa;
using namespace Macsa::MProtocol;

XMLElement *generalConfigToXml(const Printers::Printer& printer, XMLDocument &doc)
{
	XMLElement *general = doc.NewElement(MCONFIG_GENERAL);
	MTools::newTextElement(MCONFIG_GENERAL_DT, printer.formatedDateTime().c_str(), doc, &general);

	XMLElement *log = doc.NewElement(MCONFIG_GENERAL_LOG);
	log->SetAttribute(MCONFIG_GENERAL_LOG_ERR_ATTR,			MTools::toString(false).c_str());	//TODO: add logger to protocol
	log->SetAttribute(MCONFIG_GENERAL_LOG_WARN_ATTR,		MTools::toString(false).c_str());	//TODO: add logger to protocol
	log->SetAttribute(MCONFIG_GENERAL_LOG_INFO_ATTR,		MTools::toString(false).c_str());	//TODO: add logger to protocol
	log->SetAttribute(MCONFIG_GENERAL_LOG_SAVE_ERR_ATTR,	MTools::toString(false).c_str());	//TODO: add logger to protocol
	log->SetAttribute(MCONFIG_GENERAL_LOG_SAVE_WARN_ATTR,	MTools::toString(false).c_str());	//TODO: add logger to protocol
	log->SetAttribute(MCONFIG_GENERAL_LOG_SAVE_INFO_ATTR,	MTools::toString(false).c_str());	//TODO: add logger to protocol
	log->SetAttribute(MCONFIG_GENERAL_LOG_COMMS,			MTools::toString(false).c_str());	//TODO: add logger to protocol
	general->InsertEndChild(log);

	return general;
}

XMLElement* boardConnectionsToXml(const Printers::PrinterComms &comms, XMLDocument &doc)
{
	XMLElement*	connections = doc.NewElement(MCONFIG_CONNECTIONS);
	XMLElement*	network = MTools::newElement(MCONFIG_CONN_NETWORK, doc, &connections);
	if(network != nullptr) {
		for (int i = 0; i < comms.ethernetIfaces(); i++) {
			const Printers::Ethernet* eth = comms.ethernetIface(i);
			XMLElement* iface = MTools::newTextElement(MCONFIG_CONN_NETWORK_ADAPTER, eth->address().c_str(), doc, &network);
			iface->SetAttribute(MCONFIG_CONN_NETWORK_ADAPTER_ID_ATTR, i);
			MTools::newTextElement(MCONFIG_CONN_NETWORK_SUBNET,		eth->netmask().c_str(),		doc, &network);
			MTools::newTextElement(MCONFIG_CONN_NETWORK_GATEWAY,	eth->gateway().c_str(),		doc, &network);
			MTools::newTextElement(MCONFIG_CONN_NETWORK_DHCP,		MTools::toString(eth->dhcp()),		doc, &network);
			MTools::newTextElement(MCONFIG_CONN_NETWORK_HOSTNAME,	eth->hostname().c_str(),	doc, &network);
			MTools::newTextElement(MCONFIG_CONN_NETWORK_TCPPORT,	std::to_string(eth->tcpPort()),	doc, &network);
		}
	}
	XMLElement*	ble = MTools::newElement(MCONFIG_CONN_BLUETOOTH, doc, &connections);
	if(ble != nullptr) {
		MTools::newTextElement(MCONFIG_CONN_BLUETOOTH_DEVNAME,		comms.bluetooth()->name(), doc, &ble);
		MTools::newTextElement(MCONFIG_CONN_BLUETOOTH_VISIBILITY,	MTools::toString(comms.bluetooth()->visible()), doc, &ble);
		MTools::newTextElement(MCONFIG_CONN_BLUETOOTH_PASSWORD,		comms.bluetooth()->pass(), doc, &ble);
	}

	return connections;
}
