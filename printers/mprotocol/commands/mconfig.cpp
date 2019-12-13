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

bool MSetConfig::parseRequest(const XMLElement *xml)
{
	return false;
}

bool MSetConfig::parseResponse(const XMLElement *xml)
{
	return false;
}

void MSetConfig::buildRequest()
{
	XMLElement* cmd = newCommandNode();

}

void MSetConfig::buildResponse()
{

}

//######################################################
//	SETCONFIG (set date and time)
//######################################################
MSetDateTime::MSetDateTime(Macsa::Printers::TIJPrinter &printer):
	MSetConfig(printer)
{}

bool MSetDateTime::parseRequest(const XMLElement *xml)
{
	return false; //todo
}

void MSetDateTime::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	//TODO
}


//XMLElement * MGetConfig::getPrinterConnections()
//{
//	XMLElement *connections = _doc.NewElement(MCONFIG_CONNECTIONS);
//	//TODO: Fill with network connections

//	return connections;
//}

//XMLElement * MGetConfig::getPrinterBoards()
//{
////	board->InsertEndChild(textElement(MPRINTER_BOARD_CURRENT_MSG,	_printer.currentMessage())); //TODO: Add printer management

//	/* ****************************************	*/
//	/*	 TODO (Fill with all printer config)	*/
//	/* ****************************************	*/


//	boards->InsertEndChild(board);
//	return boards;

//}

//MSetConfig::MSetConfig(Printers::Printer &printer, bool request):
//	MCommandBase(printer, request)
//{}

//std::string MSetConfig::commandName() const
//{
//	return MCONFIG_SET;
//}

//// ////////////////////////////////////////////
//// Server Commands
//// ////////////////////////////////////////////
//Server::MGetConfig::MGetConfig(Macsa::Printers::Printer &printer) :
//	Macsa::MProtocol::MGetConfig(printer, false)
//{}

//void Server::MGetConfig::build()
//{
//	XMLElement *cmd = _doc.NewElement(MCONFIG_GET);
//	cmd->InsertEndChild(getPrinterGenerals());
//	//	config.InsertEndChild(getPrinterConnections());
//	cmd->InsertEndChild(getPrinterBoards());
//	setWind(&cmd);
//}


//bool Server::MGetConfig::parse(const XMLElement * root)
//{
//	return noChildrenSingleNode(root, MCONFIG_GET);
//}

//// ////////////////////////////////////////////
//// Client Commands
//// ////////////////////////////////////////////
//Client::MGetConfig::MGetConfig(Macsa::Printers::Printer &printer) :
//	Macsa::MProtocol::MGetConfig(printer, true)
//{}

//void Client::MGetConfig::build()
//{
//	XMLElement* cmd = _doc.NewElement(MCONFIG_GET);
//	setWind(&cmd);
//}

//bool Client::MGetConfig::parse(const XMLElement * wind)
//{
//	const XMLElement * pwind = getWindNode(wind, true);
//	bool valid = (pwind != nullptr);
//	if (valid) {
//		const XMLElement * cmd = pwind->FirstChildElement(MCONFIG_GET);
//		if ((MCommandBase::valid(pwind) && cmd != nullptr))
//		{

//		}
//	}
//	return valid;
//}

//bool Client::MSetConfig::parse(const XMLElement * root)
//{
//	return noChildrenSingleNodeResponse(root, MCONFIG_SET);
//}

//void Client::MSetConfig::build()
//{
//	XMLElement *cmd = _doc.NewElement(MCONFIG_SET);
//	//TODO: fill setConfig response
//	cmd->InsertEndChild(MBoard::boardConnectionsToXml(_printer.comms(), _doc));

//	setWind(&cmd);
//}


//void Client::MSetDateTime::build()
//{
//	XMLElement *cmd = _doc.NewElement(MCONFIG_SET);
//	//TODO: fill setConfig response
//	setWind(&cmd);
//}

