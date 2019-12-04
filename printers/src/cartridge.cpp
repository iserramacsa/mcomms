#include "printer/cartridge.h"

using namespace Macsa::Printers;

Cartridge::Cartridge()
{
	clear();
}

Cartridge::~Cartridge()
{}

std::string Cartridge::id() const
{
	return _id;
}

void Cartridge::setId(const std::string &id)
{
	_id = id;
}

uint32_t Cartridge::columnDistance() const
{
	return _columnDistance;
}

void Cartridge::setColumnDistance(const uint32_t &columnDistance)
{
	_columnDistance = columnDistance;
}

uint32_t Cartridge::adjustedCapacity() const
{
	return _adjustedCapacity;
}

void Cartridge::setAdjustedCapacity(const uint32_t &adjustedCapacity)
{
	_adjustedCapacity = adjustedCapacity;
}

double Cartridge::voltage() const
{
	return _voltage;
}

void Cartridge::setVoltage(double voltage)
{
	_voltage = voltage;
}

double Cartridge::pulseWarmingTemp() const
{
	return _pulseWarmingTemp;
}

void Cartridge::setPulseWarmingTemp(double pulseWarmingTemp)
{
	_pulseWarmingTemp = pulseWarmingTemp;
}

double Cartridge::pulseWidth() const
{
	return _pulseWidth;
}

void Cartridge::setPulseWidth(double pulseWidth)
{
	_pulseWidth = pulseWidth;
}

bool Cartridge::autoconfig() const
{
	return _autoconfig;
}

void Cartridge::setAutoconfig(bool autoconfig)
{
	_autoconfig = autoconfig;
}

bool Cartridge::pulseWarming() const
{
	return _pulseWarming;
}

void Cartridge::setPulseWarming(bool pulseWarming)
{
	_pulseWarming = pulseWarming;
}

void Cartridge::clear()
{
	_id.clear();
	_autoconfig		  = true;
	_pulseWarming     = false ;
	_voltage          = 0;
	_pulseWarmingTemp = 0;
	_columnDistance   = 0;
	_adjustedCapacity = 100;
	_pulseWidth       = 0;
}

void Cartridge::operator =(const Cartridge &other)
{
	_id				  = other._id;
	_autoconfig		  = other._autoconfig;
	_pulseWarming     = other._pulseWarming;
	_voltage          = other._voltage;
	_pulseWarmingTemp = other._pulseWarmingTemp;
	_columnDistance   = other._columnDistance;
	_adjustedCapacity = other._adjustedCapacity;
	_pulseWidth       = other._pulseWidth;
}

bool Cartridge::equal(const Cartridge &other) const
{
	bool equal = false;
	equal  = (_id.compare(other._id) == 0);
	equal &= (_autoconfig		== other._autoconfig);
	equal &= (_pulseWarming     == other._pulseWarming);
	equal &= (_columnDistance   == other._columnDistance);
	equal &= (_adjustedCapacity == other._adjustedCapacity);
	equal &= (static_cast<int>(_voltage          * 1000) == static_cast<int>(other._voltage			 * 1000));
	equal &= (static_cast<int>(_pulseWarmingTemp * 1000) == static_cast<int>(other._pulseWarmingTemp * 1000));
	equal &= (static_cast<int>(_pulseWidth       * 1000) == static_cast<int>(other._pulseWidth		 * 1000));

	return equal;
}
