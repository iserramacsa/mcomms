#include "printer/board.h"
#include "tij/tijprinter.h"

using namespace Macsa::Printers;

Board::Board(const int id, TIJPrinter* parent) :
	_id(id),
	_parent(parent)
{
	clear();
}

Board::Board(const Board &other) :
	_id(other.id()),
	_parent(other._parent)
{
	copy(other);
}

Board::~Board()
{}

int Board::id() const
{
	return _id;
}

std::string Board::type() const
{
	return _type;
}

void Board::setType(const std::string &type)
{
	_type = type;
}

bool Board::autoStart() const
{
	return _autostart;
}

void Board::setAutoStart(bool autoStart)
{
	_autostart = autoStart;
}

bool Board::lowLevelOutput() const
{
	return _lowLvlOutput;
}

void Board::setLowLevelOutput(bool lowLevelOutput)
{
	_lowLvlOutput = lowLevelOutput;
}

bool Board::printing() const
{
	return _printing;
}

void Board::setPrinting(bool printing)
{
	_printing = printing;
}

bool Board::enabled() const
{
	return _enabled;
}

void Board::setEnabled(bool enabled)
{
	_enabled = enabled;
}

bool Board::blocked() const
{
	return _blocked;
}

void Board::setBlocked(bool blocked)
{
	_blocked = blocked;
}

std::string Board::currentMessage() const
{
	return _messageManager.currentMessage();
}

std::string Board::userMessage() const
{
	return _messageManager.userMessage();
}

void Board::setUserMessage(const std::string &currentMessage)
{
	_messageManager.setUserMessage(currentMessage);
}

const BCDTable& Board::bcdTable() const
{
	return _messageManager.bcdTable();
}

BCDMode Board::bcdMode() const
{
	return _messageManager.mode();
}

uint8_t Board::currentBcdCode() const
{
	return _messageManager.currentBcdCode();
}

void Board::setBcdTable(const BCDTable& bcdTable)
{
	_messageManager.setBcdTable(bcdTable);
}

void Board::setBcdMode(const BCDMode &mode)
{
	_messageManager.setMode(mode);
}

void Board::setBcdMode(const BCDMode_n &mode)
{
	_messageManager.setMode(mode);
}

void Board::setBcdMode(const std::string &mode)
{
	_messageManager.setMode(mode);
}

void Board::setBcdCurrent(uint8_t current)
{
	_messageManager.setCurrentBcdCode(current);
}

PrinterDir Board::printDirection() const
{
	return _printerDirection;
}

void Board::setPrinterDirection(const PrinterDir &printerDirection)
{
	_printerDirection = printerDirection;
}

void Board::setPrinterDirection(const PrinterDir_n &printerDirection)
{
	_printerDirection = printerDirection;
}

void Board::setPrinterDirection(const std::string &printerDirection)
{
	_printerDirection = printerDirection;
}

bool Board::printRotated() const
{
	return _printRotated;
}

void Board::setPrintRotated(bool printRotated)
{
	_printRotated = printRotated;
}

NozzlesCol Board::nozzlesCol() const
{
	return _nozzlesCol;
}

void Board::setNozzlesCol(const NozzlesCol &nozzlesCol)
{
	_nozzlesCol = nozzlesCol;
}

void Board::setNozzlesCol(const NozzlesCol_n &nozzlesCol)
{
	_nozzlesCol = nozzlesCol;
}

void Board::setNozzlesCol(const std::string &nozzlesCol)
{
	_nozzlesCol = nozzlesCol;
}

ShotMode Board::shotMode() const
{
	return _shotMode;
}

void Board::setShotMode(const ShotMode &shotMode)
{
	_shotMode = shotMode;
}

Encoder Board::encoder() const
{
	return _encoder;
}

void Board::setEncoder(const Encoder &encoder)
{
	_encoder = encoder;
}

Photocell Board::photocell() const
{
    return _photocell;
}

void Board::setPhotocell(const Photocell& photocell)
{
	_photocell = photocell;
}

void Board::setPhotocell(const Photocell_n& photocell)
{
	_photocell = photocell;
}

void Board::setPhotocell(const std::string &photocell)
{
	_photocell = photocell;
}

Board::countersMap Board::counters() const
{
	return _counters;
}

int Board::counter(const std::string &name) const
{
	int value = -1;
	if (_counters.find(name) != _counters.end()) {
		value = _counters.at(name);
	}
	return value;

}

void Board::setCounters(const Board::countersMap& counters)
{
	_counters.clear();
	_counters.insert(counters.begin(), counters.end());
}

void Board::setCounter(const std::string &name, int value)
{
	if (_counters.find(name) == _counters.end()) {
		_counters.insert(std::pair<std::string, int>(name, value));
	}
	else{
		_counters[name] = value;
	}
}
Board::propertyMap Board::properties() const
{
	return _properties;
}

std::string Board::property(const std::string &name) const
{
	std::string value = "";
	if (_properties.find(name) != _properties.end()) {
		value = _properties.at(name);
	}
	return value;
}

void Board::setProperties(const Board::propertyMap& properties)
{
	_properties.clear();
	_properties.insert(properties.begin(), properties.end());
}

void Board::setProperty(const std::string &name, const std::string &value)
{
	if (_properties.find(name) == _properties.end()) {
		_properties.insert(std::pair<std::string, std::string>(name, value));
	}
	else{
		_properties[name] = value;
	}
}

