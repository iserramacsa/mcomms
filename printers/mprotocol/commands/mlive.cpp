#include "mprotocol/mlive.h"
#include "mprotocol/mprotocol.h"
#include "mtools.h"
#include <sstream>

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MLive::MLive(Macsa::Printers::TIJPrinter& printer, LiveFlags& flags):
	MCommand(MLIVE, printer),
	_liveFlags(flags)
{}

void MLive::buildRequest()
{
	newCommandNode();
}

void MLive::buildResponse()
{
	XMLElement* live = newCommandNode();
	live->SetAttribute(MLIVE_DT_ATTR, _printer.formatedDateTime ().c_str());

	_error = Printers::ErrorCode_n::SUCCESS;

	live->SetAttribute(MLIVE_STATUS_ATTR, MTools::toCString(_liveFlags.statusChanged));
	live->SetAttribute(MLIVE_CONFIG_ATTR, MTools::toCString(_liveFlags.configChanged));
	live->SetAttribute(MLIVE_FILES_ATTR,  MTools::toCString(_liveFlags.filesChanged));
	live->SetAttribute(MLIVE_FONTS_ATTR,  MTools::toCString(_liveFlags.fontsChanged));
	live->SetAttribute(MLIVE_USER_VALUES_ATTR,  MTools::toCString(_liveFlags.userValueChanged));
	live->SetAttribute(MLIVE_ERRORS_LOG_ATTR,  MTools::toCString(_liveFlags.errorsLogChanged));
	live->SetAttribute(MLIVE_ERROR_ATTR,	MTools::toCString(_liveFlags.isInError));

	XMLElement* eBoards = createChildNode(MPRINTER_BOARDS_LIST, &live);
	if (eBoards != nullptr) {
		const std::vector<Printers::Board> & boards = _printer.boards();
		for (auto& board : boards) {
			//<BOARD id="[Board Id]" enabled="[value]" printing="[value]" >
			XMLElement* eBoard = createChildNode(MPRINTER_BOARD, &eBoards);
			eBoard->SetAttribute(ATTRIBUTE_ID, board.id());
			eBoard->SetAttribute(MPRINTER_BOARD_ENABLED_ATTR, board.enabled());
			eBoard->SetAttribute(MPRINTER_BOARD_PRINT_ATTR, board.printing());
			if (board.enabled()) {
				//<COUNTERS total="[value]" user="[value]"/>
				XMLElement* eCounters = createChildNode(MPRINTER_BOARD_COUNTERS_LIST, &eBoard);
				std::stringstream counterName;
				if (board.bcdMode() == Printers::BCDMode_n::USER_MODE) {
					counterName << key_counter_system_user;
				}
				else {
					counterName << key_counter_system_bcd << board.currentBcdCode();
				}
				eCounters->SetAttribute(MPRINTER_BOARD_COUNT_TOTAL, board.counter(key_counter_system_total));
				eCounters->SetAttribute(MPRINTER_BOARD_COUNT_USER, board.counter(counterName.str()));

				// <PRINT_SPEED value="[Actual print speed]"/>
				XMLElement* eSpeed = createChildNode(MPRINTER_BOARD_PRINT_SPEED, &eBoard);
				eSpeed->SetAttribute(ATTRIBUTE_VALUE, board.configurationProperty(key_prop_status_general_print_speed).c_str());

				// <NUM_PRINTS_REMAIN Value="[Num prints remaining]"/>
				XMLElement* ePrintsRemain = createChildNode(MPRINTER_BOARD_PRINTS_REMAIN, &eBoard);
				ePrintsRemain->SetAttribute(ATTRIBUTE_VALUE, board.configurationProperty(key_prop_status_general_print_remain).c_str());
			}
		}
	}
	addWindError(_error);
}

bool MLive::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	return valid;
}

bool MLive::parseResponse(const XMLElement *xml)
{
	bool valid = false;
	const XMLElement * cmd = getCommand(xml, _id);
	if (cmd != nullptr)
	{
		_error = getCommandError(xml);
		std::string dt = getTextAttribute(cmd, MLIVE_DT_ATTR);
		valid = (!cmd->NoChildren() && dt.length());
		if (valid){
			_printer.setDateTime(dt);

			_liveFlags.statusChanged = getBoolAttribute(cmd, MLIVE_STATUS_ATTR, _liveFlags.statusChanged);
			_liveFlags.configChanged = getBoolAttribute(cmd, MLIVE_CONFIG_ATTR, _liveFlags.configChanged);
			_liveFlags.filesChanged = getBoolAttribute(cmd, MLIVE_FILES_ATTR, _liveFlags.filesChanged);
			_liveFlags.fontsChanged = getBoolAttribute(cmd, MLIVE_FONTS_ATTR, _liveFlags.fontsChanged);
			_liveFlags.userValueChanged = getBoolAttribute(cmd, MLIVE_USER_VALUES_ATTR, _liveFlags.userValueChanged);
			_liveFlags.errorsLogChanged = getBoolAttribute(cmd, MLIVE_ERRORS_LOG_ATTR, _liveFlags.errorsLogChanged);
			_liveFlags.isInError = getBoolAttribute(cmd, MLIVE_ERROR_ATTR, _liveFlags.isInError);

			const XMLElement* eBoards = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
			if (eBoards != nullptr) {
				const XMLElement* eBoard = eBoards->FirstChildElement(MPRINTER_BOARD);
				while (eBoard != nullptr) {
					int id = eBoard->IntAttribute(ATTRIBUTE_ID, -1);
					if (id != -1) {
						Printers::Board* pBoard = _printer.board(id);
						bool newBoard = (pBoard == nullptr);
						if (newBoard) {
							pBoard = new Printers::Board(id, &_printer);
						}
						pBoard->setEnabled( getBoolAttribute(eBoard,MPRINTER_BOARD_ENABLED_ATTR, pBoard->enabled()));
						pBoard->setPrinting(getBoolAttribute(eBoard,MPRINTER_BOARD_PRINT_ATTR, pBoard->printing ()));
						if (pBoard->enabled()) {
							const XMLElement* eCounters = eBoard->FirstChildElement(MPRINTER_BOARD_COUNTERS_LIST);
							if (eCounters != nullptr) {
								int total = eCounters->IntAttribute(MPRINTER_BOARD_COUNT_TOTAL);
								int partial = eCounters->IntAttribute(MPRINTER_BOARD_COUNT_USER);
								pBoard->setCounter(key_counter_system_total, total);
								std::string counterName = key_counter_system_user;
								if (pBoard->bcdMode() != Printers::BCDMode_n::USER_MODE) {
									counterName = key_counter_system_bcd;
									counterName.append(std::to_string(pBoard->currentBcdCode()));
								}
								pBoard->setCounter(counterName, partial);
							}

							const XMLElement* eSpeed = eBoard->FirstChildElement(MPRINTER_BOARD_PRINT_SPEED);
							if (eSpeed != nullptr){
								pBoard->setConfigurationProperty(key_prop_status_general_print_speed, getTextAttribute(eSpeed, ATTRIBUTE_VALUE));
							}

							const XMLElement* ePrintsRemain = eBoard->FirstChildElement(MPRINTER_BOARD_PRINTS_REMAIN);
							if  (ePrintsRemain){
								pBoard->setConfigurationProperty(key_prop_status_general_print_remain, getTextAttribute(ePrintsRemain, ATTRIBUTE_VALUE));
							}

						}
						_printer.setBoard(*pBoard);
						if (newBoard) {
							delete pBoard;
						}
					}
					eBoard = eBoard->NextSiblingElement(MPRINTER_BOARD);
				}
			}
		}
	}
	return valid;
}
