#include "mprotocol/mconfig.h"
#include "mprotocol/mprotocol.h"

#include "mtools.h"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MGetConfig::MGetConfig(Printers::TIJPrinter &printer):
	MConfigCommand(MCONFIG_GET, printer)
{}

bool MGetConfig::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	return valid;
}

bool MGetConfig::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
		generalConfigFromXml(cmd, _printer);
		Printers::TIJComms * comms = dynamic_cast<Printers::TIJComms *>(_printer.comms());
		if (comms != nullptr) {
			printerConnectionsFromXml(cmd, *comms);
		}
		const XMLElement* xBoards = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
		std::vector<Printers::Board> boards;
		if (xBoards != nullptr) {
			const XMLElement* xBoard = xBoards->FirstChildElement(MPRINTER_BOARD);
			while (xBoard != nullptr) {
				int id = xBoard->IntAttribute(ATTRIBUTE_ID, 0);
				Printers::Board* board = _printer.board(id);
				bool newBoard = (board == nullptr);
				if (newBoard) {
					board = new Printers::Board(id, &_printer);
				}

				boardFromXml(xBoard, *board);

				boards.push_back(*board);
				if (newBoard) {
					delete board;
				}
				xBoard = xBoard->NextSiblingElement(MPRINTER_BOARD);
			}
		}
		_printer.setBoards(boards);
	}
	return valid;
}

void MGetConfig::buildRequest()
{
	newCommandNode();
}


void MGetConfig::buildResponse()
{
	XMLElement* cmd = newCommandNode();

	generalConfigToXml(_printer, &cmd);
	printerConnectionsToXml(dynamic_cast<const Printers::TIJComms *>(_printer.comms()), &cmd);
	XMLElement* xBoards = createChildNode(MPRINTER_BOARDS_LIST, &cmd);
	if (xBoards) {
		std::vector<Printers::Board> boards = _printer.boards();
		for (std::vector<Printers::Board>::const_iterator board = boards.begin(); board != boards.end(); board++) {
			boardToXml(*board, &xBoards);
		}
	}

	addWindError(_error);
}

//######################################################
//	SETCONFIG
//######################################################
MSetConfig::MSetConfig(Macsa::Printers::TIJPrinter &printer):
	MConfigCommand(MCONFIG_GET, printer)
{}

void MSetConfig::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	generalConfigToXml(_printer, &cmd);
	Printers::TIJComms * comms = dynamic_cast<Printers::TIJComms *>(_printer.comms());
	if (comms != nullptr) {
		printerConnectionsToXml(comms, &cmd);
	}
	XMLElement* xBoards = createChildNode(MPRINTER_BOARDS_LIST, &cmd);
	if (xBoards) {
		std::vector<Printers::Board> boards = _printer.boards();
		for (std::vector<Printers::Board>::const_iterator board = boards.begin(); board != boards.end(); board++) {
			boardToXml(*board, &xBoards);
		}
	}
}

bool MSetConfig::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
		generalConfigFromXml(cmd, _printer);
		Printers::TIJComms * comms = dynamic_cast<Printers::TIJComms *>(_printer.comms());
		if (comms != nullptr) {
			printerConnectionsFromXml(cmd, *comms);
		}
		const XMLElement* xBoards = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
		std::vector<Printers::Board> boards;
		if (xBoards != nullptr) {
			const XMLElement* xBoard = cmd->FirstChildElement(MPRINTER_BOARD);
			while (xBoard != nullptr) {
				int id = xBoard->IntAttribute(ATTRIBUTE_ID, 0);
				Printers::Board* board = _printer.board(id);
				bool newBoard = (board == nullptr);
				if (newBoard) {
					board = new Printers::Board(id, &_printer);
				}

				boardFromXml(xBoard, *board);

				boards.push_back(*board);
				if (newBoard) {
					delete board;
				}
			}
		}
		_printer.setBoards(boards);
	}
	return valid;
}

void MSetConfig::buildResponse()
{
	newCommandNode();
	addWindError(_error);
}

bool MSetConfig::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	if  (valid) {
		_error = getCommandError(xml);
	}
	return valid;
}

//######################################################
//	SETCONFIG (set date and time)
//######################################################
MSetDateTime::MSetDateTime(Macsa::Printers::TIJPrinter &printer):
	MSetConfig(printer)
{}

void MSetDateTime::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	XMLElement * xGeneral = createChildNode(MCONFIG_GENERAL, &cmd);
	if(xGeneral != nullptr) {
		createTextChildNode(MCONFIG_GENERAL_DT, _printer.formatedDateTime(), &xGeneral);
	}
}
//TODO
MUpdateConfig::MUpdateConfig(Macsa::Printers::TIJPrinter &baseConfig, Macsa::Printers::TIJPrinter &newConfig):
	MSetConfig(baseConfig),
	_newConfig(newConfig)
{}

void MUpdateConfig::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	updateGeneralConfig(&cmd);
	updateCommsConfig(&cmd);
	updateBoards(&cmd);
}

