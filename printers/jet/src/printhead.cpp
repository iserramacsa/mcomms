#include "jet/printhead.h"

using namespace Macsa::Printers;

JetPrinthead::JetPrinthead(unsigned int id) :
	_id(id)
{}

JetPrinthead::JetPrinthead(const JetPrinthead &other) :
	_id(other._id)
{
	copy(other);
}

unsigned int JetPrinthead::id() const
{
	return _id;
}

std::string JetPrinthead::ipAddress() const
{
	return _ipAddress;
}

void JetPrinthead::setIpAddress(const std::string &ipAddress)
{
	_ipAddress = ipAddress;
}

std::string JetPrinthead::lineId() const
{
	return _lineId;
}

void JetPrinthead::setLineId(const std::string &lineId)
{
	_lineId = lineId;
}

std::string JetPrinthead::machineId() const
{
	return _machineId;
}

void JetPrinthead::setMachineId(const std::string &machineId)
{
	_machineId = machineId;
}

std::string JetPrinthead::defaultFont() const
{
	return _defaultFont;
}

void JetPrinthead::setDefaultFont(const std::string &defaultFont)
{
	_defaultFont = defaultFont;
}

double JetPrinthead::printDelay() const
{
	return _printDelay;
}

void JetPrinthead::setPrintDelay(double printDelay)
{
	_printDelay = printDelay;
}

unsigned int JetPrinthead::horizontalResolution() const
{
	return _hres;
}

void JetPrinthead::sethorizontalResolution(unsigned int hRes)
{
	_hres = hRes;
}

bool JetPrinthead::invertedBitmap() const
{
	return _inverted;
}

void JetPrinthead::setInvertedBitmap(bool inverted)
{
	_inverted = inverted;
}

unsigned int JetPrinthead::temperature() const
{
	return _temperature;
}

void JetPrinthead::setTemperature(unsigned int temperature)
{
	_temperature = temperature;
}

bool JetPrinthead::equal(const JetPrinthead &other) const
{
	return false;
}

void JetPrinthead::copy(const JetPrinthead &other)
{
	return;
}
