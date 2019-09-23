#include "printer/configuration.h"

using namespace Macsa;
using namespace Macsa::Printers;
using namespace std;


Configuration::Configuration()
{
    _autostart = false;
}

Configuration::~Configuration()
{}

bool Configuration::autostart() const
{
    return _autostart;
}

void Configuration::setAutostart(bool autostart)
{
    _autostart = autostart;
}

bool Configuration::enabled() const
{
    return _enabled;
}

void Configuration::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool Configuration::blocked() const
{
    return _blocked;
}

void Configuration::setBlocked(bool blocked)
{
    _blocked = blocked;
}

std::string Configuration::currentMessage() const
{
    return _currentMessage;
}

void Configuration::setCurrentMessage(const std::string &currentMessage)
{
    _currentMessage = currentMessage;
}

uint8_t Configuration::bcdMode() const
{
    return _bcd.bcdMode();
}

string Configuration::bcdModeStr() const
{
    return _bcd.bcdModeStr();
}

void Configuration::setBcdMode(const string &bcdMode)
{
    return _bcd.setBcdMode(bcdMode);
}

void Configuration::setBcdMode(const BcdTable::BCDMode_n &bcdMode)
{
    _bcd.setBcdMode(bcdMode);
}

string Configuration::bcdMessage(uint8_t code) const
{
    return _bcd.bcdMessage(code);
}

void Configuration::setBcdMessage(const uint8_t &code, const string &message)
{
    return _bcd.setbBcdMessage(code, message);
}

PrinterDir_n Configuration::printerDirection() const
{
    return _printerDirection;
}

void Configuration::setPrinterDirection(const PrinterDir_n &printerDirection)
{
    _printerDirection = printerDirection;
}

string Configuration::printerDirectionStr() const
{
    switch (_printerDirection) {
        case PrinterDir_n::R2L:     return "LR";
        case PrinterDir_n::L2R:     return "RL";
        case PrinterDir_n::AUTO:    return "ID";
    }
	return "";
}

void Configuration::setPrinterDirection(const string &printerDirection)
{
    PrinterDir_n dir = _printerDirection;

    if (printerDirection.compare("LR")      == 0) { dir = PrinterDir_n::L2R; }
    else if (printerDirection.compare("RL") == 0) { dir = PrinterDir_n::R2L; }
    else if (printerDirection.compare("ID") == 0) { dir = PrinterDir_n::AUTO; }
    setPrinterDirection(dir);
}

bool Configuration::printRotated() const
{
    return _printRotated;
}

void Configuration::setPrintRotated(bool printRotated)
{
    _printRotated = printRotated;
}

NozzlesCol_n Configuration::nozzlesCol() const
{
    return _nozzlesCol;
}

string Configuration::nozzlesColStr() const
{
    switch (_nozzlesCol) {
        case COL_A: return NOZZLES_COL_A;
        case COL_B: return NOZZLES_COL_B;
        case COL_BOTH: return  NOZZLES_COL_BOTH;
    }
	return "";
}

void Configuration::setNozzlesCol(const NozzlesCol_n &nozzlesCol)
{
    _nozzlesCol = nozzlesCol;
}

void Configuration::setNozzlesCol(const string &nozzlesCol)
{
    NozzlesCol_n col = _nozzlesCol;

    if (nozzlesCol.compare(NOZZLES_COL_A) == 0)         { col = NozzlesCol_n::COL_A; }
    else if (nozzlesCol.compare(NOZZLES_COL_B) == 0)    { col = NozzlesCol_n::COL_B; }
    else if (nozzlesCol.compare(NOZZLES_COL_BOTH) == 0) { col = NozzlesCol_n::COL_BOTH; }
    setNozzlesCol(col);
}

ShotMode::ShotMode_n Configuration::shotMode() const
{
	return _shotMode.mode();
}

uint16_t Configuration::shotNumPrints()
{
    return _shotMode.numPrints();
}

std::vector<unsigned int> Configuration::shotDelays() const
{
	return _shotMode.delays();
}

EncoderMode_n Configuration::encoderMode() const
{
	return _encoder.mode;
}

double Configuration::encoderFixedSpeed() const
{
	return _encoder.fixedSpeed;
}

double Configuration::encoderResolution() const
{
	return _encoder.resolution;
}

double Configuration::encoderWheelDiameter() const
{
	return _encoder.diameter;
}

void Configuration::setEncoderMode(EncoderMode_n mode)
{
	_encoder.mode = mode;
}

void Configuration::setEncoderFixedSpeed(double speed)
{
	_encoder.fixedSpeed = speed;
}

void Configuration::setEncoderResolution(double resolution)
{
	_encoder.resolution = resolution;
}

void Configuration::setEncoderWheelDiameter(double diameter)
{
	_encoder.diameter = diameter;
}

Photocell_n Configuration::photocell() const
{
	return _photocell;
}

void Configuration::setPhotocell(const Photocell_n &photocell)
{
	_photocell = photocell;
}

bool Configuration::equal(const Configuration &other)
{
	bool equal = false;

	equal = (_autostart == other._autostart);
	equal &= (_enabled == other._enabled);
    equal &= (_blocked == other._blocked);
    equal &= (_currentMessage.compare(other._currentMessage) == 0);
    equal &= (_bcd == other._bcd);
    equal &= (_printerDirection == other._printRotated);
    equal &= (_printRotated == other._printRotated);

    return equal;
}
