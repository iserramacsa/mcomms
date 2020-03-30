#include "jetprotocol/jetstatus.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace tinyxml2;

//================		GET STATUS COMMAND		================//
JetGetStatus::JetGetStatus(Macsa::Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_STATUS, printer)
{}

JetGetStatus::~JetGetStatus()
{}

void JetGetStatus::buildRequest()
{
	newCommandWind();
}

bool JetGetStatus::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetStatus::buildResponse()
{
	newCommandWind();
	//TODO
}

bool JetGetStatus::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid) {
		parseCommandError();
		parsePrintheadsTemperature(xml->FirstChildElement(JET_PRINTHEADS_LIST));
		parseInkLevels(xml->FirstChildElement(JET_INK_TANKS_LIST));
		_printer.setPrintStatus(getBoolFromChildNode(xml, JET_PRINT_STATUS, _printer.printStatus()));
		_printer.setPause(getBoolFromChildNode(xml, JET_PRINT_PAUSE, _printer.paused()));
		parseCurrentMessage(xml);
		parseNetworkStatus(xml->FirstChildElement(JET_NETWORKS_LIST));
		parseInputs(xml->FirstChildElement(JET_INPUTS_LIST));
		parseOutputs(xml->FirstChildElement(JET_OUTPUTS_LIST));
		parseCounters(xml->FirstChildElement(JET_COUNTERS_LIST));

		const XMLElement* eError = xml->FirstChildElement(JET_ERROR_TAG);
		if (eError) {
			const char* isInError = eError->Attribute(VALUE_ATTRIBUTE);
			if (isInError != nullptr) {
				_printer.setIsInError(strToBool(isInError));
			}
		}

		const XMLElement* ePrintDir = xml->FirstChildElement(JET_PRINT_DIRECTION_TAG);
		if (ePrintDir) {
			unsigned int printDir = ePrintDir->UnsignedAttribute(VALUE_ATTRIBUTE, _printer.printDir()());
			_printer.setPrintDir(static_cast<Printers::nPrintDirection>(printDir));
		}

		const XMLElement* eBMPInverted = xml->FirstChildElement(JET_BITMAPINVERTED_TAG);
		if (eBMPInverted) {
			const char* bmpInverted = eBMPInverted->Attribute(VALUE_ATTRIBUTE);
			if (bmpInverted != nullptr) {
				_printer.setBitmapInverted(strToBool(bmpInverted));
			}
		}

		const XMLElement* eSSCC = xml->FirstChildElement(JET_PRINT_DIRECTION_TAG);
		if (eSSCC) {
			unsigned int sscc = eSSCC->UnsignedAttribute(VALUE_ATTRIBUTE, _printer.sscc());
			_printer.setSscc(sscc);
		}

		const XMLElement* eDatetime = xml->FirstChildElement(JET_DATETIME_TAG);
		if (eDatetime) {
			const char* datetime = eDatetime->Attribute(VALUE_ATTRIBUTE);
			if (datetime != nullptr) {
				_printer.setDateTime(datetime);
			}
		}
	}
	return valid;
}

void JetGetStatus::parsePrintheadsTemperature(const XMLElement *ePrintheads)
{
	if (ePrintheads){
		const XMLElement* ePH = ePrintheads->FirstChildElement(JET_PRINTHEAD_TAG);
		while(ePH != nullptr) {
			unsigned int id = ePH->UnsignedAttribute(ID_ATTRIBUTE, 0);
			unsigned int temperature = ePH->UnsignedAttribute(TEMPERATURE_ATTRIBUTE);
			_printer.setPrintheadTemperature(id, temperature);
			ePH = ePH->NextSiblingElement(JET_PRINTHEAD_TAG);
		}
	}
}

void JetGetStatus::parseInkLevels(const XMLElement *eTanks)
{
	if (eTanks != nullptr) {
		const XMLElement* eTank = eTanks->FirstChildElement(JET_INK_TANK);
		while(eTank != nullptr) {
			unsigned int id = eTank->UnsignedAttribute(ID_ATTRIBUTE);
			unsigned int level = eTank->UnsignedAttribute(LEVEL_ATTRIBUTE);
			_printer.setTankLevel(id, level);
			eTank = eTank->NextSiblingElement(JET_PRINTHEAD_TAG);
		}
	}
}

