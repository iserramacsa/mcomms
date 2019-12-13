#include "printer/outputs.h"
#include <typeinfo>
#include <iostream>

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

bool Output::equal(const IOBase &other) const
{
	bool equal = false;
	try {
		Output output = dynamic_cast<const Output&>(other);
		equal = (_id == output._id);
		equal &= (_descriptor.compare(output._descriptor) == 0);
		equal &= (_value == output._value);
		equal &= (_time == output._time);
		equal &= (_type == output._type);
		equal &= (_initialValue == output._initialValue);
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<" Caught bad cast" << std::endl;
	}
	return equal;
}

void Output::copy(const IOBase &other)
{
	try {
		Output output = dynamic_cast<const Output&>(other);
		_id = output._id;
		_descriptor = output._descriptor;
		_value = output._value;
		_time = output._time;
		_type = output._type;
		_initialValue = output._initialValue;
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<" Caught bad cast" << std::endl;
	}
}

