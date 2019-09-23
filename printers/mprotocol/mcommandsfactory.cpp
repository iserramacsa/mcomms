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

bool MCommandsFactory::parse(const std::string &frame)
{
	bool valid = false;

	if (_doc.FirstChild() != nullptr)
	{
		_doc.Clear();
	}

	if (frame.length())
	{
		_doc.Parse(frame.c_str());

		XMLElement* pWind = _doc.FirstChildElement();
		valid = isWindValid(pWind);
	}

	return valid;
}

bool MCommandsFactory::parse(const std::string &frame, MCommandBase *handler)
{
	bool success = false;
	if(parse(frame)) {
		XMLElement* pWind = _doc.FirstChildElement();
		success = handler->parse(pWind);
	}

	return success;
}

#if defined (MCLIENT)

MCommandBase *MCommandsFactory::getConfigCommand()
{
	MGetConfig* cmd = new MGetConfig(_printer);
	return cmd;
}

MCommandBase *MCommandsFactory::getFontsCommand()
{
	MGetFilesList* cmd = new MGetFilesList(_printer);
	cmd->setFilter(FONTS_FILTER);
	return cmd;
}

MCommandBase *MCommandsFactory::getMessagesCommand()
{
	MGetFilesList* cmd = new MGetFilesList(_printer);
	cmd->setFilter(NISX_FILTER);
	return cmd;
}

MCommandBase *MCommandsFactory::getImagesCommand()
{
	MGetFilesList* cmd = new MGetFilesList(_printer);
	cmd->setFilter(IMG_FILTER);
	return cmd;
}

MCommandBase *MCommandsFactory::getAllFilesCommand()
{
	MGetFilesList* cmd = new MGetFilesList(_printer);
	cmd->setFilter(NO_FILTER);
	return cmd;
}

MCommandBase *MCommandsFactory::getLiveCommand()
{
	return  new MLive(_printer);
}

MCommandBase *MCommandsFactory::getStatusCommand()
{
	return  new MGetStatus(_printer);
}
#endif
#if defined (MSERVER)
std::string MCommandsFactory::getResponse()
{
	std::string response = "";
	XMLElement* pWind = _doc.FirstChildElement();
	while (pWind != nullptr)
	{
		/* *** Debug *** */
		XMLPrinter p;
		_doc.Print(&p);
//		std::cout << "RX:" << std::endl <<  p.CStr() << std::endl;
		/* *** Debug *** */

		response += getCommandResponse(pWind);
		pWind = pWind->NextSiblingElement(MWIND);
	}

	/* *** Debug *** */
//	std::cout << "TX:" << std::endl << response << std::endl;
	/* *** Debug *** */

	return response;
}
#endif

std::string MCommandsFactory::getCommandResponse(XMLElement *wind)
{
	std::string response = "";
	if (isWindValid(wind)) {
		XMLElement* pCmd = wind->FirstChildElement();
		if (isElement(pCmd, MLIVE))
		{
			Macsa::MProtocol::MLive cmd(_printer);
			if(cmd.parse(wind)){
				response = cmd.toString();
			}
		}
		else if (isElement(pCmd, MSTATUS))
		{
			Macsa::MProtocol::MGetStatus cmd(_printer);
			if(cmd.parse(wind)){
				response = cmd.toString();
			}
		}
		else if (isElement(pCmd, MCONFIG_GET))
		{
			Macsa::MProtocol::MGetConfig cmd(_printer);
			if(cmd.parse(wind)){
				response = cmd.toString();
			}
		}
		else if (isElement(pCmd, MFILES_GET_LIST))
		{
			Macsa::MProtocol::MGetFilesList cmd(_printer);
			if(cmd.parse(wind)){
				response = cmd.toString();
			}
		}
//		else if (isElement(pCmd, MUPDATE))
//		{
//			MProtocol::MUpdate cmd(_printer);
//			if(cmd.parse(wind)){
//				response = cmd.toString();
//			}
//		}
	}
	return response;
}

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
