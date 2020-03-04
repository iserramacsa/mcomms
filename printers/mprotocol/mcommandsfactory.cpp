#include "mprotocol/mcommandsfactory.h"
#include "mprotocol/mprotocol.h"
#include "mprotocol/mfiles.h"
#include "mprotocol/mconfig.h"
#include "mprotocol/mlive.h"
#include "mprotocol/mstatus.h"
#include "mprotocol/merrorslogs.h"
#include "mprotocol/mmessagevalues.h"
#include "mprotocol/mupdate.h"

using namespace tinyxml2;
using namespace Macsa::MProtocol;

MCommandsFactory::MCommandsFactory(Printers::TijPrinter &printer, LiveFlags &liveFlags) :
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

bool MCommandsFactory::parseResponse(const std::string &frame, MCommand * cmd)
{
	bool valid = false;

	if (_doc.FirstChild() != nullptr) 	{
		_doc.Clear();
	}

	if (frame.length())
	{
		_doc.Parse(frame.c_str());
		XMLElement* wind = _doc.FirstChildElement();
		if(isWindValid(wind))
		{
			XMLElement* eError = wind->FirstChildElement();
			if (eError)
			{
				XMLElement* eCmd = eError->NextSiblingElement();
				if (eCmd->Name() != nullptr && (cmd->commandName().compare(eCmd->Name()) == 0))
				{
					valid = cmd->parseResponse(wind);
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

// ==============  LIVE Commands  ============== //
MCommand *MCommandsFactory::getLiveCommand()
{
	return new MLive(_printer, _liveFlags);
}

// =============  STATUS Commands  ============= //
MCommand *MCommandsFactory::getStatusCommand()
{
	return  new MGetStatus(_printer);
}

MCommand *MCommandsFactory::getIOStatusCommand()
{
	return new MGetIOStatus(_printer);
}

MCommand *MCommandsFactory::getCurrentErrors()
{
	return new MGetErrors(_printer);
}

// =============  CONFIG Commands  ============= //
MCommand *MCommandsFactory::getConfigCommand()
{
	return new MGetConfig(_printer);
}

MCommand *MCommandsFactory::setDateTimeCommand(time_t dateTime)
{
	Macsa::Printers::TijPrinter printer = _printer;
	printer.setDateTime(dateTime);
	return new MSetDateTime(printer);
}

MCommand *MCommandsFactory::setConfigBoard(const Macsa::Printers::Board &board)
{
	if (_printer.board(board.id()) != nullptr)
	{
		Macsa::Printers::TijPrinter printer = _printer;
		printer.setBoard(board);
		return new MUpdateConfig(_printer, printer);
	}

	return nullptr;
}

// =============  FILES Commands  ============= //
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
	return new MGetFilesList(_printer, ALL_FILES);
}

MCommand *MCommandsFactory::getFileContent(const std::string &filePath, bool rawMode)
{
	return new MGetFile(_printer, filePath, rawMode);
}

MCommand *MCommandsFactory::getMsgUserValues(const std::string &filePath)
{
	return new MGetMessageValues(_printer, filePath);
}

MCommand *MCommandsFactory::getMsgDataSources(const std::string &filePath)
{
	return new MGetMessageDataSource(_printer, filePath);
}

// =============  ERROR HISTORY Commands  ============= //
MCommand *MCommandsFactory::getErrorsList()
{
	return new MErrorsLogs(_printer);
}


// =============  Handler  ============= //
MCommand *MCommandsFactory::getCommand(XMLElement *eCmd)
{
	MCommand * cmd = nullptr;
	if (eCmd != nullptr) {
		std::string cmdName = eCmd->Name();

		// ==============  LIVE Commands  ============== //
		if (cmdName == MLIVE) {
			cmd = new MLive(_printer, _liveFlags);
		}
		// =============  STATUS Commands  ============= //
		else if (cmdName == MSTATUS){
			cmd = new MGetStatus(_printer);
		}
		else if (cmdName == MIOSTATUS){
			cmd = new MGetIOStatus(_printer);
		}
		else if (cmdName == MERRORS_GET) {
			cmd = new MGetErrors(_printer);
		}
		// =============  CONFIG Commands  ============= //
		else if (cmdName == MCONFIG_GET) {
			cmd = new MGetConfig(_printer);
		}
		else if (cmdName == MCONFIG_SET) {
			cmd = new MSetConfig(_printer);
		}
		// =============  FILES Commands  ============= //
		else if (cmdName == MFILES_GET_LIST) {
			cmd = new MGetFilesList(_printer);
		}
		else if (cmdName == MFILES_COPY) {
			cmd = new MCopyFile(_printer);
		}
		else if (cmdName == MFILES_MOVE) {
			cmd = new MMoveFile(_printer);
		}
		else if (cmdName == MFILES_DELETE) {
			cmd = new MDeleteFile(_printer);
		}
		else if (cmdName == MFILES_GET) {
			cmd = new MGetFile(_printer);
		}
		else if (cmdName == MFILES_SET) {
			cmd = new MGetFile(_printer);
		}
		else if (cmdName == MMESSAGE_USER_FIELD_GET) {
			cmd = new MGetMessageValues(_printer);
		}
		else if (cmdName == MMESSAGE_USER_FIELD_SET) {
			cmd = new MSetMessageValues(_printer);
		}
		else if (cmdName == MMESSAGE_DATA_SOURCE_GET) {
			cmd = new MGetMessageDataSource(_printer);
		}
		else if (cmdName == MMESSAGE_DATA_SOURCE_SET) {
			cmd = new MSetMessageDataSource(_printer);
		}
		// =============  ERROR HISTORY Commands  ============= //
		else if (cmdName == MERRORS_LOGS) {
			cmd = new MErrorsLogs(_printer);
		}
		// =============  UPDATE Commands  ============= //
		else if (cmdName == MUPDATE) {
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
