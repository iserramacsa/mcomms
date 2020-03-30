#include "jetprotocol/jetconfigbase.h"
#include "jetprotocol/jetprotocol.h"

#include <algorithm>

using namespace Macsa::Printers;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetConfigCommand::JetConfigCommand(const std::string &command, Printers::JetPrinter &printer):
	JetCommand(command, printer)
{}

JetConfigCommand::~JetConfigCommand()
{}

void JetConfigCommand::printheadToXml(const Macsa::Printers::JetPrinter &printer, XMLElement **parent)
{
	std::vector<unsigned int>  printheads = printer.printheads();
	for (unsigned int i = 0; i < printheads.size(); i++) {
		JetPrinthead printhead = printer.printhead(printheads.at(i));
		XMLElement * ePrinthead = createChildNode(JET_PRINTHEAD_TAG, parent);
		if (ePrinthead) {
			ePrinthead->SetAttribute(UPPERCASE_ID_ATTRIBUTE, printhead.id());
			insertPrintheadProperty(JET_IP_ADDRESS_TAG, printhead.ipAddress(), &ePrinthead);
			insertPrintheadProperty(JET_PRINT_DIRECTION_TAG, static_cast<unsigned int>(printer.printDir()()), &ePrinthead);
			insertPrintheadProperty(JET_BITMAPINVERTED_TAG, printer.bitmapInverted(), &ePrinthead);
			insertPrintheadProperty(JET_PRINTSPEED_TAG, static_cast<unsigned int>(printhead.encoder().fixedSpeed()), &ePrinthead);
			insertPrintheadProperty(JET_PRINTDELAY_TAG, static_cast<unsigned int>(printhead.printDelay()), &ePrinthead);
			insertPrintheadProperty(JET_HRES_TAG, printhead.horizontalResolution(), &ePrinthead);
			XMLElement * eEncoder = createChildNode(JET_ENCODER_TAG, &ePrinthead);
			if (eEncoder) {
				const Encoder & encoder = printhead.encoder();
				XMLElement * eEncEnabled = createChildNode(JET_ENABLED_TAG, &eEncoder);
				if (eEncEnabled) {
					bool enabled = (encoder.mode() == nEncoderMode::EXTERNAL_ENCODER);
					eEncEnabled->SetText(toString(enabled).c_str());
				}
				XMLElement * eEncPulses = createChildNode(JET_PULSES_TAG, &eEncoder);
				if (eEncPulses) {
					eEncPulses->SetText(XMLCommand::toString(encoder.resolution(), 0).c_str());
				}
				XMLElement * eEncWheel = createChildNode(JET_WHEEL_TAG, &eEncoder);
				if (eEncWheel){
					eEncWheel->SetText(XMLCommand::toString(encoder.diameter(), 0).c_str());
				}
				XMLElement * eEncPitch = createChildNode(JET_ABC_PITCH_TAG, &eEncoder);
				if (eEncPitch){
					eEncPitch->SetText(XMLCommand::toString(encoder.abcPitch(), 0).c_str());
				}
			}

			insertPrintheadProperty(JET_IP_ADDRESS_TAG, printhead.ipAddress(), &ePrinthead);
			insertPrintheadProperty(JET_PRINTING_LIST_TAG, printhead.printingList(), &ePrinthead);
			insertPrintheadProperty(JET_FIFO_TAG, printhead.fifo(), &ePrinthead);
			insertPrintheadProperty(JET_DELAY_POINTS_TAG, printhead.delayInPoints(), &ePrinthead);
			insertPrintheadProperty(JET_STB_SSCC_TAG, printhead.stbIncrementsSSCC(), &ePrinthead);
			insertPrintheadProperty(JET_IMG_AFTER_PRINT_TAG, printhead.sendImageAfterPrint(), &ePrinthead);
			insertPrintheadProperty(JET_STB_PRINTING_LIST_TAG, printhead.stbResetPrintingList(), &ePrinthead);
			insertPrintheadProperty(JET_LINE_ID_TAG, printhead.lineId(), &ePrinthead);
			insertPrintheadProperty(JET_MACHINE_ID_TAG, printhead.machineId(), &ePrinthead);
			insertPrintheadProperty(JET_MAX_PRINT_TIME_TAG, static_cast<unsigned int>(printhead.maxPrintTime()), &ePrinthead);
			insertPrintheadProperty(JET_OPTIMIZE_BARCODE_TAG, printhead.optimizeBarcode(), &ePrinthead);
			insertPrintheadProperty(JET_OVERLAPPING_TYPE_TAG, static_cast<unsigned int>(printhead.overlappingMode()()), &ePrinthead);
			insertPrintheadProperty(JET_DEFAULT_FONT_TAG, printhead.defaultFont(), &ePrinthead);
			XMLElement* uvLamp = insertPrintheadProperty(JET_LAMP_CONTROL_TAG, printhead.uvLampControl(), &ePrinthead);
			if (uvLamp) {
				XMLElement* uvLampTime = createChildNode(JET_LAMP_TIME_TAG, &uvLamp);
				if (uvLampTime) {
					uvLampTime->SetText(printhead.uvLampTime());
				}
			}
			insertPrintheadProperty(JET_XROFFSET_TAG,  static_cast<unsigned int>(printhead.xrOffset()), &ePrinthead);
			insertPrintheadProperty(JET_CELL_FILTER_TAG, static_cast<unsigned int>(printhead.cellFilter()), &ePrinthead);
			insertPrintheadProperty(JET_PRINT_MODE_TAG, static_cast<unsigned int>(printhead.printMode()()), &ePrinthead);
		}
	}
}

