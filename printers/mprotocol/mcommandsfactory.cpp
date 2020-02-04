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

MCommandsFactory::MCommandsFactory(Printers::TIJPrinter &printer, LiveFlags &liveFlags) :
	_printer(printer),
	_liveFlags(liveFlags)
{
	_requestId = -1;
	_doc.Clear();
}

MCommandsFactory::~MCommandsFactory()
{
	_doc.Clear();
}

bool MCommandsFactory::parseResponse(const std::string &frame, Printers::ErrorCode &error)
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
			XMLElement* eError = wind->FirstChildElement();
			if (eError) {
				XMLElement* eCmd = eError->NextSiblingElement();
				MCommand* cmd = getCommand(eCmd);
				if (cmd != nullptr){
					std::cout << frame << std::endl;
					valid = cmd->parseResponse(wind);
					error = cmd->getError();
					delete cmd;
				}
			}
		}
	}

	return valid;
}

bool MCommandsFactory::parseRequest(const std::string &frame, Macsa::MProtocol::MCommand** cmd)
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
			XMLElement* eCmd = wind->FirstChildElement();
			*cmd = getCommand(eCmd);
			if (cmd != nullptr){
				valid = (*cmd)->parseRequest(wind);
			}
		}
	}

	return valid;
}

MCommand *MCommandsFactory::getLiveCommand()
{
	return new MLive(_printer, _liveFlags);
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

MCommand *MCommandsFactory::getCommand(XMLElement *eCmd)
{
	MCommand * cmd = nullptr;
	if (eCmd != nullptr) {
		std::string cmdName = eCmd->Name();

		if (cmdName.compare(MLIVE) == 0) {
			cmd = new MLive(_printer, _liveFlags);
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
		else if (cmdName.compare(MFILES_COPY)) {
			cmd = new MCopyFile(_printer);
		}
		else if (cmdName.compare(MFILES_MOVE)) {
			cmd = new MMoveFile(_printer);
		}
		else if (cmdName.compare(MFILES_DELETE)) {
			cmd = new MDeleteFile(_printer);
		}
		else if (cmdName.compare(MFILES_GET)) {
			cmd = new MGetFile(_printer);
		}
		else if (cmdName.compare(MFILES_SET)) {
			cmd = new MGetFile(_printer);
		}
		else if (cmdName.compare(MUPDATE) == 0) {
			cmd = new MUpdate(_printer);
		}
	}

	return cmd;
}

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
