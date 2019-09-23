#include "printer/inputs.h"

using namespace Macsa::Printers;

Inputs::Inputs(uint32_t id) :
	IOBase (id)
{}

Inputs::~Inputs()
{}

InputMode_n Inputs::mode() const
{
	return _mode;
}

void Inputs::setMode(const InputMode_n &mode)
{
	_mode = mode;
}

bool Inputs::inverted() const
{
	return _inverted;
}

void Inputs::setInverted(bool inverted)
{
	_inverted = inverted;
}

uint32_t Inputs::filter() const
{
	return _filter;
}

void Inputs::setFilter(const uint32_t &filter)
{
	_filter = filter;
}

bool Inputs::equal(const Inputs &other) const
{
	bool eq = false;
	eq = (_id == other._id);
	eq &= (_descriptor.compare(other._descriptor) == 0);
	eq &= (_value == other._value);
	eq &= (_filter == other._filter);
	eq &= (_mode == other._mode);
	eq &= (_inverted == other._inverted);

	return eq;
}
