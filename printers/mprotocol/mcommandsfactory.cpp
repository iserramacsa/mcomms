#include "mprotocol/mcommandsfactory.h"
#include "mprotocol/mfiles.h"
#include "mprotocol/mconfig.h"
#include "mprotocol/mlive.h"
#include "mprotocol/mstatus.h"
//#include "commands/mupdate.h"
#include <iostream>

using namespace tinyxml2;
using namespace Macsa::MProtocol;

MCommandsFactory::MCommandsFactory(Printers::Printer& printer) :
	_printer(printer)
{
	_doc.Clear();
}

MCommandsFactory::~MCommandsFactory()
{
	_doc.Clear();
}

//bool MCommandsFactory::parse(const std::string &frame)
//{
//	bool valid = false;

//	if (_doc.FirstChild() != nullptr)
//	{
//		_doc.Clear();
//	}

//	if (frame.length())
//	{
//		_doc.Parse(frame.c_str());

//		XMLElement* pWind = _doc.FirstChildElement();
//		valid = isWindValid(pWind);
//	}

//	return valid;
//}

//bool MCommandsFactory::parse(const std::string &frame, MCommand *handler)
//{
//	bool success = false;
//	if(parse(frame)) {
//		XMLElement* pWind = _doc.FirstChildElement();
//		success = handler->parseResponse(pWind);
//	}

//	return success;
//}

// ////////////////////////////////////////////
// CLIENT METHODS  //TODO: Refactorize
//MCommand *MCommandsFactory::getConfigCommand()
//{
//	MGetConfig* cmd = new Client::MGetConfig(_printer);
//	return cmd;
//}

//MCommand *MCommandsFactory::getFontsCommand()
//{
//	MGetFilesList* cmd = new Client::MGetFilesList(_printer);
//	cmd->setFilter(FONTS_FILTER);
//	return cmd;
//}

//MCommand *MCommandsFactory::getMessagesCommand()
//{
//	MGetFilesList* cmd = new Client::MGetFilesList(_printer);
//	cmd->setFilter(NISX_FILTER);
//	return cmd;
//}

//MCommand *MCommandsFactory::getImagesCommand()
//{
//	MGetFilesList* cmd = new Client::MGetFilesList(_printer);
//	cmd->setFilter(IMG_FILTER);
//	return cmd;
//}

//MCommand *MCommandsFactory::getAllFilesCommand()
//{
//	MGetFilesList* cmd = new Client::MGetFilesList(_printer);
//	cmd->setFilter(NO_FILTER);
//	return cmd;
//}

//MCommand *MCommandsFactory::getLiveCommand()
//{
//	return  new Macsa::MProtocol::MLive(_printer);
//}

//MCommand *MCommandsFactory::getStatusCommand()
//{
//	return  new Macsa::MProtocol::MGetStatus(_printer);
//}
// END OF CLIENT METHODS  //TODO: Refactorize
// ////////////////////////////////////////////

// ////////////////////////////////////////////
// SERVER METHODS  //TODO: Refactorize
//std::string MCommandsFactory::getResponse()
//{
//	std::string response = "";
//	XMLElement* pWind = _doc.FirstChildElement();
//	while (pWind != nullptr)
//	{
//		/* *** Debug *** */
//		XMLPrinter p;
//		_doc.Print(&p);
////		std::cout << "RX:" << std::endl <<  p.CStr() << std::endl;
//		/* *** Debug *** */

//		response += getCommandResponse(pWind);
//		pWind = pWind->NextSiblingElement(MWIND);
//	}

//	/* *** Debug *** */
////	std::cout << "TX:" << std::endl << response << std::endl;
//	/* *** Debug *** */

//	return response;
//}
// END OF SERVER METHODS  //TODO: Refactorize
// ////////////////////////////////////////////

//std::string MCommandsFactory::getCommandResponse(XMLElement *wind)
//{
//	std::string response = "";
//	if (isWindValid(wind)) {
//		XMLElement* pCmd = wind->FirstChildElement();
//		if (isElement(pCmd, MLIVE))
//		{
//			Macsa::MProtocol::MLive cmd(_printer);
//			if(cmd.parseRequest(wind)){
//				response = cmd.getResponse();
//			}
//		}
//		else if (isElement(pCmd, MSTATUS))
//		{
//			Macsa::MProtocol::Client::MGetStatus cmd(_printer);
//			if(cmd.parse(wind)){
//				response = cmd.toString();
//			}
//		}
//		else if (isElement(pCmd, MCONFIG_GET))
//		{
//			Macsa::MProtocol::Client::MGetConfig cmd(_printer);
//			if(cmd.parse(wind)){
//				response = cmd.toString();
//			}
//		}
//		else if (isElement(pCmd, MFILES_GET_LIST))
//		{
//			Macsa::MProtocol::Client::MGetFilesList cmd(_printer);
//			if(cmd.parse(wind)){
//				response = cmd.toString();
//			}
//		}
////		else if (isElement(pCmd, MUPDATE))
////		{
////			MProtocol::MUpdate cmd(_printer);
////			if(cmd.parse(wind)){
////				response = cmd.toString();
////			}
////		}
//	}
//	return response;
//}

bool MCommandsFactory::isElement(const XMLElement *wind, const std::string &name) const
{
	std::string elementName = wind->Value();
	return (elementName.compare(name) == 0);
}

bool MCommandsFactory::isWindValid(XMLElement *wind)
{
	bool valid = false;
	if (wind != nullptr) {
		valid = (isElement(wind, MWIND) && wind->FirstChildElement() != nullptr);
	}
	return valid;
}
