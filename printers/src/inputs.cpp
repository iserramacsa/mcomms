#include "printer/inputs.h"

using namespace Macsa::Printers;

Input::Input(uint32_t id) :
	IOBase (id)
{}

Input::~Input()
{}

InputMode Input::mode() const
{
	return _mode;
}

void Input::setMode(const InputMode& mode)
{
	_mode = mode;
}

void Input::setMode(InputMode_n mode)
{
	_mode = mode;
}

void Input::setMode(const std::string &mode)
{
	_mode = mode;
}

bool Input::inverted() const
{
	return _inverted;
}

void Input::setInverted(bool inverted)
{
	_inverted = inverted;
}

uint32_t Input::filter() const
{
	return _filter;
}

void Input::setFilter(const uint32_t &filter)
{
	_filter = filter;
}

void Input::operator =(const Input &other)
{
	_id = other._id;
	_descriptor = other._descriptor;
	_value = other._value;
	_filter = other._filter;
	_mode = other._mode;
	_inverted = other._inverted;
}

bool Input::equal(const Input &other) const
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
