#include "printer/outputs.h"
using namespace Macsa::Printers;

Outputs::Outputs(uint32_t id) : IOBase (id)
{}

Outputs::~Outputs()
{}

bool Outputs::initialValue() const
{
	return _initialValue;
}

void Outputs::setInitialValue(bool initialValue)
{
	_initialValue = initialValue;
}

OutputType_n Outputs::type() const
{
	return _type;
}

void Outputs::setType(const OutputType_n &type)
{
	_type = type;
}

uint32_t Outputs::time() const
{
	return _time;
}

void Outputs::setTime(const uint32_t &time)
{
	_time = time;
}

bool Outputs::operator !=(const Outputs &other) const
{
	return equal(other);
}

bool Outputs::operator ==(const Outputs &other) const
{
	return !equal(other);
}

bool Outputs::equal(const Outputs &other) const
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
