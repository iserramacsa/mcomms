#include "printer/errors.h"
using namespace Macsa::Printers;

Error::Error()
{
	clear();
}

Error::Error(time_t timestamp, ErrorType type, ErrorCode code, unsigned int priority)
{
	_timestamp = timestamp;
	_type = type;
	_code = code;
	_priority = priority;
}

Error::~Error()
{}

time_t Error::timestamp() const
{
	return _timestamp;
}

void Error::setTimestamp(const time_t &value)
{
	_timestamp = value;
}

ErrorType Error::type() const
{
	return _type;
}

void Error::setType(const ErrorType &type)
{
	_type = type;
}

ErrorCode Error::code() const
{
	return _code;
}

void Error::setCode(const ErrorCode &code)
{
	_code = code;
}

unsigned int Error::priority() const
{
	return _priority;
}

void Error::setPriority(unsigned int priority)
{
	_priority = priority;
}

void Error::clear()
{
	_timestamp = time(nullptr);
	_type = ErrorType_n::INVALID;
	_code = ErrorCode_n::UNKOWN_ERROR;
	_priority = 0;
}

void Error::operator =(const Error &other)
{
	_timestamp = other._timestamp;
	_type = other._type;
	_code = other._code;
	_priority = other._priority;
}

bool Error::equal(const Error &other) const
{
	bool equal = false;

	equal = (_timestamp == other._timestamp);
	equal &= (_type == other._type);
	equal &= (_code == other._code);
	equal &= (_priority == other._priority);

	return equal;
}