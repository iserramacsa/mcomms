#include "mprotocol/mstatus.h"
#include "mboard.h"
#include "mtools.h"
using namespace Macsa::MProtocol;
using namespace tinyxml2;

MGetStatus::MGetStatus(Printers::TIJPrinter &printer):
	MCommand(MSTATUS, printer)
{}

bool MGetStatus::parseRequest(const XMLElement *xml)
{
	return parseSingleCommand(xml);
}

bool MGetStatus::parseResponse(const XMLElement *xml)
{
	//TODO:: Refactor
	bool valid = false;
	int id = MTools::XML::getWindId(xml);
	if (id != -1) {
		_id = static_cast<unsigned int>(id);
		valid = true;
	}
	if (valid) {
		const XMLElement * cmd = xml->FirstChildElement(MSTATUS);
		//TODO: create MCommand::valid(pwind) to check common frame skeleton
		if ((/*MCommand::valid(pwind) && */cmd != nullptr))
		{
			const XMLElement * dtTag = cmd->FirstChildElement(MSTATUS_DT);
			if (dtTag != nullptr)
			{
				_printer.setDateTime(MTools::dateTime(dtTag->GetText()));
			}

			const XMLElement * versionsTag = cmd->FirstChildElement(MSTATUS_VERSION);
			if (versionsTag != nullptr)
			{
				std::string ctrlVersion = _tools.getTextFromChildNode(versionsTag, MSTATUS_VERSION_CTRL);
				std::string fpgaVersion = _tools.getTextFromChildNode(versionsTag, MSTATUS_VERSION_FPGA);
				std::string mpkVersion = _tools.getTextFromChildNode(versionsTag, MSTATUS_VERSION_API);
				_printer.setVersions(ctrlVersion, fpgaVersion, mpkVersion);
			}

			const XMLElement * boardsList = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
			if (boardsList != nullptr)
			{
				const XMLElement * board = boardsList->FirstChildElement(MPRINTER_BOARD);
				while (board != nullptr){
					//MBoard::parseBoard(_printer, board); //TODO create parse board status
					board = board->NextSiblingElement(MPRINTER_BOARD);
				}
			}
			return true;
		}
	}

	return false;
}

void MGetStatus::buildRequest()
{
	newCommandNode();
}

void MGetStatus::buildResponse()
{
	XMLElement * cmd = newCommandNode();
	_error = Printers::ErrorCode_n::SUCCESS;
	_tools.createTextChildNode(MSTATUS_DT, _printer.formatedDateTime().c_str(), &cmd);
	//TODO: fill response
}

