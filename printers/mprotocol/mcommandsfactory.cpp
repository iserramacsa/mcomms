#include "mprotocol/mcommandsfactory.h"
#include "mprotocol/mprotocol.h"
#include "mprotocol/mfiles.h"
#include "mprotocol/mconfig.h"
#include "mprotocol/mlive.h"
#include "mprotocol/mstatus.h"
#include "mprotocol/mmessagevalues.h"
#include "mprotocol/mupdate.h"
#include <iostream>

using namespace tinyxml2;
using namespace Macsa::MProtocol;

MCommandsFactory::MCommandsFactory(Printers::TIJPrinter &printer) :
	_printer(printer)
{
	_requestId = -1;
	_doc.Clear();
}

MCommandsFactory::~MCommandsFactory()
{
	_doc.Clear();
}

bool MCommandsFactory::parse(const std::string &frame, Printers::ErrorCode &error)
{
	bool valid = false;

	if (_doc.FirstChild() != nullptr) 	{
		_doc.Clear();
	}

	if (frame.length())
	{
		_doc.Parse(frame.c_str());

		XMLElement* wind = _doc.FirstChildElement();
		if(isWindValid(wind)) {
			MCommand* cmd = getCommand(wind);
			if (cmd != nullptr){
				valid = cmd->parseResponse(wind);
				error = cmd->getError();
				delete cmd;
			}
		}
	}

	return valid;
}

MCommand *MCommandsFactory::getLiveCommand()
{
	return new MLive(_printer);
}

MCommand *MCommandsFactory::getStatusCommand()
{
	return  new MGetStatus(_printer);
}

MCommand *MCommandsFactory::getConfigCommand()
{
	return new MGetConfig(_printer);
}

MCommand *MCommandsFactory::setDateTimeCommand()
{
	return new MSetDateTime(_printer);
}

MCommand *MCommandsFactory::getFontsCommand()
{
	return new MGetFilesList(_printer, FONTS_FILTER);
}

MCommand *MCommandsFactory::getMessagesCommand()
{
	return new MGetFilesList(_printer, MESSAGES_FILTER);
}

MCommand *MCommandsFactory::getImagesCommand()
{
	return new MGetFilesList(_printer, IMG_FILTER);
}

MCommand *MCommandsFactory::getAllFilesCommand()
{
	return new MGetFilesList(_printer, ALL_FILES_FILTER);
}

MCommand *MCommandsFactory::getCommand(XMLElement *wind) const
{
	MCommand * cmd = nullptr;
	XMLElement* eCmd = wind->FirstChildElement()->NextSiblingElement();
	if (eCmd != nullptr) {
		std::string cmdName = eCmd->Name();

		if (cmdName.compare(MLIVE) == 0) {
			cmd = new MLive(_printer);
		}
		else if (cmdName.compare(MSTATUS) == 0){
			cmd = new MGetStatus(_printer);
		}
		else if (cmdName.compare(MCONFIG_GET) == 0) {
			cmd = new MGetConfig(_printer);
		}
		else if (cmdName.compare(MCONFIG_SET) == 0) {
			cmd = new MSetConfig(_printer);
		}
		else if (cmdName.compare(MFILES_GET_LIST) == 0) {
			cmd = new MGetFilesList(_printer);
		}
		else if (cmdName.compare(MUPDATE) == 0) {
			cmd = new MUpdate(_printer);
		}
	}

	return cmd;
}


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

bool MCommandsFactory::isWindValid(XMLElement *wind) const
{
	bool valid = false;
	if (wind != nullptr) {
		valid = (isElement(wind, MWIND) && wind->FirstChildElement() != nullptr);
	}
	return valid;
}
