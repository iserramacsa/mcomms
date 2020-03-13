#include "jetprotocol/jetconfigbase.h"
#include "jetprotocol/jetprotocol.h"

#include <algorithm>

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetConfigCommand::JetConfigCommand(const std::string &command, Printers::JetPrinter &printer):
	JetCommand(command, printer)
{}

JetConfigCommand::~JetConfigCommand()
{}

void JetConfigCommand::generalConfigToXml(const Printers::JetPrinter &printer, XMLElement **parent)
{
	XMLElement * xGeneral = createChildNode(MCONFIG_GENERAL, parent);
	if(xGeneral != nullptr) {
		datetimeToXml(printer, &xGeneral);
		loggerToXml(printer, &xGeneral);
	}
}

void JetConfigCommand::datetimeToXml(const Macsa::Printers::JetPrinter &printer, XMLElement **parent)
{
	createTextChildNode(MCONFIG_GENERAL_DT, printer.formatedDateTime(), parent);
}

void JetConfigCommand::loggerToXml(const Macsa::Printers::JetPrinter &printer, XMLElement **parent)
{
	XMLElement * xLog = createChildNode(MCONFIG_GENERAL_LOG, parent);
	if(xLog != nullptr) {
		// xLog->SetAttribute(MCONFIG_GENERAL_LOG_ENABLED_ATTR, MTools::toCString(printer.logsEnabled()));
		// xLog->SetAttribute(MCONFIG_GENERAL_LOG_LEVEL_ATTR, printer.loggerLevel().toString().c_str());
		// xLog->SetAttribute(MCONFIG_GENERAL_LOG_COMMS, MTools::toCString(printer.logComsEnabled()));
	}
}

void JetConfigCommand::printerConnectionsToXml(const Printers::JetComms *comms, XMLElement **parent)
{
	XMLElement * xConnections = createChildNode(MCONFIG_CONNECTIONS, parent);
	if (xConnections != nullptr && comms != nullptr) {
		XMLElement* xNetwork = createChildNode(MCONFIG_CONN_NETWORK, &xConnections);
		if (xNetwork != nullptr) {
			for (int i = 0; i < comms->ethernetIfaces(); i++) {
				const Printers::Ethernet* eth = comms->ethernetIface(i);
				if (eth != nullptr){
					XMLElement* xAdapter = createChildNode(MCONFIG_CONN_NETWORK, &xNetwork);
					xAdapter->SetAttribute(ATTRIBUTE_ID, i);
					createTextChildNode(MCONFIG_CONN_NETWORK_IP, eth->address().c_str(), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_SUBNET, eth->netmask().c_str(), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_GATEWAY, eth->gateway().c_str(), &xNetwork);
					//createTextChildNode(MCONFIG_CONN_NETWORK_DHCP, MTools::toString(eth->dhcp()), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_HOSTNAME, eth->hostname().c_str(), &xNetwork);
					//createTextChildNode(MCONFIG_CONN_NETWORK_TCPPORT, MTools::toString(eth->tcpPort()), &xNetwork);
					createTextChildNode(MCONFIG_CONN_NETWORK_HW_ADDRESS, eth->macAddress().c_str(), &xNetwork);
				}
			}
		}
		XMLElement* xBle = createChildNode(MCONFIG_CONN_BLUETOOTH, &xConnections);
		if (xBle != nullptr) {
			const Printers::BlueTooth* ble = comms->bluetooth();
			createTextChildNode(MCONFIG_CONN_BLUETOOTH_DEVNAME, ble->name().c_str(), &xBle);
			//createTextChildNode(MCONFIG_CONN_BLUETOOTH_VISIBILITY, MTools::toString(ble->visible()), &xBle);
			createTextChildNode(MCONFIG_CONN_BLUETOOTH_PASSWORD, ble->pass().c_str(), &xBle);
		}
	}
}
void JetConfigCommand::boardToXml(const Printers::Board& board, tinyxml2::XMLElement **parent)
{
	XMLElement * xBoard = createChildNode(MPRINTER_BOARD, parent);
	if (xBoard != nullptr) {
		xBoard->SetAttribute(ATTRIBUTE_ID, board.id());
		boardTypeToXml(board.type(), &xBoard);
		autostartToXml(board.autoStart(), &xBoard);
		lowLevelOutputToXml(board.lowLevelOutput(), &xBoard);
		enabledToXml(board.enabled(), &xBoard);
		blockToXml(board.blocked(), &xBoard);
		userMessageToXml(board.userMessage(), &xBoard);
		bcdToXml(board.bcdMode(), board.bcdTable(), &xBoard);
		printDirectionToXml(board.printDirection(), &xBoard);
		printInvertedToXml(board.printRotated(), &xBoard);
		nozzlesToXml(board.nozzlesCol(), &xBoard);
		shotModeToXml(board.shotMode(), &xBoard);
		encoderToXml(board.encoder(), &xBoard);
		photocellToXml(board.photocell(), &xBoard);
		propertiesToXml(board.configurationProperties(), &xBoard);
		cartridgeToXml(board.cartridge(), &xBoard);
		inputsToXml(board.inputs(), &xBoard);
		outputsToXml(board.outputs(), &xBoard);
		if (board.printer() != nullptr){
			//dateCodesToXml(board.printer()->dateCodes(), &xBoard);
		}
	}

}

