//#include "mboard.h"
//#include "mtools.h"
//#include <sstream>

//#include "mprotocol/mprotocol.h"

//using namespace Macsa;
//using namespace Macsa::MProtocol;


//XMLElement *MPrinter::generalConfigToXml(const Printers::TIJPrinter& printer, XMLDocument &doc)
//{
//	XMLElement *general = doc.NewElement(MCONFIG_GENERAL);
//	MTools::XML::newTextElement(MCONFIG_GENERAL_DT, printer.formatedDateTime().c_str(), doc, &general);

////	const Printers::Configuration& config = printer.configuration();

//	XMLElement *log = doc.NewElement(MCONFIG_GENERAL_LOG);
////	log->SetAttribute(MCONFIG_GENERAL_LOG_LEVEL_ATTR,	printer.logLevel().toString().c_str());
////	log->SetAttribute(MCONFIG_GENERAL_LOG_ENABLED_ATTR,	MTools::toString(config.traceLogs()).c_str());
////	log->SetAttribute(MCONFIG_GENERAL_LOG_COMMS,		MTools::toString(config.traceComms()).c_str());
//	general->InsertEndChild(log);

//	return general;
//}

//XMLElement* MPrinter::printerConnectionsToXml(const Printers::TIJComms* comms, XMLDocument &doc)
//{
//	XMLElement*	connections = doc.NewElement(MCONFIG_CONNECTIONS);
//	XMLElement*	network = MTools::XML::newElement(MCONFIG_CONN_NETWORK, doc, &connections);
//	if(network != nullptr) {
//		for (int i = 0; i < comms->ethernetIfaces(); i++) {
//			const Printers::Ethernet* eth = comms->ethernetIface(i);
//			XMLElement* iface = MTools::XML::newTextElement(MCONFIG_CONN_NETWORK_ADAPTER, eth->address().c_str(), doc, &network);
//			iface->SetAttribute(MCONFIG_CONN_NETWORK_ADAPTER_ID_ATTR, i);
//			MTools::XML::newTextElement(MCONFIG_CONN_NETWORK_SUBNET,		eth->netmask().c_str(),		doc, &network);
//			MTools::XML::newTextElement(MCONFIG_CONN_NETWORK_GATEWAY,	eth->gateway().c_str(),		doc, &network);
//			MTools::XML::newTextElement(MCONFIG_CONN_NETWORK_DHCP,		MTools::toString(eth->dhcp()),		doc, &network);
//			MTools::XML::newTextElement(MCONFIG_CONN_NETWORK_HOSTNAME,	eth->hostname().c_str(),	doc, &network);
//			MTools::XML::newTextElement(MCONFIG_CONN_NETWORK_TCPPORT,	std::to_string(eth->tcpPort()),	doc, &network);
//		}
//	}
//	XMLElement*	ble = MTools::XML::newElement(MCONFIG_CONN_BLUETOOTH, doc, &connections);
//	if(ble != nullptr) {
//		MTools::XML::newTextElement(MCONFIG_CONN_BLUETOOTH_DEVNAME,		comms->bluetooth()->name(), doc, &ble);
//		MTools::XML::newTextElement(MCONFIG_CONN_BLUETOOTH_VISIBILITY,	MTools::toString(comms->bluetooth()->visible()), doc, &ble);
//		MTools::XML::newTextElement(MCONFIG_CONN_BLUETOOTH_PASSWORD,		comms->bluetooth()->pass(), doc, &ble);
//	}

//	return connections;
//}

//XMLElement *MPrinter::boardConfigToXml(const Printers::Board &board, XMLDocument &doc)
//{
//	XMLElement* eBoard = doc.NewElement(MPRINTER_BOARD);
//	eBoard->SetAttribute(MPRINTER_BOARD_ID_ATTR, board.id());
//	MTools::XML::newTextElement(MPRINTER_BOARD_TYPE, board.type().c_str(), doc, &eBoard);
//	MTools::XML::newTextElement(MPRINTER_BOARD_AUTOSTART, board.autoStart(), doc, &eBoard);
//	MTools::XML::newTextElement(MPRINTER_BOARD_ENABLED,	board.enabled(), doc, &eBoard);
//	MTools::XML::newTextElement(MPRINTER_BOARD_BLOCKED,	board.blocked(), doc, &eBoard);
//	MTools::XML::newTextElement(MPRINTER_BOARD_CURRENT_MSG,	board.currentMessage(), doc, &eBoard);
//	MTools::XML::newTextElement(MPRINTER_BOARD_BCD_MODE, board.bcdMode().toString(), doc, &eBoard);
//	XMLElement* eBCDTable = boardBCDTableToXml(board.bcdTable(), doc);
//	if  (eBCDTable != nullptr) {
//		eBoard->InsertEndChild(eBCDTable);
//	}
//	MTools::XML::newTextElement(MPRINTER_BOARD_PRINT_DIR, board.printerDirection().toString(), doc, &eBoard);
//	MTools::XML::newTextElement(MPRINTER_BOARD_PRINT_INVERTED, board.printRotated(), doc, &eBoard);
//	MTools::XML::newTextElement(MPRINTER_BOARD_NOZZLES_COL, board.nozzlesCol().toString(), doc, &eBoard);
//	XMLElement* eShotMode = boardShotModeToXml(board.shotMode(), doc);
//	if  (eShotMode != nullptr) {
//		eBoard->InsertEndChild(eShotMode);
//	}
//	XMLElement* eEncoder = boardEncoderToXml(board.encoder(), doc);
//	if  (eEncoder != nullptr) {
//		eBoard->InsertEndChild(eEncoder);
//	}