Cartridge Board::cartridge() const
{
    return _cartridge;
}

void Board::setCartridge(const Cartridge &cartridge)
{
    _cartridge = cartridge;
}

std::vector<Input> Board::inputs() const
{
	return _inputs;
}

void Board::setInputs(const std::vector<Input> &inputs)
{
	_inputs.clear();
	_inputs.assign(inputs.begin(), inputs.end());
}

Input Board::input(unsigned int idx) const
{
	if (idx < _inputs.size()){
		return _inputs.at(idx);
	}
	return Input(idx);
}

void Board::setInput(unsigned int idx, const Input &input)
{
	if (idx < _inputs.size()){
		_inputs[idx] = input;
	}
}
std::vector<Output> Board::outputs() const
{
	return _outputs;
}

void Board::setOutputs(const std::vector<Output> &outputs)
{
	_outputs.clear();
	_outputs.assign(outputs.begin(), outputs.end());
}

Output Board::output(unsigned int idx) const
{
	if (idx <  _outputs.size()){
		return _outputs.at(idx);
	}
	return Output(idx);
}

void Board::setOutput(unsigned int idx, const Output &output)
{
	if (idx < _outputs.size()){
		_outputs[idx] = output;
	}
}

std::vector<Error> Board::errors() const
{
	return _errors;
}

void Board::setErrors(const std::vector<Error> &errors)
{
	_errors.clear();
	_errors.assign(errors.begin(), errors.end());
}

Error Board::error(unsigned int idx) const
{
	if (idx <  _errors.size()){
		return _errors.at(idx);
	}
	return Error();
}

void Board::setError(unsigned int idx, const Error &error)
{
	if (idx < _outputs.size()){
		_errors[idx] = error;
	}
}

TIJPrinter *Board::printer()
{
	return _parent;
}

const TIJPrinter *Board::printer() const
{
	return _parent;
}

void Board::clear()
{
	_type.clear();
	_autostart = false;
	_lowLvlOutput = false;
	_printing = false;
	_enabled = false;
	_blocked = true;
	_messageManager.clear();
	_printerDirection = PrinterDir_n::R2L;
	_printRotated = false;
	_nozzlesCol = NozzlesCol_n::COL_A;
	_shotMode.clear();
	_encoder.clear();
	_photocell = Photocell_n::PHCELL_A;
	_cartridge.clear();
	_properties.clear();
	_counters.clear();
	_inputs.clear();
	_outputs.clear();
	_errors.clear();
}


bool Board::equal(const Board &other) const
{
	if (_id != other._id)
		return false;
	else if (_type.compare(other._type) != 0)
		return false;
	else if (_autostart != other._autostart)
		return false;
	else if (_lowLvlOutput != other._lowLvlOutput)
		return false;
	else if (_printing != other._printing)
		return false;
	else if (_enabled != other._enabled)
		return false;
	else if (_blocked != other._blocked)
		return false;
	else if (_messageManager == other._messageManager)
		return false;
	else if (_printerDirection != other._printerDirection)
		return false;
	else if (_printRotated != other._printRotated)
		return false;
	else if (_nozzlesCol != other._nozzlesCol)
		return false;
	else if (_shotMode != other._shotMode)
		return false;
	else if (_encoder != other._encoder)
		return false;
	else if (_photocell != other._photocell)
		return false;
	else if (_cartridge != other._cartridge)
		return false;
	else if(!checkProperties(other._properties))
		return false;
	else if (!isSameVector(_inputs, other._inputs))
		 return false;
	else if (!isSameVector(_outputs, other._outputs))
		return false;
	else if (!isSameVector(_errors, other._errors))
		return false;

	return true;
}

void Board::copy(const Board &other)
{
	_type = other._type;
	_autostart = other._autostart;
	_lowLvlOutput = other._lowLvlOutput;
	_printing = other._printing;
	_enabled = other._enabled;
	_blocked = other._blocked;
	_messageManager = other._messageManager;
	_printerDirection = other._printerDirection;
	_printRotated = other._printRotated;
	_nozzlesCol = other._nozzlesCol;
	_shotMode = other._shotMode;
	_encoder = other._encoder;
	_photocell = other._photocell;
	_cartridge = other._cartridge;
	setCounters(other._counters);
	setProperties(other._properties);
	setInputs(other._inputs);
	setOutputs(other._outputs);
	setErrors(other.errors());
}

bool Board::checkProperties(const Board::propertyMap& other) const
{
	bool equal = false;
	equal = (_properties.size() == other.size());

	if(equal) {
		for (itProp i = _properties.begin(); i != _properties.end(); i++){
			itProp prop = other.find(i->first);
			equal = (prop != other.end());
			if (equal) {
				equal = (prop->second.compare(i->second) != 0);
			}

			if(!equal){
				break;
			}
		}
	}

	return equal;
}

template<class T>
bool Board::isSameVector(const std::vector<T> a, const std::vector<T> b) const
{
	bool equal = (a.size() == b.size());
	if (equal) {
		for (unsigned int i = 0; i < a.size(); i++) {
			equal = (a.at(i) != b.at(i));
			if (!equal) {
				break;
			}
		}
	}
	return equal;
}
