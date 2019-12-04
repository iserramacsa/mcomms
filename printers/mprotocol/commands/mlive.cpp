#include "mprotocol/mlive.h"
#include "mtools.h"
#include <sstream>

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MLive::MLive(Macsa::Printers::Printer &printer):
	MCommand(MLIVE, printer)
{}

void MLive::buildRequest()
{
	XMLElement* wind = buildNewFrame();
	MTools::XML::newElement(commandName(), _doc, &wind);
}

void MLive::buildResponse()
{
	XMLElement* wind = buildNewFrame();
	XMLElement* live = MTools::XML::newElement(MLIVE, _doc, &wind);

	live->SetAttribute(MLIVE_DT_ATTR,		MTools::dateTime().c_str());
	//live->SetAttribute(MLIVE_STATUS_ATTR,	_printer.statusChanged());			//TODO: refactor live monitor
	//live->SetAttribute(MLIVE_CONFIG_ATTR,	_printer.configChanged());			//TODO: refactor live monitor
	//live->SetAttribute(MLIVE_FILES_ATTR,		_printer.filesChanged());		//TODO: refactor live monitor
	//live->SetAttribute(MLIVE_FONTS_ATTR,		_printer.fontsChanged());		//TODO: refactor live monitor
	//live->SetAttribute(MLIVE_ERRORS_ATTR,	_printer.errorsChanged());			//TODO: refactor live monitor

	XMLElement* eBoards = MTools::XML::newElement(MPRINTER_BOARDS_LIST, _doc, &live);
	if (eBoards != nullptr) {
		const std::vector<Printers::Board> & boards = _printer.configuration().boards();
		for (auto& board : boards) {
			//<BOARD id="[Board Id]" enabled="[value]" printing="[value]" >
			XMLElement* eBoard = MTools::XML::newElement(MPRINTER_BOARD, _doc, &eBoards);
			eBoard->SetAttribute(MPRINTER_BOARD_ID_ATTR, board.id());
			eBoard->SetAttribute(MPRINTER_BOARD_ENABLED_ATTR, board.enabled());
			eBoard->SetAttribute(MPRINTER_BOARD_PRINT_ATTR, board.printing());
			if (board.enabled()) {
				//<COUNTERS total="[value]" user="[value]"/>
				XMLElement* eCounters = MTools::XML::newElement(MPRINTER_BOARD_COUNTERS_LIST, _doc, &eBoard);
				std::stringstream counterName;
				if (board.bcdTable().mode()() == Printers::BCDMode_n::USER_MODE) {
					counterName << key_counter_system_user;
				}
				else {
					counterName << key_counter_system_bcd << board.bcdTable().current();
				}
				eCounters->SetAttribute(MPRINTER_BOARD_COUNT_TOTAL, board.counter(key_counter_system_total));
				eCounters->SetAttribute(MPRINTER_BOARD_COUNT_USER, board.counter(counterName.str()));

				// <PRINT_SPEED value="[Actual print speed]"/>
				XMLElement* eSpeed = MTools::XML::newElement(MPRINTER_BOARD_PRINT_SPEED, _doc, &eBoard);
				eSpeed->SetAttribute(ATTRIBUTE_VALUE, board.property(key_prop_status_general_print_speed).c_str());

				// <NUM_PRINTS_REMAIN Value="[Num prints remaining]"/>
				XMLElement* ePrintsRemain = MTools::XML::newElement(MPRINTER_BOARD_PRINTS_REMAIN, _doc, &eBoard);
				ePrintsRemain->SetAttribute(ATTRIBUTE_VALUE, board.property(key_prop_status_general_print_remain).c_str());
			}
		}
	}
}

bool MLive::parseRequest(const XMLElement *xml)
{
	return parseSingleCommand(xml);
}

bool MLive::parseResponse(const XMLElement *xml)
{
	int id  = MTools::XML::getWindId(xml);
	bool valid = false;
	if (id != -1) {
		const XMLElement * cmd = xml->FirstChildElement(MLIVE);
		if (cmd != nullptr)
		{
			_error = MTools::XML::getWindError(xml);
			const char* dt = cmd->Attribute(MLIVE_DT_ATTR);
			valid = (!cmd->NoChildren() && dt != nullptr);
			if (valid){
				_id = static_cast<uint32_t>(id);
				_printer.setDateTime(MTools::dateTime(dt));
				// _printer.setStatusChanged(cmd->BoolAttribute(MLIVE_STATUS_ATTR));  //TODO refactor live monitor
				// _printer.setConfigChanged(cmd->BoolAttribute(MLIVE_CONFIG_ATTR));  //TODO refactor live monitor
				// _printer.setFilesChanged(cmd->BoolAttribute(MLIVE_FILES_ATTR));	  //TODO refactor live monitor
				// _printer.setFontsChanged(cmd->BoolAttribute(MLIVE_FONTS_ATTR));	  //TODO refactor live monitor
				// _printer.setErrorsChanged(cmd->BoolAttribute(MLIVE_ERRORS_ATTR));  //TODO refactor live monitor

				const XMLElement* eBoards = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
				if (eBoards != nullptr) {
					const XMLElement* eBoard = eBoards->FirstChildElement(MPRINTER_BOARD);
					while (eBoard != nullptr) {
						int id = eBoard->IntAttribute(MPRINTER_BOARD_ID_ATTR, -1);
						Printers::Board* pBoard = _printer.configuration().board(id);
						if  (id != -1 && pBoard != nullptr) {
							pBoard->setEnabled(eBoard->BoolAttribute(MPRINTER_BOARD_ENABLED_ATTR));
							pBoard->setPrinting(eBoard->BoolAttribute(MPRINTER_BOARD_PRINT_ATTR));
							if (pBoard->enabled()) {
								const XMLElement* eCounters = eBoard->FirstChildElement(MPRINTER_BOARD_COUNTERS_LIST);
								if (eCounters != nullptr) {
									int total = eCounters->IntAttribute(MPRINTER_BOARD_COUNT_TOTAL);
									int partial = eCounters->IntAttribute(MPRINTER_BOARD_COUNT_USER);
									pBoard->setCounter(key_counter_system_total, total);
									std::string counterName = key_counter_system_user;
									if (pBoard->bcdTable().mode()() != Printers::BCDMode_n::USER_MODE) {
										counterName = key_counter_system_bcd;
										counterName.append(std::to_string(pBoard->bcdTable().current()));
									}
									pBoard->setCounter(counterName, partial);
								}

								const XMLElement* eSpeed = eBoard->FirstChildElement(MPRINTER_BOARD_PRINT_SPEED);
								if (eSpeed != nullptr){
									pBoard->setProperty(key_prop_status_general_print_speed, eSpeed->Attribute(ATTRIBUTE_VALUE));
								}

								const XMLElement* ePrintsRemain = eBoard->FirstChildElement(MPRINTER_BOARD_PRINTS_REMAIN);
								if  (ePrintsRemain){
									pBoard->setProperty(key_prop_status_general_print_remain, ePrintsRemain->Attribute(ATTRIBUTE_VALUE));
								}
							}
							_printer.configuration().setBoard(*pBoard);
						}
						eBoard = eBoard->NextSiblingElement(MPRINTER_BOARD);
					}
				}
			}

		}
	}
	return valid;
}