void JetConfigCommand::printerCommsToXml(const Macsa::Printers::JetComms &comms, XMLElement **parent)
{
	XMLElement * eNetwork = createChildNode(JET_NETWORK_ETH_LIST, parent);
	std::vector<std::string> ifaces = comms.ifaces();
	if (eNetwork) {
		for (unsigned int i = 0; i < ifaces.size(); i++) {
			const Ethernet* eth = comms.ethernetIface(ifaces.at(i));
			if (eth) {
				XMLElement * eIface = createChildNode(JET_NETWORK_ADAPTER_TAG, &eIface);
				if (eIface){
					eIface->SetAttribute(UPPERCASE_ID_ATTRIBUTE, eth->id().c_str());
					networkApaterToXml(*eth, &eIface);
				}
			}
		}
	}
}

void JetConfigCommand::networkApaterToXml(const Ethernet &eth, XMLElement **parent)
{
	XMLElement* eIPlist = createChildNode(JET_ETH_IP_ADDR_LIST, parent);
	if (eIPlist) {
		std::vector<IpAddress> ips = eth.addresses();
		for (auto & ip : ips) {
			XMLElement* eIp = createChildNode(JET_ETH_IP_ADDR_TAG, &eIPlist);
			if (eIp) {
				eIp->SetAttribute(VALUE_ATTRIBUTE, ip.address().c_str());
				eIp->SetAttribute(TYPE_ATTRIBUTE, ip.version()());
				eIp->SetAttribute(MASK_ATTRIBUTE, ip.netmask().c_str());
			}
		}
	}
	// GateWays
	const XMLElement* eGatewaylist = createChildNode(JET_ETH_GATEWAYS_LIST, parent);
	if (eGatewaylist) {
		std::vector<IpAddress> gateways = eth.gateways();
		for (auto & gw : gateways) {
			XMLElement* eGateway = createChildNode(JET_ETH_GATEWAY_TAG, &eIPlist);
			if (eGateway) {
				eGateway->SetAttribute(VALUE_ATTRIBUTE, gw.address().c_str());
				eGateway->SetAttribute(TYPE_ATTRIBUTE, gw.version()());
			}
		}
	}
	// Dns
	const XMLElement* eDNSlist = createChildNode(JET_ETH_DNS_LIST, parent);
	if (eDNSlist) {
		std::vector<IpAddress> dnsList = eth.dns();
		for (auto & dns : dnsList) {
			XMLElement* eDNS = createChildNode(JET_ETH_DNS_TAG, &eIPlist);
			if (eDNS) {
				eDNS->SetAttribute(VALUE_ATTRIBUTE, dns.address().c_str());
				eDNS->SetAttribute(TYPE_ATTRIBUTE, dns.version()());
			}
		}
	}
}