void JetConfigCommand::boardTypeToXml(const std::string  &boardType, XMLElement **parent)
{
	return boardTextValueToXml(MPRINTER_BOARD_TYPE, boardType, parent);
}

void JetConfigCommand::autostartToXml(bool autostart, XMLElement **parent)
{
	//return boardTextValueToXml(MPRINTER_BOARD_AUTOSTART, MTools::toString(autostart), parent);
}

void JetConfigCommand::lowLevelOutputToXml(bool lowLevel, XMLElement **parent)
{
	//return boardTextValueToXml(MPRINTER_BOARD_LOW_LEVEL, MTools::toString(lowLevel), parent);
}

void JetConfigCommand::enabledToXml(bool enabled, XMLElement **parent)
{
	//return boardTextValueToXml(MPRINTER_BOARD_ENABLED, MTools::toString(enabled), parent);
}

void JetConfigCommand::blockToXml(bool block, XMLElement **parent)
{
	//return boardTextValueToXml(MPRINTER_BOARD_BLOCKED, MTools::toString(block), parent);
}

void JetConfigCommand::userMessageToXml(const std::string &userMessage, XMLElement **parent)
{
	return boardTextValueToXml(MPRINTER_BOARD_CURRENT_MSG, userMessage, parent);
}

void JetConfigCommand::bcdToXml(const Printers::BCDMode& bcdMode, const Printers::BCDTable& bcdTable, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		createTextChildNode(MPRINTER_BOARD_BCD_MODE, bcdMode.toString(), parent);
		XMLElement *xBcdTable = createChildNode(MPRINTER_BOARD_BCD_TABLE, parent);
		if (xBcdTable != nullptr) {
			for (uint i = 0; i < MAX_BCD_CODES; i++) {
				XMLElement *xBcd = createChildNode(MPRINTER_BOARD_BCD_CODE, &xBcdTable);
				if (xBcd != nullptr) {
					xBcd->SetAttribute(ATTRIBUTE_CODE, i);
					xBcd->SetAttribute(ATTRIBUTE_FILEPATH, bcdTable.at(i).c_str());
				}
			}
		}
	}
}

void JetConfigCommand::printDirectionToXml(const Printers::PrinterDir &printDir, XMLElement **parent)
{
	return boardTextValueToXml(MPRINTER_BOARD_PRINT_DIR, printDir.toString(), parent);
}

void JetConfigCommand::printInvertedToXml(bool printRotated, XMLElement **parent)
{
//	return boardTextValueToXml(MPRINTER_BOARD_PRINT_INVERTED, MTools::toString(printRotated), parent);
}

void JetConfigCommand::nozzlesToXml(const Printers::NozzlesCol &nozzlesCol, XMLElement **parent)
{
	return boardTextValueToXml(MPRINTER_BOARD_NOZZLES_COL, nozzlesCol.toString(), parent);
}

void JetConfigCommand::shotModeToXml(const Printers::ShotMode &shotMode, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		XMLElement* xShotMode = createChildNode(MPRINTER_BOARD_SHOT_MODE, parent);
		if (xShotMode != nullptr) {
			const std::vector<Printers::Delay>& delays = shotMode.delays();
			xShotMode->SetAttribute(MPRINTER_BOARD_SHOT_MODE_MODE_ATTR, shotMode.mode().toString().c_str());
			xShotMode->SetAttribute(ATTRIBUTE_VALUE, shotMode.numPrints());
			xShotMode->SetAttribute(MPRINTER_BOARD_SHOT_MODE_DELAY_ATTR, static_cast<uint32_t>(delays.size()));
//			xShotMode->SetAttribute(MPRINTER_BOARD_SHOT_MODE_REPEAT_ATTR, MTools::toCString(shotMode.repeat()));
			for (uint i = 0; i < delays.size(); i++) {
				XMLElement* xDelay = createChildNode(MPRINTER_BOARD_SHOT_DELAY, &xShotMode);
				if  (xDelay != nullptr) {
					xDelay->SetAttribute(ATTRIBUTE_VALUE, delays.at(i).delay());
					xDelay->SetAttribute(MPRINTER_BOARD_SHOT_DELAY_UNITS_ATTR, delays.at(i).units().toString().c_str());
				}
			}
		}
	}
}