void MUpdateConfig::updateGeneralConfig(XMLElement **parent)
{
	XMLElement * xGeneral = nullptr;
	if (_printer.dateTime() != _newConfig.dateTime()) {
		xGeneral = createChildNode(MCONFIG_GENERAL, parent);
		if(xGeneral != nullptr) {
			datetimeToXml(_newConfig, &xGeneral);
		}
	}
	if (_printer.loggerLevel() != _newConfig.loggerLevel() ||
		_printer.logsEnabled() != _newConfig.logsEnabled() ||
		_printer.logComsEnabled() != _newConfig.logComsEnabled() )
	{
		xGeneral = createChildNode(MCONFIG_GENERAL, parent);
		if(xGeneral != nullptr) {
			loggerToXml(_newConfig, &xGeneral);
		}
	}
}

void MUpdateConfig::updateCommsConfig(XMLElement ** parent)
{
	Printers::TIJComms * comms = dynamic_cast<Printers::TIJComms *>(_printer.comms());
	Printers::TIJComms * newcomms = dynamic_cast<Printers::TIJComms *>(_newConfig.comms());
	if (comms != nullptr && newcomms != nullptr && ((*comms) != (*newcomms))) {
		printerConnectionsToXml(newcomms,  parent);
	}
}

void MUpdateConfig::updateBoards(XMLElement **parent)
{
	for (int b = 0; b < static_cast<int>(_newConfig.boards().size()); b++) {
		const Printers::Board *oldBoard = _printer.board(b);
		const Printers::Board *newBoard = _newConfig.board(b);
		if ((newBoard != nullptr) && (oldBoard != nullptr) && *oldBoard != *newBoard)
		{
			const Printers::Board& oBoard = *oldBoard;
			const Printers::Board& nBoard = *newBoard;
			XMLElement * xBoards = createChildNode(MPRINTER_BOARDS_LIST, parent);
			if(xBoards != nullptr) {
				XMLElement * xBoard = createChildNode(MPRINTER_BOARD, &xBoards);
				if (xBoard != nullptr) {
					xBoard->SetAttribute(ATTRIBUTE_ID, nBoard.id());
					if (oBoard.type() != nBoard.type()) {
						boardTypeToXml(nBoard.type(), &xBoard);
					}
					if (oBoard.autoStart() != nBoard.autoStart()) {
						autostartToXml(nBoard.autoStart(), &xBoard);
					}
					if (oBoard.lowLevelOutput() != nBoard.lowLevelOutput()) {
						lowLevelOutputToXml(nBoard.lowLevelOutput(), &xBoard);
					}
					if (oBoard.enabled() != nBoard.enabled()) {
						enabledToXml(nBoard.enabled(), &xBoard);
					}
					if (oBoard.blocked() != nBoard.blocked()) {
						blockToXml(nBoard.blocked(), &xBoard);
					}
					if (oBoard.userMessage().compare(nBoard.userMessage()) != 0) {
						userMessageToXml(nBoard.userMessage(), &xBoard);
					}
					if (oBoard.bcdMode() != nBoard.bcdMode() || oBoard.bcdTable() != nBoard.bcdTable()) {
						bcdToXml(nBoard.bcdMode(), nBoard.bcdTable(), &xBoard);
					}
					if (oBoard.printDirection() != nBoard.printDirection()) {
						printDirectionToXml(nBoard.printDirection(), &xBoard);
					}
					if (oBoard.printRotated() != nBoard.printRotated()) {
						printInvertedToXml(nBoard.printRotated(), &xBoard);
					}
					if (oBoard.nozzlesCol() != nBoard.nozzlesCol()) {
						nozzlesToXml(nBoard.nozzlesCol(), &xBoard);
					}
					if (oBoard.shotMode() != nBoard.shotMode()) {
						shotModeToXml(nBoard.shotMode(), &xBoard);
					}
					if (oBoard.encoder() != nBoard.encoder()) {
						encoderToXml(nBoard.encoder(), &xBoard);
					}
					if (oBoard.photocell() != nBoard.photocell()) {
						photocellToXml(nBoard.photocell(), &xBoard);
					}
					if (oBoard.properties() != nBoard.properties()) {
						propertiesToXml(nBoard.properties(), &xBoard);
					}
					if (oBoard.cartridge() != nBoard.cartridge()) {
						cartridgeToXml(nBoard.cartridge(), &xBoard);
					}
					if (oBoard.inputs() != nBoard.inputs()) {
						inputsToXml(nBoard.inputs(), &xBoard);
					}
					if (oBoard.outputs() != nBoard.outputs()) {
						outputsToXml(nBoard.outputs(), &xBoard);
					}
					if (nBoard.printer() != nullptr) {
						if (oBoard.printer() == nullptr || nBoard.printer()->dateCodes() != oBoard.printer()->dateCodes() ) {
							dateCodesToXml(nBoard.printer()->dateCodes(), &xBoard);
						}
					}
				}
			}
		}
	}
}
