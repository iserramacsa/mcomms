#include "jetprotocol/jetcounters.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;

//=============		Get Counters		=============//
JetGetCounters::JetGetCounters(JetPrinter &printer) :
	JetCommand(CMD_GET_COUNTERS, printer)
{}

JetGetCounters::~JetGetCounters()
{}

bool JetGetCounters::parseRequest(const tinyxml2::XMLElement *xml)
{
	return false;
}

bool JetGetCounters::parseResponse(const tinyxml2::XMLElement *xml)
{
	return false;
}

void JetGetCounters::buildRequest()
{

}

void JetGetCounters::buildResponse()
{

}

//=============		Set Counters		=============//
JetSetCounters::JetSetCounters(JetPrinter &printer) :
	JetCommand(CMD_SET_COUNTERS, printer)
{}

JetSetCounters::~JetSetCounters()
{}

bool JetSetCounters::parseRequest(const tinyxml2::XMLElement *xml)
{
	return false;
}

bool JetSetCounters::parseResponse(const tinyxml2::XMLElement *xml)
{
	return false;
}

void JetSetCounters::buildRequest()
{

}

void JetSetCounters::buildResponse()
{

}

//=============		Reset Counters		=============//
JetResetCounters::JetResetCounters(JetPrinter &printer) :
	JetCommand(CMD_RESET_COUNTERS, printer)
{}

JetResetCounters::~JetResetCounters()
{}

bool JetResetCounters::parseRequest(const tinyxml2::XMLElement *xml)
{
	return false;
}

bool JetResetCounters::parseResponse(const tinyxml2::XMLElement *xml)
{
	return false;
}

void JetResetCounters::buildRequest()
{

}

void JetResetCounters::buildResponse()
{

}