void JetConfigCommand::encoderToXml(const Printers::Encoder &encoder, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		XMLElement* xEncoder = createChildNode(MPRINTER_BOARD_ENCODER, parent);
		if (xEncoder != nullptr) {
			xEncoder->SetAttribute(MPRINTER_BOARD_ENCODER_MODE_ATTR, encoder.mode().toString().c_str());
			XMLElement* xFixedSpeed = createChildNode(MPRINTER_BOARD_ENCODER_FIXED, &xEncoder);
			if (xFixedSpeed != nullptr){
//				xFixedSpeed->SetAttribute(ATTRIBUTE_VALUE, MTools::toCString(encoder.fixedSpeed(), 1));
			}
			XMLElement* xExternal = createChildNode(MPRINTER_BOARD_ENCODER_EXTERNAL, &xEncoder);
			if (xExternal != nullptr){
				// xExternal->SetAttribute(MPRINTER_BOARD_ENCODER_EXT_RESOL_ATTR, MTools::toCString(encoder.resolution(), 0));
				// xExternal->SetAttribute(MPRINTER_BOARD_ENCODER_EXT_DIAM_ATTR, MTools::toCString(encoder.diameter(), 1));
			}
		}
	}
}

void JetConfigCommand::photocellToXml(const Printers::Photocell &photocell, XMLElement **parent)
{
	return boardTextValueToXml(MPRINTER_BOARD_PHOTOCELL, photocell.toString(), parent);
}

void JetConfigCommand::propertiesToXml(const Printers::Board::propertyMap &properties, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		XMLElement* xProperties = createChildNode(MPRINTER_BOARD_PROPERTIES_LIST, parent);
		if (xProperties != nullptr) {
			for (Printers::Board::propertyMap::const_iterator prop = properties.begin(); prop != properties.end(); prop++) {
				XMLElement* xProperty = createChildNode(MPRINTER_BOARD_PROPERTY, &xProperties);
				if (xProperty != nullptr) {
					xProperty->SetAttribute(ATTRIBUTE_KEY, prop->first.c_str());
					xProperty->SetAttribute(ATTRIBUTE_VALUE, prop->second.c_str());
				}
			}
		}
	}
}

void JetConfigCommand::cartridgeToXml(const Printers::Cartridge &cartridge, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		XMLElement* xCartridge = createChildNode(MPRINTER_BOARD_CARTRIDGE, parent);
		if (xCartridge != nullptr) {
			xCartridge->SetAttribute(ATTRIBUTE_ID, cartridge.id().c_str());
			xCartridge->SetAttribute(MPRINTER_BOARD_CARTRIDGE_AUTOCONFIG_ATTR, (cartridge.autoconfig() ? "1" : "0")); //This boolean is writed as a number
			// xCartridge->SetAttribute(MPRINTER_BOARD_CARTRIDGE_VOLTAGE_ATTR, MTools::toCString(cartridge.voltage(), 2));
			// xCartridge->SetAttribute(MPRINTER_BOARD_CARTRIDGE_PULSE_WARM_ATTR, MTools::toCString(cartridge.pulseWarming()));
			// xCartridge->SetAttribute(MPRINTER_BOARD_CARTRIDGE_WARM_TEMP_ATTR, MTools::toCString(cartridge.pulseWarmingTemp(), 2));
			// xCartridge->SetAttribute(MPRINTER_BOARD_CARTRIDGE_COL_DIST_ATTR, MTools::toCString(cartridge.columnDistance()));
			// xCartridge->SetAttribute(MPRINTER_BOARD_CARTRIDGE_PULSE_WIDTH_ATTR, MTools::toCString(cartridge.pulseWidth(), 2));
			// xCartridge->SetAttribute(MPRINTER_BOARD_CARTRIDGE_ADJ_CAPACITY_ATTR, MTools::toCString(cartridge.adjustedCapacity()));
		}
	}
}

