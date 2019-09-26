#include "mprotocol/mconfig.h"
#include "mtools.h"
#include "xmlboard.h"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MGetConfig::MGetConfig(Printers::Printer &printer):
	MCommandBase(printer)
{}

std::string MGetConfig::commandName() const
{
	return MCONFIG_GET;
}

#if defined (MSERVER)
void MGetConfig::build()
{
	XMLElement *cmd = _doc.NewElement(MCONFIG_GET);
	cmd->InsertEndChild(getPrinterGenerals());
	//	config.InsertEndChild(getPrinterConnections());
	cmd->InsertEndChild(getPrinterBoards());
	setWind(&cmd);
}

bool MGetConfig::parse(const XMLElement * root)
{
	return isNoChildrenSingleNode(root, MCONFIG_GET);
}
#endif

XMLElement * MGetConfig::getPrinterGenerals()
{
	XMLElement *general = _doc.NewElement(MCONFIG_GENERAL);
	general->InsertEndChild(textElement(MCONFIG_GENERAL_DT, dateTime()));

	XMLElement *log = _doc.NewElement(MCONFIG_GENERAL_LOG);
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

XMLElement * MGetConfig::getPrinterConnections()
{
	XMLElement *connections = _doc.NewElement(MCONFIG_CONNECTIONS);
	//TODO: Fill with network connections

	return connections;
}

XMLElement * MGetConfig::getPrinterBoards()
{
	XMLElement* boards = _doc.NewElement(MPRINTER_BOARDS_LIST);
	XMLElement* board = _doc.NewElement(MPRINTER_BOARD);
	board->SetAttribute(MPRINTER_BOARD_ID_ATTR, _printer.id());

	board->InsertEndChild(textElement(MPRINTER_BOARD_TYPE,			_printer.type()));
	board->InsertEndChild(textElement(MPRINTER_BOARD_AUTOSTART,		MTools::toString(false))); //TODO: Add printer management
	board->InsertEndChild(textElement(MPRINTER_BOARD_ENABLED,		MTools::toString(false))); //TODO: Add printer management
//	board->InsertEndChild(textElement(MPRINTER_BOARD_CURRENT_MSG,	_printer.currentMessage())); //TODO: Add printer management

	/* ****************************************	*/
	/*	 TODO (Fill with all printer config)	*/
	/* ****************************************	*/


	boards->InsertEndChild(board);
	return boards;

}
#if defined (MCLIENT)
void MGetConfig::build()
{
	XMLElement* cmd = _doc.NewElement(MCONFIG_GET);
	setWind(&cmd);
}

bool MGetConfig::parse(const XMLElement * wind)
{
	const XMLElement * pwind = getWindNode(wind);
	bool valid = (pwind != nullptr);
	if (valid) {
		const XMLElement * cmd = pwind->FirstChildElement(MCONFIG_GET);
		if ((MCommandBase::valid(pwind) && cmd != nullptr))
		{

		}
	}
	return valid;
}
#endif

/* ===================================================================*/

MSetConfig::MSetConfig(Printers::Printer &printer):
	MCommandBase(printer)
{}

std::string MSetConfig::commandName() const
{
	return MCONFIG_SET;
}

bool MSetConfig::parse(const XMLElement * /*root*/)
{
	return false;
}

void MSetConfig::build()
{
	XMLElement *cmd = _doc.NewElement(MCONFIG_SET);
	//TODO: fill setConfig response
	cmd->InsertEndChild(boardConnectionsToXml(_printer.comms(), _doc));

	setWind(&cmd);
}

MSetDateTime::MSetDateTime(Macsa::Printers::Printer &printer):
	MSetConfig(printer)
{}

void MSetDateTime::build()
{
	XMLElement *cmd = _doc.NewElement(MCONFIG_SET);
	//TODO: fill setConfig response
	setWind(&cmd);
}
