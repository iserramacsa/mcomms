#include "mprotocol/mconfigbase.h"
#include "mprotocol/mprotocol.h"
#include "mtools.h"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MConfigCommand::MConfigCommand(const std::string &command, Macsa::Printers::TIJPrinter &printer):
	MCommand(command, printer)
{

}

MConfigCommand::~MConfigCommand()
{

}

void MConfigCommand::generalConfigToXml(const Macsa::Printers::TIJPrinter &printer, XMLElement **parent)
{
	XMLElement * xGeneral = createChildNode(MCONFIG_GENERAL, parent);
	if(xGeneral != nullptr) {
		createTextChildNode(MCONFIG_GENERAL_DT, printer.formatedDateTime(), parent);
		XMLElement * xLog = createChildNode(MCONFIG_GENERAL_LOG, parent);
		if(xLog != nullptr) {
			xLog->SetAttribute(MCONFIG_GENERAL_LOG_ENABLED_ATTR, MTools::toString(printer.logsEnabled()).c_str());
			xLog->SetAttribute(MCONFIG_GENERAL_LOG_LEVEL_ATTR, printer.loggerLevel().toString().c_str());
			xLog->SetAttribute(MCONFIG_GENERAL_LOG_COMMS, MTools::toString(printer.logComsEnabled()).c_str());
		}
	}
}

// #define MCONFIG_CONNECTIONS			"CONNECTIONS"
// #define MCONFIG_CONN_NETWORK			"NETWORK"
// #define MCONFIG_CONN_NETWORK_ADAPTER		"ADAPTER"
// #define MCONFIG_CONN_NETWORK_IP					"IP_ADDRESS"
// #define MCONFIG_CONN_NETWORK_SUBNET				"SUBNET_MASK"
// #define MCONFIG_CONN_NETWORK_GATEWAY			"GATEWAY"
// #define MCONFIG_CONN_NETWORK_DHCP				"DHCP"
// #define MCONFIG_CONN_NETWORK_HOSTNAME			"HOSTNAME"
// #define MCONFIG_CONN_NETWORK_TCPPORT			"TCP_PORT"
// #define MCONFIG_CONN_BLUETOOTH			"BLUETOOTH"
// #define MCONFIG_CONN_BLUETOOTH_DEVNAME		"DEVICE_NAME"
// #define MCONFIG_CONN_BLUETOOTH_VISIBILITY	"VISIBILITY"
// #define MCONFIG_CONN_BLUETOOTH_PASSWORD		"PASSWORD"
void MConfigCommand::printerConnectionsToXml(const Macsa::Printers::TIJPrinter &printer, XMLElement **parent)
{
	XMLElement * xConnections = createChildNode(MCONFIG_CONNECTIONS, parent);
	if (xConnections != nullptr) {
		XMLElement* xNetwork = createChildNode(MCONFIG_CONN_NETWORK, &xConnections);
		const Printers::TIJComms* comms = dynamic_cast<const Printers::TIJComms*>(printer.comms());
		if (xNetwork != nullptr && comms != nullptr) {
			for (int i = 0; i < comms->ethernetIfaces(); i++) {
				const Printers::Ethernet* eth = comms->ethernetIface(i);
				if (eth != nullptr){
					XMLElement* xAdapter = createChildNode(MCONFIG_CONN_NETWORK, &xNetwork);
					xAdapter->SetAttribute(ATTRIBUTE_ID, i);
					createTextChildNode(MCONFIG_CONN_NETWORK_IP, eth->address().c_str(), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_SUBNET, eth->netmask().c_str(), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_GATEWAY, eth->gateway().c_str(), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_DHCP, MTools::toString(eth->dhcp()), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_HOSTNAME, eth->hostname().c_str(), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_TCPPORT, MTools::toString(eth->tcpPort()), &xNetwork);
				}
			}
		}
		XMLElement* xBle = createChildNode(MCONFIG_CONN_BLUETOOTH, &xConnections);
		if (xBle != nullptr && comms != nullptr) {
			const Printers::BlueTooth* ble = comms->bluetooth();
			createTextChildNode(MCONFIG_CONN_BLUETOOTH_DEVNAME, ble->name().c_str(), &xBle);
			createTextChildNode(MCONFIG_CONN_BLUETOOTH_VISIBILITY, MTools::toString(ble->visible()), &xBle);
			createTextChildNode(MCONFIG_CONN_BLUETOOTH_PASSWORD, ble->pass().c_str(), &xBle);
		}
	}
}

void MConfigCommand::generalConfigFromXml(const XMLElement *parent, Macsa::Printers::TIJPrinter &printer) const
{
	if (parent != nullptr) {
		const XMLElement* xGeneral = parent->FirstChildElement(MCONFIG_GENERAL);
		if (xGeneral) {
			printer.setDateTime(getTextFromChildNode(xGeneral, MCONFIG_GENERAL_DT, _printer.formatedDateTime()));
			const XMLElement* xLog = xGeneral->FirstChildElement(MCONFIG_GENERAL_LOG);
			if (xLog) {
				printer.setlogsEnabled(MTools::boolfromString(xLog->Attribute(MCONFIG_GENERAL_LOG_ENABLED_ATTR)));
				printer.setloggerLevel(xLog->Attribute(MCONFIG_GENERAL_LOG_LEVEL_ATTR));
				printer.setlogComsEnabled(MTools::boolfromString(xLog->Attribute(MCONFIG_GENERAL_LOG_COMMS)));
			}
		}
	}
}