void JetConfigCommand::inputsToXml(const std::vector<Printers::Input> &inputs, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		XMLElement* xInputs = createChildNode(MPRINTER_BOARD_INPUTS_LIST, parent);
		if (xInputs != nullptr) {
			for (std::vector<Printers::Input>::const_iterator input = inputs.begin(); input != inputs.end(); input++) {
				XMLElement* xInput = createChildNode(MPRINTER_BOARD_INPUT, &xInputs);
				if (xInput != nullptr) {
					xInput->SetAttribute(ATTRIBUTE_ID, input->id());
					xInput->SetAttribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR, input->descriptor().c_str());
					xInput->SetAttribute(MPRINTER_BOARD_IO_CONFIG_ATTR, input->mode().toString().c_str());
					//xInput->SetAttribute(MPRINTER_BOARD_IO_INVERTED_ATTR, MTools::toCString(input->inverted()));
					xInput->SetAttribute(MPRINTER_BOARD_IO_FILTER_ATTR, input->filter());
				}
			}
		}
	}
}

void JetConfigCommand::outputsToXml(const std::vector<Macsa::Printers::Output> &outputs, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		XMLElement* xOutputs = createChildNode(MPRINTER_BOARD_OUTPUTS_LIST, parent);
		if (xOutputs != nullptr) {
			for (std::vector<Printers::Output>::const_iterator output = outputs.begin(); output != outputs.end(); output++) {
				XMLElement* xOutput = createChildNode(MPRINTER_BOARD_OUTPUT, &xOutputs);
				if (xOutput != nullptr) {
					xOutput->SetAttribute(ATTRIBUTE_ID, output->id());
					xOutput->SetAttribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR, output->descriptor().c_str());
					xOutput->SetAttribute(MPRINTER_BOARD_IO_TYPE_ATTR, output->type().toString().c_str());
					xOutput->SetAttribute(MPRINTER_BOARD_IO_TIME_ATTR, output->time());
//					xOutput->SetAttribute(MPRINTER_BOARD_IO_INI_VAL_ATTR, MTools::toCString(output->initialValue()));
				}
			}
		}
	}
}

void JetConfigCommand::dateCodesToXml(const Macsa::Printers::DateCodes &dateCodes, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		XMLElement* xDCList = createChildNode(MPRINTER_DATECODES_LIST, parent);
		if (xDCList != nullptr) {
			dateCodesFormatedListToXml(CODE_FORMAT_MINUTE, dateCodes.getMinuteCodes(),     &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_HOUR,   dateCodes.getHourCodes(),       &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_DOM,    dateCodes.getDayCodes(),	       &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_DOW,    dateCodes.getDayOfWeekCodes(),  &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_DOY,    dateCodes.getJulianCodes(),     &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_WOY,    dateCodes.getWeekOfYearCodes(), &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_MONTH,  dateCodes.getMonthCodes(),      &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_YEAR,   dateCodes.getYearCodes(),       &xDCList);
			dateCodesFormatedListToXml(CODE_FORMAT_SHIFT,  dateCodes.getShiftCodes(),      &xDCList);
		}
	}

}

void JetConfigCommand::generalConfigFromXml(const tinyxml2::XMLElement *parent, Printers::JetPrinter& printer) const
{
	if (parent != nullptr) {
		const XMLElement* xGeneral = parent->FirstChildElement(MCONFIG_GENERAL);
		if (xGeneral != nullptr) {
			printer.setDateTime(getTextFromChildNode(xGeneral, MCONFIG_GENERAL_DT, _printer.formatedDateTime()));
			const XMLElement* xLog = xGeneral->FirstChildElement(MCONFIG_GENERAL_LOG);
			if (xLog != nullptr) {
				printer.setlogsEnabled(getBoolAttribute(xLog, MCONFIG_GENERAL_LOG_ENABLED_ATTR, printer.logsEnabled()));
				printer.setloggerLevel(getTextAttribute(xLog, MCONFIG_GENERAL_LOG_LEVEL_ATTR, printer.loggerLevel().toString()));
				printer.setlogComsEnabled(getBoolAttribute(xLog, MCONFIG_GENERAL_LOG_COMMS, printer.logComsEnabled ()));
			}
		}
	}
}

