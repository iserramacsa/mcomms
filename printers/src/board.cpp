#include "printer/board.h"
#include "tij/tijprinter.h"

using namespace Macsa::Printers;

Board::Board(const int id, TIJPrinter* parent) :
	_id(id),
	_parent(parent),
	_mutex(new std::mutex())
{
	clear();
}

Board::Board(const Board &other, TIJPrinter* parent) :
	_id(other.id()),
	_parent(parent),
	_mutex(new std::mutex())
{
	copy(other);
}

Board::~Board()
{
	if (_mutex) {
		delete _mutex;
	}
}

int Board::id() const
{
	return _id;
}

std::string Board::type() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _type;
}

void Board::setType(const std::string &type)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_type = type;
}

bool Board::autoStart() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _autostart;
}

void Board::setAutoStart(bool autoStart)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_autostart = autoStart;
}

bool Board::lowLevelOutput() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _lowLvlOutput;
}

void Board::setLowLevelOutput(bool lowLevelOutput)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_lowLvlOutput = lowLevelOutput;
}

bool Board::printing() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _printing;
}

void Board::setPrinting(bool printing)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_printing = printing;
}

bool Board::enabled() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _enabled;
}

void Board::setEnabled(bool enabled)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_enabled = enabled;
}

bool Board::blocked() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _blocked;
}

void Board::setBlocked(bool blocked)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_blocked = blocked;
}

std::string Board::currentMessage() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _messageManager.currentMessage();
}

std::string Board::userMessage() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _messageManager.userMessage();
}

void Board::setUserMessage(const std::string &currentMessage)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_messageManager.setUserMessage(currentMessage);
}

const BCDTable& Board::bcdTable() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _messageManager.bcdTable();
}

BCDMode Board::bcdMode() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _messageManager.mode();
}

uint8_t Board::currentBcdCode() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _messageManager.currentBcdCode();
}

void Board::setBcdTable(const BCDTable& bcdTable)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_messageManager.setBcdTable(bcdTable);
}

void Board::setBcdMode(const BCDMode &mode)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_messageManager.setMode(mode);
}

void Board::setBcdMode(const BCDMode_n &mode)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_messageManager.setMode(mode);
}

void Board::setBcdMode(const std::string &mode)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_messageManager.setMode(mode);
}

void Board::setBcdCurrent(uint8_t current)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_messageManager.setCurrentBcdCode(current);
}

PrinterDir Board::printDirection() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _printerDirection;
}

void Board::setPrinterDirection(const PrinterDir &printerDirection)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_printerDirection = printerDirection;
}

void Board::setPrinterDirection(const PrinterDir_n &printerDirection)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_printerDirection = printerDirection;
}

void Board::setPrinterDirection(const std::string &printerDirection)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_printerDirection = printerDirection;
}

bool Board::printRotated() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _printRotated;
}

void Board::setPrintRotated(bool printRotated)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_printRotated = printRotated;
}

NozzlesCol Board::nozzlesCol() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _nozzlesCol;
}

void Board::setNozzlesCol(const NozzlesCol &nozzlesCol)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_nozzlesCol = nozzlesCol;
}

void Board::setNozzlesCol(const NozzlesCol_n &nozzlesCol)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_nozzlesCol = nozzlesCol;
}

void Board::setNozzlesCol(const std::string &nozzlesCol)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_nozzlesCol = nozzlesCol;
}

ShotMode Board::shotMode() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _shotMode;
}

void Board::setShotMode(const ShotMode &shotMode)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_shotMode = shotMode;
}

Encoder Board::encoder() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _encoder;
}

void Board::setEncoder(const Encoder &encoder)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_encoder = encoder;
}

Photocell Board::photocell() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
    return _photocell;
}

void Board::setPhotocell(const Photocell& photocell)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_photocell = photocell;
}

void Board::setPhotocell(const Photocell_n& photocell)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_photocell = photocell;
}

void Board::setPhotocell(const std::string &photocell)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_photocell = photocell;
}

Board::countersMap Board::counters() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _counters;
}

int Board::counter(const std::string &name) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	int value = -1;
	if (_counters.find(name) != _counters.end()) {
		value = _counters.at(name);
	}
	return value;

}

void Board::setCounters(const Board::countersMap& counters)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_counters.clear();
	_counters.insert(counters.begin(), counters.end());
}

void Board::setCounter(const std::string &name, int value)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (_counters.find(name) == _counters.end()) {
		_counters.insert(std::pair<std::string, int>(name, value));
	}
	else{
		_counters[name] = value;
	}
}
Board::propertyMap Board::properties() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _properties;
}

std::string Board::property(const std::string &name) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	std::string value = "";
	if (_properties.find(name) != _properties.end()) {
		value = _properties.at(name);
	}
	return value;
}

void Board::setProperties(const Board::propertyMap& properties)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_properties.clear();
	_properties.insert(properties.begin(), properties.end());
}

void Board::setProperty(const std::string &name, const std::string &value)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (_properties.find(name) == _properties.end()) {
		_properties.insert(std::pair<std::string, std::string>(name, value));
	}
	else{
		_properties[name] = value;
	}
}

Cartridge Board::cartridge() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
    return _cartridge;
}

void Board::setCartridge(const Cartridge &cartridge)
{
	std::lock_guard<std::mutex>lock(*_mutex);
    _cartridge = cartridge;
}

std::vector<Input> Board::inputs() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _inputs;
}

void Board::setInputs(const std::vector<Input> &inputs)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_inputs.clear();
	_inputs.assign(inputs.begin(), inputs.end());
}

Input Board::input(unsigned int idx) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (idx < _inputs.size()){
		return _inputs.at(idx);
	}
	return Input(idx);
}

void Board::setInput(unsigned int idx, const Input &input)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (idx < _inputs.size()){
		_inputs[idx] = input;
	}
}
std::vector<Output> Board::outputs() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _outputs;
}

void Board::setOutputs(const std::vector<Output> &outputs)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_outputs.clear();
	_outputs.assign(outputs.begin(), outputs.end());
}

Output Board::output(unsigned int idx) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (idx <  _outputs.size()){
		return _outputs.at(idx);
	}
	return Output(idx);
}

void Board::setOutput(unsigned int idx, const Output &output)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (idx < _outputs.size()){
		_outputs[idx] = output;
	}
}

std::vector<Error> Board::errors() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _errors;
}

void Board::setErrors(const std::vector<Error> &errors)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_errors.clear();
	_errors.assign(errors.begin(), errors.end());
}

Error Board::error(unsigned int idx) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (idx <  _errors.size()){
		return _errors.at(idx);
	}
	return Error();
}

void Board::setError(unsigned int idx, const Error &error)
{
	std::lock_guard<std::mutex>lock(*_mutex);
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
	std::lock_guard<std::mutex>lock(*_mutex);
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
	std::lock_guard<std::mutex>lock(*_mutex);
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
	if (*this != other){
		{
			std::lock_guard<std::mutex>lock(*_mutex);
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
		}
		setCounters(other._counters);
		setProperties(other._properties);
		setInputs(other._inputs);
		setOutputs(other._outputs);
		setErrors(other.errors());
	}
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
