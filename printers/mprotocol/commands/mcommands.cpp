#include "mprotocol/mcommands.h"
#include "mtools.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Macsa;
using namespace Macsa::MProtocol;
using namespace tinyxml2;

static int32_t seed = -1;

MCommand::MCommand(const std::string& commandName, Printers::Printer &printer):
	_printer(printer),
	_commandName(commandName)
{
}

MCommand::~MCommand()
{}

std::string MCommand::getRequest(uint32_t windId)
{
	_id = windId;
	buildRequest();
	return toString();
}

std::string MCommand::getResponse()
{
	buildResponse();
	return toString();
}

std::string MCommand::toString()
{
	XMLPrinter p;
	_doc.Print(&p);
	return p.CStr();
}

XMLElement *MCommand::buildNewFrame()
{
	if (_doc.RootElement() != nullptr) {
		_doc.Clear();
	}
	XMLElement* wind = _doc.NewElement(MWIND);
	int id = static_cast<int>(_id);
	wind->SetAttribute(MWIND_ID_ATTR, id);
	_doc.InsertEndChild(wind);
	return _doc.RootElement();
}

bool MCommand::parseSingleCommand(const XMLElement *root)
{
	bool parsed = false;
	int id  = MTools::XML::getWindId(root);
	if(id != -1) {
		if (MTools::XML::isSingleCommand(root, _commandName.c_str())){
			_id = static_cast<uint32_t>(id);
			parsed = true;
		}
	}
	return parsed;
}

uint32_t MCommand::nextId() const
{
	if(++seed < 0){seed = 0;}
	return static_cast<uint32_t>(seed);
}
