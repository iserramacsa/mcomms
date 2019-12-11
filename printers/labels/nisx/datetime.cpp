#include "nisx/datetime.h"

using namespace Macsa::Nisx;

DateTime::DateTime(const std::string &format)
{
	clear();
	_format = format;
}

DateTime::DateTime(const std::string &format, int dayOffset, int monthOffset, int yearOffset, uint8_t startOfDay)
{
	_format = format;
	_dayOffset = dayOffset;
	_monthOffset = monthOffset;
	_yearOffset = yearOffset;
	_startOfDay = startOfDay;
}

DateTime::~DateTime()
{}

std::string DateTime::format() const
{
	return _format;
}

void DateTime::setFormat(const std::string &format)
{
	_format = format;
}

int DateTime::dayOffset() const
{
	return _dayOffset;
}

void DateTime::setDayOffset(int dayOffset)
{
	_dayOffset = dayOffset;
}

int DateTime::monthOffset() const
{
	return _monthOffset;
}

void DateTime::setMonthOffset(int MonthOffset)
{
	_monthOffset = MonthOffset;
}

int DateTime::yearOffset() const
{
	return _yearOffset;
}

void DateTime::setYearOffset(int yearOffset)
{
	_yearOffset = yearOffset;
}

uint8_t DateTime::startOfDay() const
{
	return _startOfDay;
}

void DateTime::setStartOfDay(const uint8_t &startOfDay)
{
	_startOfDay = startOfDay;
}

void Macsa::Nisx::DateTime::clear()
{
	_format = "";
	_dayOffset = 0;
	_monthOffset = 0;
	_yearOffset = 0;
	_startOfDay = 0;
}

void DateTime::copy(const DateTime &other)
{
	_format      = other._format;
	_dayOffset   = other._dayOffset;
	_monthOffset = other._monthOffset;
	_yearOffset  = other._yearOffset;
	_startOfDay  = other._startOfDay;
}

bool DateTime::compare(const DateTime &other)
{
	bool equal = false;
	equal = _format.compare(other._format) == 0;
	equal &= _dayOffset   == other._dayOffset;
	equal &= _monthOffset == other._monthOffset;
	equal &= _yearOffset  == other._yearOffset;
	equal &= _startOfDay  == other._startOfDay;

	return equal;
}