void JetConfigCommand::printerConnectionsFromXml(const XMLElement *parent, Printers::JetComms &comms) const
{
	if (parent != nullptr) {
		const XMLElement* xConnections = parent->FirstChildElement(MCONFIG_CONNECTIONS);
		if (xConnections != nullptr) {
			const XMLElement* xNetwork = xConnections->FirstChildElement(MCONFIG_CONN_NETWORK);
			if (xNetwork != nullptr) {
				const XMLElement* xAdapter = xNetwork->FirstChildElement(MCONFIG_CONN_NETWORK_ADAPTER);
				while (xAdapter != nullptr) {
					int id = xAdapter->IntAttribute(ATTRIBUTE_ID, 0);
					Printers::Ethernet eth;
					if (comms.ethernetIface(id) != nullptr) {
						eth = (*(comms.ethernetIface(id)));
					}

					eth.setAddress(getTextFromChildNode(xAdapter, MCONFIG_CONN_NETWORK_IP,  eth.address()));
					eth.setNetmask(getTextFromChildNode(xAdapter, MCONFIG_CONN_NETWORK_SUBNET,  eth.netmask()));
					eth.setGateway(getTextFromChildNode(xAdapter, MCONFIG_CONN_NETWORK_GATEWAY,  eth.gateway()));
					eth.setDhcp(getBoolFromChildNode(xAdapter, MCONFIG_CONN_NETWORK_DHCP, eth.dhcp()));
					eth.setHostname(getTextFromChildNode(xAdapter, MCONFIG_CONN_NETWORK_HOSTNAME, eth.hostname()));
					eth.setMacAddress(getTextFromChildNode(xAdapter, MCONFIG_CONN_NETWORK_HW_ADDRESS, eth.macAddress()));
					eth.setTcpPort(static_cast<uint16_t>(getUnsignedFromChildNode(xAdapter, MCONFIG_CONN_NETWORK_TCPPORT, eth.tcpPort())));

					comms.setEthernetIface(&eth);

					xAdapter = xAdapter->NextSiblingElement(MCONFIG_CONN_NETWORK_ADAPTER);
				}
			}
			const XMLElement* xBle = xConnections->FirstChildElement(MCONFIG_CONN_BLUETOOTH);
			if (xBle != nullptr) {
				Printers::BlueTooth ble = *comms.bluetooth();
				ble.setName(getTextFromChildNode(xBle, MCONFIG_CONN_BLUETOOTH_DEVNAME,  ble.name()));
				ble.setPass(getTextFromChildNode(xBle, MCONFIG_CONN_BLUETOOTH_PASSWORD,  ble.pass()));
				ble.setVisible(getBoolFromChildNode(xBle, MCONFIG_CONN_BLUETOOTH_VISIBILITY,  ble.visible()));

				comms.setBluetooth(ble);
			}
		}
	}
}

void JetConfigCommand::boardFromXml(const XMLElement *xBoard, Printers::Board &board) const
{
	if (xBoard != nullptr && std::strcmp(xBoard->Name(), MPRINTER_BOARD) == 0) {
		int id = xBoard->IntAttribute(ATTRIBUTE_ID, -1);
		if (id == board.id()) {
			board.setType(getTextFromChildNode(xBoard, MPRINTER_BOARD_TYPE, board.type()));
			board.setAutoStart(getBoolFromChildNode(xBoard, MPRINTER_BOARD_AUTOSTART, board.autoStart()));
			board.setLowLevelOutput(getBoolFromChildNode(xBoard, MPRINTER_BOARD_LOW_LEVEL, board.lowLevelOutput()));
			board.setEnabled(getBoolFromChildNode(xBoard, MPRINTER_BOARD_ENABLED, board.enabled()));
			board.setBlocked(getBoolFromChildNode(xBoard, MPRINTER_BOARD_BLOCKED, board.blocked()));
			board.setUserMessage(getTextFromChildNode(xBoard, MPRINTER_BOARD_CURRENT_MSG, board.userMessage()));
			bcdFromXml(xBoard, board);
			board.setPrinterDirection(getTextFromChildNode(xBoard, MPRINTER_BOARD_PRINT_DIR, board.printDirection().toString().c_str()));
			board.setPrintRotated(getBoolFromChildNode(xBoard, MPRINTER_BOARD_PRINT_INVERTED, board.printRotated()));
			board.setNozzlesCol(getTextFromChildNode(xBoard, MPRINTER_BOARD_NOZZLES_COL, board.nozzlesCol().toString().c_str()));
			shotModeFromXml(xBoard, board);
			encoderFromXml(xBoard, board);
			board.setPhotocell(getTextFromChildNode(xBoard, MPRINTER_BOARD_PHOTOCELL, board.photocell().toString().c_str()));
			propertiesFromXml(xBoard, board);
			cartridgeFromXml(xBoard, board);
			inputsFromXml(xBoard, board);
			outputsFromXml(xBoard, board);
			if (board.printer() != nullptr){
//				dateCodesFromXml(xBoard, *(board.printer()));
			}
		}
	}
}

