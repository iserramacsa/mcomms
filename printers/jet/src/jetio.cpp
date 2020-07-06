#include "jet/jetio.h"

using namespace Macsa::Printers;

JetIO::JetIO(const std::string &id) :
	_id(id)
{
	_value = false;
}

JetIO::JetIO(const JetIO &other) :
	_id(other._id)
{
	_value = other._value;
}

std::string JetIO::id() const
{
	return _id;
}

bool JetIO::value() const
{
	return _value;
}

void JetIO::setValue(bool value)
{
	_value = value;
}

JetIO &JetIO::operator = (const JetIO &other)
{
	if (_id == other._id) {
		_value = other._value;
	}
	return *this;
}

bool JetIO::equal(const JetIO &other) const
{
	return (_id == other._id && _value == other._value);
}
