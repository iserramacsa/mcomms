#include "printer/iobase.h"

using namespace Macsa::Printers;

IOBase::IOBase(uint32_t id) :
	_id(id)
{}

IOBase::~IOBase()
{}

uint32_t IOBase::id() const
{
    return _id;
}

std::string IOBase::descriptor() const
{
    return _descriptor;
}

void IOBase::setDescriptor(const std::string &descriptor)
{
    _descriptor = descriptor;
}

bool IOBase::value() const
{
    return _value;
}

void IOBase::setValue(bool value)
{
	_value = value;
}

bool IOBase::operator < (const IOBase &other) const
{
	return (_id < other._id);
}

bool IOBase::operator > (const IOBase &other) const
{
	return (_id > other._id);
}
