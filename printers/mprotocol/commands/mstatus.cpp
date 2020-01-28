#include "mprotocol/mstatus.h"
#include "mprotocol/mprotocol.h"
#include "mtools.h"
using namespace Macsa::MProtocol;
using namespace tinyxml2;

//================		STATUS COMMANDS BASE CLASS		================//
MStatusCommand::MStatusCommand(std::string command, Macsa::Printers::TIJPrinter &printer) :
	MCommand(command, printer)
{}

MStatusCommand::~MStatusCommand()
{}

void MStatusCommand::countersToXml(const Macsa::Printers::Board &board, XMLElement **parent)
{
	XMLElement* xCountersList = createChildNode(MPRINTER_BOARD_COUNTERS_LIST, parent);
	if (xCountersList != nullptr) {
		const Printers::Board::countersMap& counters = board.counters();
		for (Printers::Board::countersMap::const_iterator counter = counters.begin(); counter != counters.end(); counter++) {
			XMLElement* xCounter = createChildNode(MPRINTER_BOARD_COUNTER, &xCountersList);
			if (xCounter != nullptr) {
				xCounter->SetAttribute(ATTRIBUTE_ID, counter->first.c_str());
				xCounter->SetAttribute(ATTRIBUTE_VALUE, counter->second);
			}
		}
	}
}

void MStatusCommand::errorsToXml(const Printers::Board &board, XMLElement **parent)
{
	XMLElement* xErrorsList = createChildNode(MPRINTER_BOARD_ERRORS_LIST, parent);
	if (xErrorsList != nullptr) {
		const std::vector<Printers::Error>& errorsList = board.errors();
		for (std::vector<Printers::Error>::const_iterator error = errorsList.begin(); error != errorsList.end(); error++) {
			XMLElement* xError = createChildNode(MPRINTER_BOARD_ERROR, &xErrorsList);
			if (xError != nullptr) {
				xError->SetAttribute(MPRINTER_BOARD_ERR_TYPE_ATTR, (*error).type().toString().c_str());
				xError->SetAttribute(MPRINTER_BOARD_ERR_PRIO_ATTR, (*error).priority());
				xError->SetAttribute(MPRINTER_BOARD_ERR_CODE_ATTR, (*error).code().toString().c_str());
			}
		}
	}
}

void MStatusCommand::inputsToXml(const Macsa::Printers::Board &board, XMLElement **parent)
{
	XMLElement* xInputs = createChildNode(MPRINTER_BOARD_INPUTS_LIST, parent);
	if (xInputs == nullptr) {
		const std::vector<Printers::Input>& inputsList = board.inputs();
		for (std::vector<Printers::Input>::const_iterator input = inputsList.begin(); input != inputsList.end(); input++) {
			XMLElement* xInput = createChildNode(MPRINTER_BOARD_INPUT, &xInputs);
			if (xInput != nullptr) {
				xInput->SetAttribute(ATTRIBUTE_ID, (*input).id());
				xInput->SetAttribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR, (*input).descriptor().c_str());
				xInput->SetAttribute(ATTRIBUTE_VALUE, (*input).value());
			}
		}
	}
}

void MStatusCommand::outputsToXml(const Macsa::Printers::Board &board, XMLElement **parent)
{
	XMLElement* xOutputs = createChildNode(MPRINTER_BOARD_OUTPUTS_LIST, parent);
	if (xOutputs == nullptr) {
		const std::vector<Printers::Output>& outputsList = board.outputs();
		for (std::vector<Printers::Output>::const_iterator output = outputsList.begin(); output != outputsList.end(); output++) {
			XMLElement* xOutput = createChildNode(MPRINTER_BOARD_OUTPUT, &xOutputs);
			if (xOutput != nullptr) {
				xOutput->SetAttribute(ATTRIBUTE_ID, (*output).id());
				xOutput->SetAttribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR, (*output).descriptor().c_str());
				xOutput->SetAttribute(ATTRIBUTE_VALUE, (*output).value());
			}
		}
	}
}

void MStatusCommand::propertiesToXml(const Macsa::Printers::Board &board, XMLElement **parent)
{
	XMLElement* xProperties = createChildNode(MPRINTER_BOARD_PROPERTIES_LIST, parent);
	if (xProperties == nullptr) {
		const Printers::Board::propertyMap& properties =  board.properties();
		for (Printers::Board::propertyMap::const_iterator property = properties.begin(); property != properties.end(); property++) {
			XMLElement* xProperty = createChildNode(MPRINTER_BOARD_PROPERTY, &xProperties);
			xProperty->SetAttribute(ATTRIBUTE_KEY, (*property).first.c_str());
			xProperty->SetAttribute(ATTRIBUTE_VALUE, (*property).second.c_str());
		}
	}
}