void JetConfigCommand::bcdFromXml(const XMLElement *xBoard, Macsa::Printers::Board &board) const
{
	if (xBoard != nullptr) {
		board.setBcdMode(getTextFromChildNode(xBoard, MPRINTER_BOARD_BCD_MODE, board.bcdMode().toString()));
		const XMLElement* xBcdTable = xBoard->FirstChildElement(MPRINTER_BOARD_BCD_TABLE);
		if (xBcdTable != nullptr) {
			Printers::BCDTable bcdTable;
			const XMLElement* xBcdCode = xBcdTable->FirstChildElement(MPRINTER_BOARD_BCD_CODE);
			while (xBcdCode != nullptr) {
				uint code = xBcdCode->UnsignedAttribute(ATTRIBUTE_CODE);
				if (code < MAX_BCD_CODES) {
					bcdTable[code] = getTextAttribute(xBcdCode, ATTRIBUTE_FILEPATH, "");
				}
				xBcdCode = xBcdCode->NextSiblingElement(MPRINTER_BOARD_BCD_CODE);
			}
			board.setBcdTable(bcdTable);
		}
	}
}

void JetConfigCommand::shotModeFromXml(const XMLElement *xBoard, Macsa::Printers::Board &board) const
{
	if (xBoard != nullptr) {
		const XMLElement* xShotMode = xBoard->FirstChildElement(MPRINTER_BOARD_SHOT_MODE);
		if (xShotMode != nullptr) {
			Printers::ShootingMode mode;
			mode = static_cast<Printers::nShootingMode>(xShotMode->UnsignedAttribute(MPRINTER_BOARD_SHOT_MODE_MODE_ATTR, static_cast<uint>(mode())));
			uint numPrints = xShotMode->UnsignedAttribute(ATTRIBUTE_VALUE, 1);
			uint numDelays = xShotMode->UnsignedAttribute(MPRINTER_BOARD_SHOT_MODE_DELAY_ATTR, 1);
			bool repeat = getBoolAttribute (xShotMode, MPRINTER_BOARD_SHOT_MODE_REPEAT_ATTR, false);
			const XMLElement* xDelay = xShotMode->FirstChildElement(MPRINTER_BOARD_SHOT_DELAY);
			std::vector<Printers::Delay> delays;
			while (xDelay != nullptr) {
				uint delay = xDelay->UnsignedAttribute(ATTRIBUTE_VALUE, 0);
				Printers::DelayUnits units;
				units = getTextAttribute(xDelay, MPRINTER_BOARD_SHOT_DELAY_UNITS_ATTR, "");
				if (delays.size() < numDelays){
					delays.push_back(Printers::Delay(delay, units()));
				}
				else{
					break;
				}
				xDelay = xDelay->NextSiblingElement(MPRINTER_BOARD_SHOT_DELAY);
			}
			board.setShotMode(Printers::ShotMode(mode, numPrints, delays, repeat));
		}
	}
}

void JetConfigCommand::encoderFromXml(const XMLElement *xBoard, Macsa::Printers::Board &board) const
{
	if (xBoard != nullptr) {
		const XMLElement* xEncoder = xBoard->FirstChildElement(MPRINTER_BOARD_ENCODER);
		if (xEncoder) {
			Printers::Encoder encoder = board.encoder();
			Printers::EncoderMode mode = encoder.mode();
			mode = getTextAttribute(xEncoder, MPRINTER_BOARD_ENCODER_MODE_ATTR, encoder.mode().toString());
			encoder.setMode(mode);
			const XMLElement* xFixed = xEncoder->FirstChildElement(MPRINTER_BOARD_ENCODER_FIXED);
			if (xFixed) {
				encoder.setFixedSpeed(xFixed->DoubleAttribute(ATTRIBUTE_VALUE, encoder.fixedSpeed()));
			}
			const XMLElement* xExternal = xEncoder->FirstChildElement(MPRINTER_BOARD_ENCODER_EXTERNAL);
			if (xExternal) {
				encoder.setDiameter(xExternal->DoubleAttribute(MPRINTER_BOARD_ENCODER_EXT_DIAM_ATTR, encoder.diameter()));
				encoder.setResolution(xExternal->DoubleAttribute(MPRINTER_BOARD_ENCODER_EXT_RESOL_ATTR, encoder.resolution()));
			}

			board.setEncoder(encoder);
		}
	}
}