void JetConfigCommand::printheadFromXml(const XMLElement *ePrinthead, JetPrinter &printer)
{
	if (ePrinthead) {
		unsigned int id = ePrinthead->UnsignedAttribute(UPPERCASE_ID_ATTRIBUTE);
		JetPrinthead printhead = printer.printhead(id);
		printhead.setIpAddress(getChildAttribute(ePrinthead, JET_IP_ADDRESS_TAG, VALUE_ATTRIBUTE, printhead.ipAddress()));

		printer.setPrintDir(static_cast<nPrintDirection>(getChildAttribute(ePrinthead, JET_PRINT_DIRECTION_TAG, VALUE_ATTRIBUTE, printer.printDir()())));

		printer.setBitmapInverted(getChildAttribute(ePrinthead, JET_BITMAPINVERTED_TAG, VALUE_ATTRIBUTE, printer.bitmapInverted()));
		printhead.setPrintDelay(getChildAttribute(ePrinthead, JET_PRINTDELAY_TAG, VALUE_ATTRIBUTE, printhead.printDelay()));
		printhead.sethorizontalResolution(getChildAttribute(ePrinthead, JET_HRES_TAG, VALUE_ATTRIBUTE, printhead.horizontalResolution()));

		Encoder& encoder = printhead.encoder();
		encoder.setFixedSpeed(getChildAttribute(ePrinthead, JET_PRINTSPEED_TAG, VALUE_ATTRIBUTE, encoder.fixedSpeed()));
		const XMLElement* eEncoder = ePrinthead->FirstChildElement(JET_ENCODER_TAG);
		if (eEncoder) {
			bool encoderEnabled = getBoolFromChildNode(eEncoder, JET_ENABLED_TAG, (encoder.mode()() == nEncoderMode::EXTERNAL_ENCODER));
			encoder.setMode((encoderEnabled ? nEncoderMode::EXTERNAL_ENCODER : nEncoderMode::FIXED_SPEED));
			encoder.setResolution(getDoubleFromChildNode(eEncoder, JET_PULSES_TAG, encoder.resolution()));
			encoder.setDiameter(getDoubleFromChildNode(eEncoder, JET_WHEEL_TAG, encoder.diameter()));
			encoder.setAbcPitch(getDoubleFromChildNode(eEncoder, JET_ABC_PITCH_TAG, encoder.abcPitch()));
		}

		printhead.setPrintingList(getChildAttribute(ePrinthead, JET_PRINTING_LIST_TAG, VALUE_ATTRIBUTE, printhead.printingList()));
		printhead.setFifo(getChildAttribute(ePrinthead, JET_FIFO_TAG, VALUE_ATTRIBUTE, printhead.fifo()));
		printhead.setDelayInPoints(getChildAttribute(ePrinthead, JET_DELAY_POINTS_TAG, VALUE_ATTRIBUTE, printhead.delayInPoints()));
		printhead.setStbIncrementsSSCC(getChildAttribute(ePrinthead, JET_STB_SSCC_TAG, VALUE_ATTRIBUTE, printhead.stbIncrementsSSCC()));
		printhead.setSendImageAfterPrint(getChildAttribute(ePrinthead, JET_IMG_AFTER_PRINT_TAG, VALUE_ATTRIBUTE, printhead.sendImageAfterPrint()));
		printhead.setStbResetPrintingList(getChildAttribute(ePrinthead, JET_STB_PRINTING_LIST_TAG, VALUE_ATTRIBUTE, printhead.stbResetPrintingList()));
		printhead.setLineId(getChildAttribute(ePrinthead, JET_LINE_ID_TAG, VALUE_ATTRIBUTE, printhead.lineId()));
		printhead.setMachineId(getChildAttribute(ePrinthead, JET_MACHINE_ID_TAG, VALUE_ATTRIBUTE, printhead.machineId()));
		printhead.setMaxPrintTime(getChildAttribute(ePrinthead, JET_MAX_PRINT_TIME_TAG, VALUE_ATTRIBUTE, printhead.maxPrintTime()));
		printhead.setOptimizeBarcode(getChildAttribute(ePrinthead, JET_OPTIMIZE_BARCODE_TAG, VALUE_ATTRIBUTE, printhead.optimizeBarcode()));
		printhead.setOverlappingMode(static_cast<nOverlappingMode>(getChildAttribute(ePrinthead, JET_OVERLAPPING_TYPE_TAG, VALUE_ATTRIBUTE, printhead.overlappingMode()())));


		printhead.setDefaultFont(getChildAttribute(ePrinthead, JET_DEFAULT_FONT_TAG, VALUE_ATTRIBUTE, printhead.defaultFont()));
		printhead.setUvLampControl(getChildAttribute(ePrinthead, JET_LAMP_CONTROL_TAG, VALUE_ATTRIBUTE, printhead.uvLampControl()));
		const XMLElement* eUVLamp = ePrinthead->FirstChildElement(JET_LAMP_CONTROL_TAG);
		if (eUVLamp) {
			printhead.setUvLampTime(getChildAttribute(ePrinthead, JET_LAMP_TIME_TAG, VALUE_ATTRIBUTE, printhead.uvLampTime()));
		}
		printhead.setXrOffset(getChildAttribute(ePrinthead, JET_XROFFSET_TAG, VALUE_ATTRIBUTE, printhead.xrOffset()));
		printhead.setCellFilter(getChildAttribute(ePrinthead, JET_CELL_FILTER_TAG, VALUE_ATTRIBUTE, printhead.cellFilter()));
		printhead.setPrintMode(static_cast<nTriggerMode>(getChildAttribute(ePrinthead, JET_PRINT_MODE_TAG, VALUE_ATTRIBUTE, printhead.printMode()())));


		printer.setPrinthead(printhead);
	}
}