void MStatusCommand::countersFromXml(const XMLElement *parent, Macsa::Printers::Board &board) const
{
	if (parent) {
		const XMLElement* xCounter = parent->FirstChildElement(MPRINTER_BOARD_COUNTER);
		while (xCounter != nullptr) {
			std::string key = xCounter->Attribute(ATTRIBUTE_ID);
			if (key.length()) {
				int value = board.counter(key);
				value = (value != -1) ? value : 0;
				value = xCounter->IntAttribute(ATTRIBUTE_VALUE, value);
				board.setCounter(key, value);
			}

			xCounter = xCounter->NextSiblingElement(MPRINTER_BOARD_COUNTER);
		}
	}
}

void MStatusCommand::errorsFromXml(const XMLElement *parent, Macsa::Printers::Board &board) const
{
	std::vector<Printers::Error> errors;
	if (parent) {
		const XMLElement* xError = parent->FirstChildElement(MPRINTER_BOARD_ERROR);
		while (xError != nullptr) {
			Printers::Error error;
			error.setType(xError->Attribute(MPRINTER_BOARD_ERR_TYPE_ATTR));
			error.setPriority(xError->UnsignedAttribute(MPRINTER_BOARD_ERR_PRIO_ATTR));
			error.setCode(xError->Attribute(MPRINTER_BOARD_ERR_CODE_ATTR));

			errors.push_back(error);

			xError = xError->NextSiblingElement(MPRINTER_BOARD_ERROR);
		}
	}
	board.setErrors(errors);
}

void MStatusCommand::inputsFromXml(const XMLElement *parent, Macsa::Printers::Board &board) const
{
	if (parent) {
		std::vector<Printers::Input> inputs;
		const XMLElement* xInput = parent->FirstChildElement();
		while (xInput != nullptr) {
			unsigned int inputId = xInput->UnsignedAttribute(ATTRIBUTE_ID);
			Printers::Input input = board.input(inputId);
			input.setDescriptor(xInput->Attribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR));
			input.setValue(MTools::boolfromString(xInput->Attribute(ATTRIBUTE_VALUE)));

			inputs.push_back(input);

			xInput = xInput->NextSiblingElement();
		}
		board.setInputs(inputs);
	}
}

void MStatusCommand::outputsFromXml(const XMLElement *parent, Macsa::Printers::Board &board) const
{
	if (parent) {
		std::vector<Printers::Output> outputs;
		const XMLElement* xOutput = parent->FirstChildElement();
		while (xOutput != nullptr) {
			unsigned int outputId = xOutput->UnsignedAttribute(ATTRIBUTE_ID);
			Printers::Output output = board.output(outputId);
			output.setDescriptor(xOutput->Attribute(MPRINTER_BOARD_IO_DESCRIPT_ATTR));
			output.setValue(MTools::boolfromString(xOutput->Attribute(ATTRIBUTE_VALUE)));

			outputs.push_back(output);

			xOutput = xOutput->NextSiblingElement();
		}
	}
}

void MStatusCommand::propertiesFromXml(const XMLElement *parent, Macsa::Printers::Board &board) const
{
	if (parent) {
		const XMLElement* xProperty = parent->FirstChildElement(MPRINTER_BOARD_PROPERTY);
		Printers::Board::propertyMap properties;
		while (xProperty != nullptr) {
			std::string key = xProperty->Attribute(ATTRIBUTE_KEY);
			if (key.length()) {
				std::string value = xProperty->Attribute(ATTRIBUTE_VALUE);
				properties.insert(std::pair<std::string,std::string>(key, value));
			}
			xProperty = xProperty->NextSiblingElement(MPRINTER_BOARD_PROPERTY);
		}
		board.setProperties(properties);
	}
}


//================		GET STATUS COMMAND		================//
MGetStatus::MGetStatus(Printers::TIJPrinter &printer):
	MStatusCommand(MSTATUS, printer)
{}

MGetStatus::~MGetStatus()
{}

void MGetStatus::buildRequest()
{
	newCommandNode();
}

bool MGetStatus::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	return valid;
}

