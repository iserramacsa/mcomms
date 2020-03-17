#include "jetprotocol/jetoutput.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;
using namespace tinyxml2;


JetSetOutput::JetSetOutput(JetPrinter &printer, const std::string & outputId, bool value, unsigned int pulse) :
	JetCommand(CMD_SET_OUTPUT, printer)
{
	_outputId = outputId;
	_value = value;
	_pulse = pulse;
}

JetSetOutput::~JetSetOutput()
{}

bool JetSetOutput::parseRequest(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid){
		const XMLAttribute* eValue = xml->FindAttribute(VALUE_ATTRIBUTE);
		if (eValue != nullptr) {
			_value = strToBool(eValue->Value());
		}
		const XMLAttribute* ePulse = xml->FindAttribute(PULSE_ATTRIBUTE);
		if (ePulse != nullptr) {
			_pulse = static_cast<unsigned int>(::atoi(eValue->Value()));
		}
		const XMLAttribute* eOutputId = xml->FindAttribute(IO_ID_ATTRIBUTE);
		if (eOutputId != nullptr) {
			_outputId = eOutputId->Value();
		}
	}
	return valid;
}

bool JetSetOutput::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if(valid){
		parseCommandError();
	}
	return valid;
}

void JetSetOutput::buildRequest()
{
	XMLElement * cmd = newCommandWind();
	cmd->SetAttribute(IO_ID_ATTRIBUTE, _outputId.c_str());
	cmd->SetAttribute(VALUE_ATTRIBUTE, toString(_value).c_str());
	cmd->SetAttribute(PULSE_ATTRIBUTE, toString(_pulse).c_str());
}

void JetSetOutput::buildResponse()
{
	newCommandWind();
	setCommandError(COMMAND_OK);
}
