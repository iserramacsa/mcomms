#include "mprotocol/mconfig.h"
#include "mtools.h"
#include "mboard.h"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MGetConfig::MGetConfig(Printers::Printer &printer):
	MCommand(MCONFIG_GET, printer)
{}

bool MGetConfig::parseRequest(const XMLElement *xml)
{
	return parseSingleCommand(xml);
}

bool MGetConfig::parseResponse(const XMLElement *xml)
{
	return false;
}

void MGetConfig::buildRequest()
{
	XMLElement* wind = buildNewFrame();
	MTools::XML::newElement(commandName(), _doc, &wind);
}


void MGetConfig::buildResponse()
{
	XMLElement* wind = buildNewFrame();
	_error = Printers::ErrorCode_n::SUCCESS;

	XMLElement* cmd = MTools::XML::newElement(commandName(), _doc, &wind);

	cmd->InsertEndChild(MPrinter::generalConfigToXml(_printer, _doc));
	cmd->InsertEndChild(MPrinter::printerConnectionsToXml(_printer.comms(), _doc));

	XMLElement* eBoards = _doc.NewElement(MPRINTER_BOARDS_LIST);
	for (auto& board : _printer.configuration().boards()) {
		eBoards->InsertEndChild(MPrinter::boardConfigToXml(board, _doc));
	}

	MTools::XML::setWindError(wind, _doc, _error);
}


//######################################################
//	SETCONFIG
//######################################################
MSetConfig::MSetConfig(Macsa::Printers::Printer &printer):
	MCommand(MCONFIG_GET, printer)
{}

bool MSetConfig::parseRequest(const XMLElement *xml)
{

}

bool MSetConfig::parseResponse(const XMLElement *xml)
{

}

void MSetConfig::buildRequest()
{
	XMLElement* wind = buildNewFrame();
	MTools::XML::newElement(commandName(), _doc, &wind);
}

void MSetConfig::buildResponse()
{

}

//######################################################
//	SETCONFIG (set date and time)
//######################################################
MSetDateTime::MSetDateTime(Macsa::Printers::Printer &printer):
	MSetConfig(printer)
{}

bool MSetDateTime::parseRequest(const XMLElement *xml)
{
	return false; //todo
}

void MSetDateTime::buildRequest()
{
	XMLElement* wind = buildNewFrame();
	XMLElement* cmd = MTools::XML::newElement(commandName(), _doc, &wind);
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
