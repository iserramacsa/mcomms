#include "printer/inputs.h"
#include <typeinfo>
#include <iostream>

using namespace Macsa::Printers;

Input::Input(uint32_t id) :
	IOBase (id)
{}

InputMode Input::mode() const
{
	return _mode;
}

void Input::setMode(const InputMode& mode)
{
	_mode = mode;
}

void Input::setMode(nInputMode mode)
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

bool Input::equal(const IOBase &other) const
{
	bool equal = false;
	try {
		Input input = dynamic_cast<const Input&>(other);
		equal = (_id == input._id);
		equal &= (_descriptor.compare(input._descriptor) == 0);
		equal &= (_value == input._value);
		equal &= (_filter == input._filter);
		equal &= (_mode == input._mode);
		equal &= (_inverted == input._inverted);
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<" Caught bad cast" << std::endl;
	}
	return equal;
}

void Input::copy(const IOBase &other)
{
	try {
		Input input = dynamic_cast<const Input&>(other);
		_id = input._id;
		_descriptor = input._descriptor;
		_value = input._value;
		_filter = input._filter;
		_mode = input._mode;
		_inverted = input._inverted;
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<" Caught bad cast" << std::endl;
	}
}


