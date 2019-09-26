#include "printer/board.h"

using namespace Macsa::Printers;

Board::Board(const int id) :
	_id(id)
{}

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
	return _currentMessage;
}

void Board::setCurrentMessage(const std::string &currentMessage)
{
	_currentMessage = currentMessage;
}

BcdTable Board::bcdTable() const
{
	return _bcdTable;
}

void Board::setBcdTable(const BcdTable &bcdTable)
{
	_bcdTable = bcdTable;
}

PrinterDir Board::printerDirection() const
{
	return _printerDirection;
}

void Board::setPrinterDirection(const PrinterDir &printerDirection)
{
	_printerDirection = printerDirection;
}

void Board::setPrinterDirection(const PrinterDir::N& printerDirection)
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

void Board::setNozzlesCol(const NozzlesCol::N &nozzlesCol)
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

void Board::setPhotocell(const Photocell::N& photocell)
{
	_photocell = photocell;
}

void Board::setPhotocell(const std::string &photocell)
{
	_photocell = photocell;
}

std::map<std::string, std::string> Board::properties() const
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

void Board::setProperties(const std::map<std::string, std::string> &properties)
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

DateCodes Board::dateCodes() const
{
	return _dateCodes;
}

void Board::setDateCodes(const DateCodes &dateCodes)
{
	_dateCodes = dateCodes;
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
	else if (_enabled != other._enabled)
		return false;
	else if (_blocked != other._blocked)
		return false;
	else if (_currentMessage.compare(other._currentMessage) != 0)
		return false;
	else if (_printerDirection != other._printerDirection)
		return false;
	else if (_bcdTable != other._bcdTable)
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
	else if (_dateCodes != other._dateCodes)
		return false;
	else if(!checkProperties(other._properties))
		return false;
	else if (!isSameVector(_inputs, other._inputs))
		 return false;
	else if (!isSameVector(_outputs, other._outputs))
		return false;

	return true;
}

bool Board::checkProperties(const std::map<std::string, std::string> other) const
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