void JetConfigCommand::printerCommsFromXml(const XMLElement *eComms, Macsa::Printers::JetComms &comms)
{
	if (eComms) {
		const XMLElement *eEth = eComms->FirstChildElement(JET_NETWORK_ADAPTER_TAG);
		while (eEth != nullptr) {
			bool newAdapter = false;
			std::string id = eEth->Attribute(UPPERCASE_ID_ATTRIBUTE, "");
			Ethernet *eth = comms.ethernetIface(id);
			if (eth == nullptr) {
				newAdapter = true;
				eth = new Ethernet();
				eth->setId(id);
			}
			networkAdapterFromXml(eEth, *eth);
			if(newAdapter){
				delete  eth;
			}
		}
		eEth = eEth->NextSiblingElement(JET_NETWORK_ADAPTER_TAG);
	}
}

tinyxml2::XMLElement* JetConfigCommand::insertPrintheadProperty(const std::string& propetyName, const std::string& value, XMLElement **parent)
{
	XMLElement* eProp = createChildNode(propetyName, parent);
	if(eProp){
		eProp->SetAttribute(VALUE_ATTRIBUTE, value.c_str());
	}
	return eProp;
}

tinyxml2::XMLElement* JetConfigCommand::insertPrintheadProperty(const std::string &propetyName, unsigned int value, XMLElement **parent)
{
	XMLElement* eProp = createChildNode(propetyName, parent);
	if(eProp){
		eProp->SetAttribute(VALUE_ATTRIBUTE, value);
	}
	return eProp;
}

tinyxml2::XMLElement* JetConfigCommand::insertPrintheadProperty(const std::string &propetyName, bool value, XMLElement **parent)
{
	XMLElement* eProp = createChildNode(propetyName, parent);
	if(eProp){
		eProp->SetAttribute(VALUE_ATTRIBUTE, toString(value).c_str());
	}
	return eProp;
}

void JetConfigCommand::networkAdapterFromXml(const XMLElement *eEth, Ethernet &eth)
{
	// IP Address
	const XMLElement* eIPlist = eEth->FirstChildElement(JET_ETH_IP_ADDR_LIST);
	if (eIPlist) {
		for (const XMLElement* eIPAddr = eIPlist->FirstChildElement(JET_ETH_IP_ADDR_TAG);
			 eIPAddr != nullptr; eIPAddr = eIPAddr->NextSiblingElement(JET_ETH_IP_ADDR_TAG))
		{
			std::string ip = eIPAddr->Attribute(VALUE_ATTRIBUTE, "");
			IpVersion type = static_cast<nIpVersion>(eIPAddr->UnsignedAttribute(TYPE_ATTRIBUTE, nIpVersion::IP_V4));
			std::string netmask = eIPAddr->Attribute(MASK_ATTRIBUTE, "");
			eth.setAddress(ip, type, netmask);
		}
	}
	// GateWays
	const XMLElement* eGatewaylist = eEth->FirstChildElement(JET_ETH_GATEWAYS_LIST);
	if (eGatewaylist) {
		for (const XMLElement* eGateway = eGatewaylist->FirstChildElement(JET_ETH_GATEWAY_TAG);
			 eGateway != nullptr; eGateway = eGateway->NextSiblingElement(JET_ETH_IP_ADDR_TAG))
		{
			std::string gw = eGateway->Attribute(VALUE_ATTRIBUTE, "");
			IpVersion type = static_cast<nIpVersion>(eGateway->UnsignedAttribute(TYPE_ATTRIBUTE, nIpVersion::IP_V4));
			eth.setGateway(gw, type);
		}
	}
	// Dns
	const XMLElement* eDNSlist = eEth->FirstChildElement(JET_ETH_DNS_LIST);
	if (eDNSlist) {
		for (const XMLElement* eDNS = eGatewaylist->FirstChildElement(JET_ETH_DNS_TAG);
			 eDNS != nullptr; eDNS = eDNS->NextSiblingElement(JET_ETH_IP_ADDR_TAG))
		{
			std::string dns = eDNS->Attribute(VALUE_ATTRIBUTE, "");
			IpVersion type = static_cast<nIpVersion>(eDNS->UnsignedAttribute(TYPE_ATTRIBUTE, nIpVersion::IP_V4));
			eth.setDNS(dns, type);
		}
	}
}