void MGetStatus::buildResponse()
{
	XMLElement * cmd = newCommandNode();
	if (cmd != nullptr) {

		createTextChildNode(MSTATUS_DT, _printer.formatedDateTime().c_str(), &cmd);

		XMLElement * xVersions = createChildNode(MSTATUS_VERSION, &cmd);
		if (xVersions == nullptr) {
			createTextChildNode(MSTATUS_VERSION_CTRL, _printer.controllerVersion(), &xVersions);
			createTextChildNode(MSTATUS_VERSION_FPGA, _printer.apiVersion(), &xVersions);
			createTextChildNode(MSTATUS_VERSION_API, _printer.fpgaVersion(), &xVersions);
		}

		XMLElement* xBoards = createChildNode(MPRINTER_BOARDS_LIST, &cmd);
		if (xBoards != nullptr) {
			std::vector<Printers::Board> boardsList = _printer.boards();
			for(std::vector<Printers::Board>::iterator b = boardsList.begin(); b != boardsList.end(); b++) {
				Printers::Board& board = *b;
				XMLElement* xBoard = createChildNode(MPRINTER_BOARD, &xBoards);
				if (xBoard){
					xBoard->SetAttribute(ATTRIBUTE_ID, board.id());
					createTextChildNode(MPRINTER_BOARD_TYPE, board.type(), &xBoard);
					createBoolTextChildNode(MPRINTER_BOARD_PRINTING, board.printing(), &xBoard);
					createBoolTextChildNode(MPRINTER_BOARD_ENABLED, board.enabled(), &xBoard);
					XMLElement* xCurrentMsg = createChildNode(MPRINTER_BOARD_CURRENT_MSG, &xBoard);
					if (xCurrentMsg != nullptr) {
						xCurrentMsg->SetAttribute(ATTRIBUTE_FILEPATH, board.userMessage().c_str());
					}
					createTextChildNode(MPRINTER_BOARD_BCD_MODE, board.bcdMode().toString(), &xBoard);
					createUnsignedTextChildNode(MPRINTER_BOARD_BCD_STATUS, board.currentBcdCode(), &xBoard);
					countersToXml(board, &xBoard);
					errorsToXml(board, &xBoard);
					inputsToXml(board, &xBoard);
					outputsToXml(board, &xBoard);
					propertiesToXml(board, &xBoard);
				}
			}
		}
	}

	addWindError(_error);
}

bool MGetStatus::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
		if (_error == Printers::ErrorCode_n::SUCCESS) {
			_printer.setDateTime(getTextFromChildNode(cmd, MSTATUS_DT, _printer.formatedDateTime()));
			const XMLElement* xVersion = cmd->FirstChildElement(MSTATUS_VERSION);
			if (xVersion != nullptr){
				std::string ctrlVersion = getTextFromChildNode(xVersion, MSTATUS_VERSION_CTRL,_printer.controllerVersion());
				std::string fpgaVersion = getTextFromChildNode(xVersion, MSTATUS_VERSION_FPGA, _printer.fpgaVersion());
				std::string mpkVersion  = getTextFromChildNode(xVersion, MSTATUS_VERSION_API, _printer.apiVersion());
				_printer.setVersions(ctrlVersion, fpgaVersion, mpkVersion);
			}
			const XMLElement * xBoardsList = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
			if (xBoardsList != nullptr) {
				const XMLElement * xBoard = xBoardsList->FirstChildElement(MPRINTER_BOARD);
				std::vector<Printers::Board> boards;
				while (xBoard != nullptr){
					int id = xBoard->IntAttribute(ATTRIBUTE_ID, 0);
					Printers::Board board(id, &_printer);
					if (_printer.board(id) != nullptr) {
						board = *_printer.board(id);
					}
					board.setType(getTextFromChildNode(xBoard, MPRINTER_BOARD_TYPE, board.type().c_str()));
					board.setEnabled(getBoolFromChildNode(xBoard, MPRINTER_BOARD_ENABLED, board.enabled()));
					board.setPrinting(getBoolFromChildNode(xBoard, MPRINTER_BOARD_PRINTING, board.printing()));
					const XMLElement * xUserMessage = xBoard->FirstChildElement(MPRINTER_BOARD_CURRENT_MSG);
					if (xUserMessage != nullptr){
						board.setUserMessage(xUserMessage->Attribute(ATTRIBUTE_FILEPATH, board.userMessage().c_str()));
					}
					board.setBcdMode(getTextFromChildNode(xBoard, MPRINTER_BOARD_BCD_MODE, board.bcdMode().toString()));
					board.setBcdCurrent(static_cast<uint8_t>(getUnsignedFromChildNode(xBoard, MPRINTER_BOARD_BCD_STATUS, board.currentBcdCode())));

					countersFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_COUNTERS_LIST), board);
					errorsFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_ERRORS_LIST), board);
					inputsFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_INPUTS_LIST), board);
					outputsFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_OUTPUTS_LIST), board);
					propertiesFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_PROPERTIES_LIST), board);

					boards.push_back(board);
					xBoard = xBoard->NextSiblingElement(MPRINTER_BOARD);
				}
				_printer.setBoards(boards);
			}
		}
	}
	return valid;
}