//	//TODO fill with board info

//	return eBoard;
//}

//XMLElement *MPrinter::boardBCDTableToXml(const Printers::BCDTable &bcdTable, XMLDocument &doc)
//{
//	XMLElement* eBCDTable = doc.NewElement(MPRINTER_BOARD_BCD_TABLE);
//	if(eBCDTable != nullptr) {
//		for (uint8_t i = 0; i < MAX_BCD_CODES; i++) {
//			XMLElement* eBcdCode = MTools::XML::newElement(MPRINTER_BOARD_BCD_TABLE, doc, &eBCDTable);
//			eBcdCode->SetAttribute(MPRINTER_BOARD_BCD_CODE_ATTR, i);
//			eBcdCode->SetAttribute(MPRINTER_BOARD_BCD_MSG_ATTR, bcdTable.at(i).c_str());
//		}
//	}
//	return eBCDTable;
//}

//XMLElement *MPrinter::boardShotModeToXml(const Printers::ShotMode &shotMode, XMLDocument &doc)
//{
//	XMLElement* eShotMode = doc.NewElement(MPRINTER_BOARD_SHOT_MODE);
//	if(eShotMode != nullptr) {
//		eShotMode->SetAttribute(MPRINTER_BOARD_SHOT_MODE_MODE_ATTR, shotMode.mode().toString().c_str());
//		eShotMode->SetAttribute(MPRINTER_BOARD_SHOT_MODE_VALUE_ATTR, shotMode.numPrints());
//		eShotMode->SetAttribute(MPRINTER_BOARD_SHOT_MODE_DELAY_ATTR, static_cast<unsigned>(shotMode.delays().size()));
//		eShotMode->SetAttribute(MPRINTER_BOARD_SHOT_MODE_REPEAT_ATTR, shotMode.repeat());
//		for (Printers::ShotMode::citDelay delay = shotMode.delays().begin(); delay != shotMode.delays().end(); delay++)
//		{
//			XMLElement* eDelay = doc.NewElement(MPRINTER_BOARD_SHOT_DELAY);
//			if(eDelay != nullptr) {
//				eDelay->SetAttribute(MPRINTER_BOARD_SHOT_DELAY_VALUE_ATTR, delay->delay());
//				eDelay->SetAttribute(MPRINTER_BOARD_SHOT_DELAY_UNITS_ATTR, delay->units().toString().c_str());
//				eShotMode->InsertEndChild(eDelay);
//			}
//		}
//	}
//	return eShotMode;
//}

//XMLElement *MPrinter::boardEncoderToXml(const Printers::Encoder &encoder, XMLDocument &doc)
//{
//#define MPRINTER_BOARD_ENCODER			"ENCODER"
//#define MPRINTER_BOARD_ENCODER_MODE_ATTR	"CurrentMode"
//#define MPRINTER_BOARD_ENCODER_FIXED	"FIXED_SPEED"
//#define MPRINTER_BOARD_ENCODER_FIXED_VALUE_ATTR	ATTRIBUTE_VALUE
//#define MPRINTER_BOARD_ENCODER_EXTERNAL	"EXTERNAL_ENCODER"
//#define MPRINTER_BOARD_ENCODER_EXT_RESOL_ATTR	"Resolution"
//#define MPRINTER_BOARD_ENCODER_EXT_DIAM_ATTR	"Diameter"
//	XMLElement* eEncoder = doc.NewElement(MPRINTER_BOARD_ENCODER);
//	if(eEncoder != nullptr) {
//		eEncoder->SetAttribute(MPRINTER_BOARD_ENCODER_MODE_ATTR, encoder.mode().toString().c_str());

//	}

//	return eEncoder;
//}


//void MPrinter::boardFromXml(Printers::TIJPrinter &printer, const XMLElement *xmlboard)
//{
//	std::string tagName = MPRINTER_BOARD;
//	if (xmlboard != nullptr && tagName.compare(xmlboard->Name()) == 0)
//	{
//		const char* id = xmlboard->Attribute(MPRINTER_BOARD_ID_ATTR);

//		if (id != nullptr) {
//			const int boardId = atoi(id);
//			Printers::Board* pBoard = printer.board(boardId);
//			Printers::Board board(boardId);
//			//fill the board with the previous values if needed
//			if (pBoard != nullptr) {
//				board = *pBoard;
//			}

