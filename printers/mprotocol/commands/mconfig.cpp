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
			while (xBoard != nullptr){
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
			while (xBoard != nullptr){
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
		createTextChildNode(MCONFIG_GENERAL_DT, _printer.formatedDateTime(), &cmd);
	}
}
