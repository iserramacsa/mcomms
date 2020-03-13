#include "jetprotocol/jetcommandsfactory.h"
#include "jetprotocol/jetprotocol.h"
#include "jetprotocol/jetfiles.h"
#include "jetprotocol/jetconfig.h"
#include "jetprotocol/jetstatus.h"
#include "jetprotocol/jetlogs.h"
#include "jetprotocol/jetmessagevalues.h"
#include "jetprotocol/jetmessages.h"
#include "jetprotocol/jetcounters.h"

using namespace tinyxml2;
using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;

#define CLOSE_WIND "</" JETWIND ">"

JetCommandsFactory::JetCommandsFactory(JetPrinter &printer) :
	_printer(printer)
{
	_doc.Clear();
}

JetCommandsFactory::~JetCommandsFactory()
{
	_doc.Clear();
}

bool JetCommandsFactory::parseResponse(const std::string &rx, JetCommand * cmd)
{
	bool valid = false;

	if (_doc.FirstChild() != nullptr) 	{
		_doc.Clear();
	}

	if (rx.length())
	{
		size_t close = rx.find(CLOSE_WIND);
		if (close != rx.npos) {
			close += sizeof (CLOSE_WIND);
		}
		std::string frame = rx.substr(0, close);

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

bool JetCommandsFactory::parseRequest(const std::string &frame, JetCommand** cmd)
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