//================		GET IO STATUS COMMAND		================//
MGetIOStatus::MGetIOStatus(Macsa::Printers::TIJPrinter &printer):
	MStatusCommand(MIOSTATUS, printer)
{}

MGetIOStatus::~MGetIOStatus()
{}

void MGetIOStatus::buildRequest()
{
	newCommandNode();
}

bool MGetIOStatus::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	return valid;
}

void MGetIOStatus::buildResponse()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		XMLElement* xBoards = createChildNode(MPRINTER_BOARDS_LIST, &cmd);
		if (xBoards != nullptr) {
			std::vector<Printers::Board> boardsList = _printer.boards();
			for(std::vector<Printers::Board>::iterator b = boardsList.begin(); b != boardsList.end(); b++) {
				Printers::Board& board = *b;
				XMLElement* xBoard = createChildNode(MPRINTER_BOARD, &xBoards);
				if (xBoard){
					xBoard->SetAttribute(ATTRIBUTE_ID, board.id());
					inputsToXml(board, &xBoard);
					outputsToXml(board, &xBoard);
				}
			}
		}
	}
	addWindError(_error);
}

bool MGetIOStatus::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
		if (_error == Printers::ErrorCode_n::SUCCESS) {
			const XMLElement * xBoardsList = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
			if (xBoardsList != nullptr) {
				const XMLElement * xBoard = xBoardsList->FirstChildElement(MPRINTER_BOARD);
				std::vector<Printers::Board> boards;
				while (xBoard != nullptr) {
					int id = xBoard->IntAttribute(ATTRIBUTE_ID, 0);
					Printers::Board board(id, &_printer);
					if (_printer.board(id) != nullptr) {
						board = *_printer.board(id);
					}

					inputsFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_INPUTS_LIST), board);
					outputsFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_OUTPUTS_LIST), board);

					boards.push_back(board);
					xBoard = xBoard->NextSiblingElement(MPRINTER_BOARD);
				}
				_printer.setBoards(boards);
			}
		}
	}
	return valid;

}

//================		GET CURRENT ERRORS COMMAND		================//
MGetErrors::MGetErrors(Macsa::Printers::TIJPrinter &printer):
	MStatusCommand(MERRORS_GET, printer)
{}

MGetErrors::~MGetErrors()
{}

void MGetErrors::buildRequest()
{
	newCommandNode();
}

bool MGetErrors::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr && cmd->NoChildren());
	return valid;
}
void MGetErrors::buildResponse()
{
	XMLElement * cmd = newCommandNode();
	if (cmd != nullptr) {
		XMLElement* xBoards = createChildNode(MPRINTER_BOARDS_LIST, &cmd);
		if (xBoards != nullptr) {
			std::vector<Printers::Board> boardsList = _printer.boards();
			for(std::vector<Printers::Board>::iterator b = boardsList.begin(); b != boardsList.end(); b++) {
				Printers::Board& board = *b;
				XMLElement* xBoard = createChildNode(MPRINTER_BOARD, &xBoards);
				if (xBoard){
					errorsToXml(board, &xBoard);
				}
			}
		}
	}

	addWindError(_error);
}
bool MGetErrors::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
		if (_error == Printers::ErrorCode_n::SUCCESS) {
			const XMLElement * xBoardsList = cmd->FirstChildElement(MPRINTER_BOARDS_LIST);
			if (xBoardsList != nullptr) {
				const XMLElement * xBoard = xBoardsList->FirstChildElement(MPRINTER_BOARD);
				std::vector<Printers::Board> boards;
				while (xBoard != nullptr) {
					int id = xBoard->IntAttribute(ATTRIBUTE_ID, 0);
					Printers::Board board(id, &_printer);
					if (_printer.board(id) != nullptr) {
						board = *_printer.board(id);
					}
					errorsFromXml(xBoard->FirstChildElement(MPRINTER_BOARD_ERRORS_LIST), board);

					boards.push_back(board);
					xBoard = xBoard->NextSiblingElement(MPRINTER_BOARD);
				}
				_printer.setBoards(boards);
			}
		}
	}
	return valid;

}