void JetGetStatus::parseCurrentMessage(const XMLElement *eCmd)
{
	if (eCmd) {
		unsigned int num = getUnsignedFromChildNode(eCmd, JET_MESSAGE_NUMBER);
		std::string filename = getTextFromChildNode(eCmd, JET_MESSAGE_NAME);
		if (filename.length()){
			_printer.messageManager().setCurrentMessage(filename, num);
		}
	}
}

void JetGetStatus::parseNetworkStatus(const XMLElement *eNetwork)
{
	if (eNetwork) {
		const XMLElement* eAdapter = eNetwork->FirstChildElement(JET_ADAPTER_TAG);
		while(eAdapter) {
			const XMLAttribute* eIfaceID = eAdapter->FindAttribute(ID_ATTRIBUTE);
			if (eIfaceID){
				std::string id = (eIfaceID->Value() ? eIfaceID->Value() : "");
				Printers::JetComms* comms =  dynamic_cast<Printers::JetComms*>(_printer.comms());
				if (comms) {
					Printers::Ethernet* eth = comms->ethernetIface(id);
					eth->setConnected(eAdapter->BoolAttribute(CONNECTED_ATTRIBUTE, false));
				}
			}
			eAdapter = eAdapter->NextSiblingElement(JET_ADAPTER_TAG);
		}
	}
}

void JetGetStatus::parseInputs(const XMLElement *eInputs)
{
	if (eInputs) {
		const XMLElement* eBoard = eInputs->FirstChildElement(JET_BOARD_TAG);
		while (eBoard != nullptr) {
			std::string type = getTextAttribute(eBoard, TYPE_ATTRIBUTE);
			if (type.length() > 0) {
				unsigned int number = eBoard->UnsignedAttribute(NUMBER_ATTRIBUTE, 0);
				Printers::JetBoard board = _printer.board(type, number);
				std::map<std::string, bool> inputs;
				const XMLElement* eInput = eBoard->FirstChildElement(JET_INPUT_TAG);
				while (eInput != nullptr) {
					std::string id = "";
					bool value = false;
					if (parseIOElement(eInput, id, value)) {
						inputs.insert(std::pair<std::string, bool>(id, value));
					}
					eInput = eInput->NextSiblingElement(JET_INPUT_TAG);
				}
				board.setInputs(inputs);
			}
			eBoard = eBoard->NextSiblingElement(JET_BOARD_TAG);
		}
	}
}

void JetGetStatus::parseOutputs(const XMLElement *eOutputs)
{
	if (eOutputs) {
		const XMLElement* eOutput = eOutputs->FirstChildElement(JET_OUTPUT_TAG);
		std::vector<Printers::JetIO> outputs;
		while (eOutput != nullptr) {
			std::string id = "";
			bool value = false;
			if (parseIOElement(eOutput, id, value)) {
				Printers::JetIO output(id);
				output.setValue(value);
				outputs.push_back(output);
			}
			eOutput = eOutput->NextSiblingElement(JET_OUTPUT_TAG);
		}
		_printer.setOutputs(outputs);
	}
}

void JetGetStatus::parseCounters(const XMLElement *eCounters)
{
	if (eCounters) {
		const XMLElement* eCounter = eCounters->FirstChildElement(JET_COUNTER_TAG);
		while (eCounter != nullptr) {
			unsigned int msgNum = eCounter->UnsignedAttribute(MESSAGE_ATTRIBUTE);
			unsigned int msgCnt = eCounter->UnsignedAttribute(VALUE_ATTRIBUTE);

			_printer.messageManager().setMessageCounter(msgNum, msgCnt);

			eCounter = eCounter->NextSiblingElement(JET_COUNTER_TAG);
		}
	}
}

bool JetGetStatus::parseIOElement(const XMLElement *eIO, std::string &id, bool &value)
{
	if (eIO) {
		const char* inputId = eIO->Attribute(UPPERCASE_ID_ATTRIBUTE);
		if (inputId != nullptr && strlen(inputId) > 0) {
			const char* valueStr = eIO->Attribute(VALUE_ATTRIBUTE);
			if (valueStr != nullptr) {
				value = strToBool(valueStr);
				id = inputId;
				return true;
			}
		}
	}
	return false;
}


