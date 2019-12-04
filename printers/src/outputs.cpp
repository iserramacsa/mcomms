#include "printer/outputs.h"
using namespace Macsa::Printers;

Output::Output(uint32_t id) : IOBase (id)
{}

Output::~Output()
{}

bool Output::initialValue() const
{
	return _initialValue;
}

void Output::setInitialValue(bool initialValue)
{
	_initialValue = initialValue;
}

OutputType Output::type() const
{
	return _type;
}

void Output::setType(const OutputType &type)
{
	_type = type;
}

void Output::setType(OutputType_n type)
{
	_type = type;
}

void Output::setType(const std::string &type)
{
	_type = type;
}

uint32_t Output::time() const
{
	return _time;
}

void Output::setTime(const uint32_t &time)
{
	_time = time;
}

void Output::operator =(const Output &other)
{
	_id = other._id;
	_descriptor = other._descriptor;
	_value = other._value;
	_time = other._time;
	_type = other._type;
	_initialValue = other._initialValue;
}

bool Output::equal(const Output &other) const
{
	bool eq = false;
	eq = (_id == other._id);
	eq &= (_descriptor.compare(other._descriptor) == 0);
	eq &= (_value == other._value);
	eq &= (_time == other._time);
	eq &= (_type == other._type);
	eq &= (_initialValue == other._initialValue);

	return eq;
}