void JetConfigCommand::propertiesFromXml(const XMLElement *xBoard, Macsa::Printers::Board &board) const
{
	if (xBoard != nullptr) {
		const XMLElement* xProperties = xBoard->FirstChildElement(MPRINTER_BOARD_PROPERTIES_LIST);
		if (xProperties) {
			Printers::Board::propertyMap properties;
			const XMLElement* xProperty = xProperties->FirstChildElement(MPRINTER_BOARD_PROPERTY);
			while (xProperty != nullptr) {
				std::string key = getTextAttribute(xProperty, ATTRIBUTE_KEY, "");
				if (!key.empty()){
					std::string value = getTextAttribute(xProperty, ATTRIBUTE_VALUE, "");
					properties.insert(Printers::Board::propertyPair(key, value));
				}
				xProperty = xProperty->NextSiblingElement(MPRINTER_BOARD_PROPERTY);
			}
			board.setConfigurationProperties(properties);
		}
	}
}

void JetConfigCommand::cartridgeFromXml(const XMLElement *xBoard, Macsa::Printers::Board &board) const
{
	if (xBoard != nullptr) {
		const XMLElement* xCartridge = xBoard->FirstChildElement(MPRINTER_BOARD_CARTRIDGE);
		if (xCartridge) {
			Printers::Cartridge cartridge = board.cartridge();

			cartridge.setId(getTextAttribute(xCartridge, ATTRIBUTE_ID, cartridge.id()));
			cartridge.setAutoconfig(xCartridge->BoolAttribute(MPRINTER_BOARD_CARTRIDGE_AUTOCONFIG_ATTR, cartridge.autoconfig()));
//			cartridge.setAutoconfig(getBoolAttribute(xCartridge, MPRINTER_BOARD_CARTRIDGE_AUTOCONFIG_ATTR, cartridge.autoconfig()));
			cartridge.setVoltage(xCartridge->DoubleAttribute(MPRINTER_BOARD_CARTRIDGE_VOLTAGE_ATTR, cartridge.voltage()));
			cartridge.setPulseWarming(getBoolAttribute(xCartridge, MPRINTER_BOARD_CARTRIDGE_PULSE_WARM_ATTR, cartridge.pulseWarming()));
			cartridge.setPulseWarmingTemp(xCartridge->DoubleAttribute(MPRINTER_BOARD_CARTRIDGE_WARM_TEMP_ATTR, cartridge.pulseWarmingTemp()));
			cartridge.setColumnDistance(xCartridge->UnsignedAttribute(MPRINTER_BOARD_CARTRIDGE_COL_DIST_ATTR, cartridge.columnDistance()));
			cartridge.setPulseWidth(xCartridge->DoubleAttribute(MPRINTER_BOARD_CARTRIDGE_PULSE_WIDTH_ATTR, cartridge.pulseWidth()));
			cartridge.setAdjustedCapacity(xCartridge->UnsignedAttribute(MPRINTER_BOARD_CARTRIDGE_ADJ_CAPACITY_ATTR, cartridge.adjustedCapacity()));

			board.setCartridge(cartridge);
		}
	}
}

void JetConfigCommand::inputsFromXml(const XMLElement *xBoard, Macsa::Printers::Board &board) const
{
	if (xBoard != nullptr) {
		const XMLElement* xInputs = xBoard->FirstChildElement(MPRINTER_BOARD_INPUTS_LIST);
		if (xInputs) {
			std::vector<Printers::Input> inputs;

			const XMLElement* xInput = xInputs->FirstChildElement(MPRINTER_BOARD_INPUT);
			while (xInput != nullptr) {
				uint id = xInput->UnsignedAttribute(ATTRIBUTE_ID, static_cast<unsigned>(inputs.size()));
				Printers::Input input(id);
				input = board.input(id);
				input.setDescriptor(getTextAttribute(xInput, MPRINTER_BOARD_IO_DESCRIPT_ATTR, input.descriptor()));
				input.setMode(getTextAttribute(xInput, MPRINTER_BOARD_IO_CONFIG_ATTR, input.mode().toString()));
				input.setInverted(getBoolAttribute(xInput, MPRINTER_BOARD_IO_INVERTED_ATTR, input.inverted()));
				input.setFilter(xInput->UnsignedAttribute(MPRINTER_BOARD_IO_FILTER_ATTR, input.filter()));

				inputs.push_back(input);

				xInput = xInput->NextSiblingElement(MPRINTER_BOARD_INPUT);
			}
			std::sort(inputs.begin(), inputs.end());
			board.setInputs(inputs);
		}
	}
}