//			board.setType(MTools::XML::textFromChild(xmlboard, MPRINTER_BOARD_TYPE));
//			board.setPrinting(MTools::XML::boolFromChild(xmlboard, MPRINTER_BOARD_PRINTING));
//			board.setEnabled(MTools::XML::boolFromChild(xmlboard, MPRINTER_BOARD_ENABLED));
//			board.setBlocked(MTools::XML::boolFromChild(xmlboard, MPRINTER_BOARD_BLOCKED));
//			board.setAutoStart(MTools::XML::boolFromChild(xmlboard, MPRINTER_BOARD_AUTOSTART));
//			board.setUserMessage(MTools::XML::textFromChild(xmlboard, MPRINTER_BOARD_CURRENT_MSG));
//			board.setBcdMode(MTools::XML::textFromChild(xmlboard, MPRINTER_BOARD_BCD_MODE));
//			board.setBcdCurrent(static_cast<uint8_t>(MTools::XML::intFromChild(xmlboard, MPRINTER_BOARD_BCD_STATUS)));

//			parseCounters(board, xmlboard);
//			parseErrors(board, xmlboard);
//			parseInputs(board, xmlboard);
//			parseOutputs(board, xmlboard);

//			printer.setBoard(board);
//		}
//	}
//}

//void MPrinter::parseCounters(Printers::Board &board, const XMLElement *eBoard)
//{
//	const XMLElement* counters = eBoard->FirstChildElement(MPRINTER_BOARD_COUNTERS_LIST);
//	if (counters !=  nullptr) {
//		board.counters().clear();
//		const XMLElement* counter = counters->FirstChildElement(MPRINTER_BOARD_COUNTER);
//		while (counter != nullptr) {
//			std::string countId = counter->Attribute(MPRINTER_BOARD_COUNT_ID_ATTR);
//			int countVal = counter->IntAttribute(MPRINTER_BOARD_COUNT_VAL_ATTR);
//			board.setCounter(countId, countVal);
//			counter = counters->NextSiblingElement(MPRINTER_BOARD_COUNTER);
//		}
//	}
//}

//void MPrinter::parseErrors(Printers::Board &board, const XMLElement *eBoard)
//{
//	const XMLElement* errors = eBoard->FirstChildElement(MPRINTER_BOARD_ERRORS_LIST);
//	if (errors !=  nullptr) {
//		const XMLElement* error = errors->FirstChildElement(MPRINTER_BOARD_ERROR);
//		std::vector<Printers::Error> errorsList;
//		errorsList.clear();
//		while (error != nullptr) {
//			Printers::ErrorType eType;
//			Printers::ErrorCode eCode;
//			std::string tStamp = error->Attribute(MPRINTER_BOARD_ERR_TSTAMP_ATTR);
//			eType = error->Attribute(MPRINTER_BOARD_ERR_TYPE_ATTR);
//			eCode = error->Attribute(MPRINTER_BOARD_ERR_CODE_ATTR);
//			unsigned int ePriority = error->UnsignedAttribute(MPRINTER_BOARD_ERR_PRIO_ATTR);
//			Printers::Error err(MTools::dateTime(tStamp), eType, eCode, ePriority);
//			errorsList.push_back(err);

//			error = error->NextSiblingElement(MPRINTER_BOARD_ERROR);
//		}
//		board.setErrors(errorsList);
//	}
//}

//void MPrinter::parseInputs(Printers::Board &board, const XMLElement *eBoard)
//{
//	const XMLElement* inputs = eBoard->FirstChildElement(MPRINTER_BOARD_INPUTS_LIST);
//	if (inputs != nullptr) {
//		const XMLElement* input = inputs->FirstChildElement(MPRINTER_BOARD_INPUT);
//		std::vector<Printers::Input> inputsList = board.inputs();
//		while (input != nullptr) {
//			uint32_t id = input->UnsignedAttribute(MPRINTER_BOARD_IO_ID_ATTR);
//			for (auto & in : inputsList){
//				if (in.id() == id) {
//					in.setValue(MTools::boolfromString(input->Attribute(MPRINTER_BOARD_IO_VAL_ATTR)));
//					in.setDescriptor(input->Attribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR));
//				}
//			}
//			input = input->NextSiblingElement(MPRINTER_BOARD_INPUT);
//		}
//		board.setInputs(inputsList);
//	}
//}

//void MPrinter::parseOutputs(Printers::Board &board, const XMLElement *eBoard)
//{
//	const XMLElement* outputs = eBoard->FirstChildElement(MPRINTER_BOARD_OUTPUTS_LIST);
//	if (outputs != nullptr) {
//		const XMLElement* output = outputs->FirstChildElement(MPRINTER_BOARD_OUTPUT);
//		std::vector<Printers::Output> outputsList = board.outputs();
//		while (output != nullptr) {
//			uint32_t id = output->UnsignedAttribute(MPRINTER_BOARD_IO_ID_ATTR);
//			for (auto & in : outputsList){
//				if (in.id() == id) {
//					in.setValue(MTools::boolfromString(output->Attribute(MPRINTER_BOARD_IO_VAL_ATTR)));
//					in.setDescriptor(output->Attribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR));
//				}
//			}
//			output = output->NextSiblingElement(MPRINTER_BOARD_OUTPUT);
//		}
//		board.setOutputs(outputsList);
//	}
//}
