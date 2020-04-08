#include "jetprotocol/jetoutput.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;
using namespace tinyxml2;


JetSetOutput::JetSetOutput(JetPrinter &printer) :
	JetCommand(CMD_SET_OUTPUT, printer) ,
	_output(nullptr)
{}

JetSetOutput::JetSetOutput(JetPrinter &printer, const JetIO &output) :
	JetCommand(CMD_SET_OUTPUT, printer) ,
	_output(new JetIO(output))
{}

JetSetOutput::~JetSetOutput()
{}

bool JetSetOutput::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid){

//		_outputId = getTextAttribute(xml, UPPERCASE_ID_ATTRIBUTE, _outputId);
//		_value = getBoolAttribute(xml, VALUE_ATTRIBUTE, _value);
//		_pulse = xml->UnsignedAttribute(PULSE_ATTRIBUTE, _pulse);
	}
	return valid;
}

bool JetSetOutput::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid){
		parseCommandError(xml);
	}
	return valid;
}

void JetSetOutput::buildRequest()
{
	/*XMLElement * cmd =*/ newCommandWind();
//	cmd->SetAttribute(UPPERCASE_ID_ATTRIBUTE, _outputId.c_str());
//	cmd->SetAttribute(VALUE_ATTRIBUTE, toString(_value).c_str());
//	cmd->SetAttribute(PULSE_ATTRIBUTE, toString(_pulse).c_str());
}

void JetSetOutput::buildResponse()
{
	newCommandWind();
	setCommandError(COMMAND_OK);
}