void JetConfigCommand::outputsFromXml(const XMLElement *xBoard, Macsa::Printers::Board &board) const
{
	if (xBoard != nullptr) {
		const XMLElement* xOutputs = xBoard->FirstChildElement(MPRINTER_BOARD_OUTPUTS_LIST);
		if (xOutputs) {
			std::vector<Printers::Output> outputs;

			const XMLElement* xOutput = xOutputs->FirstChildElement(MPRINTER_BOARD_OUTPUT);
			while (xOutput != nullptr) {
				uint id = xOutput->UnsignedAttribute(ATTRIBUTE_ID, static_cast<unsigned>(outputs.size()));
				Printers::Output output(id);
				output = board.output(id);
				output.setDescriptor(getTextAttribute(xOutput, MPRINTER_BOARD_IO_DESCRIPT_ATTR, output.descriptor()));
				output.setType(getTextAttribute(xOutput, MPRINTER_BOARD_IO_TYPE_ATTR, output.type().toString()));
				output.setTime(xOutput->UnsignedAttribute(MPRINTER_BOARD_IO_TIME_ATTR, output.time()));
				output.setInitialValue(getBoolAttribute(xOutput, MPRINTER_BOARD_IO_INI_VAL_ATTR, output.initialValue()));

				outputs.push_back(output);

				xOutput = xOutput->NextSiblingElement(MPRINTER_BOARD_OUTPUT);
			}
			std::sort(outputs.begin(), outputs.end());
			board.setOutputs(outputs);
		}
	}
}

void JetConfigCommand::dateCodesFromXml(const XMLElement *xBoard, Macsa::Printers::JetPrinter &printer) const
{
	if (xBoard != nullptr) {
		const XMLElement* xDateCodes = xBoard->FirstChildElement(MPRINTER_DATECODES_LIST);
		if (xDateCodes != nullptr) {
			Printers::DateCodes dateCodes;
			const XMLElement* xDateCode = xDateCodes->FirstChildElement(MPRINTER_DATECODE);
			while (xDateCode != nullptr){
				std::string format = getTextAttribute(xDateCode, MPRINTER_DATECODE_FORMAT_ATTR, "");
				const XMLElement* xCode = xDateCode->FirstChildElement(MPRINTER_DATECODE_CODE);
				while (xCode != nullptr) {
					std::string interval = getTextAttribute(xCode, MPRINTER_DATECODE_INTERVAL_ATTR, "");
					const char* code = xCode->GetText();
					if (code == nullptr) {
						code = "";
					}

					dateCodes.addCode(code, format, interval);

					xCode = xCode->NextSiblingElement(MPRINTER_DATECODE_CODE);
				}
				xDateCode = xDateCode->NextSiblingElement(MPRINTER_DATECODE);
			}
			printer.setDateCodes(dateCodes);
		}
	}
}

template<class T>
void JetConfigCommand::dateCodesFormatedListToXml(const std::string &format, const std::vector<T> &dateCodesList, XMLElement **parent)
{
	if (dateCodesList.size()) {
		XMLElement* xDateCodes = createChildNode(MPRINTER_DATECODE, parent);
		if (xDateCodes != nullptr) {
			xDateCodes->SetAttribute(MPRINTER_DATECODE_FORMAT_ATTR, format.c_str());
			for (uint dc = 0; dc < dateCodesList.size(); dc++) {
				XMLElement* xCode = createTextChildNode(MPRINTER_DATECODE_CODE, dateCodesList.at(dc).getCode().c_str(), &xDateCodes);
				if (xCode) {
					xCode->SetAttribute(MPRINTER_DATECODE_INTERVAL_ATTR, dateCodesList.at(dc).getIntervalStart().c_str());
				}
			}
		}
	}
}


void JetConfigCommand::boardTextValueToXml(const std::string &valueName, const std::string &value, XMLElement **parent)
{
	if (*parent != nullptr && std::strcmp((*parent)->Name(), MPRINTER_BOARD) == 0) {
		createTextChildNode(valueName, value, parent);
	}
}

