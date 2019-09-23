#include "printer/status.h"

using namespace Macsa;
using namespace Macsa::Printers;

Status::Status(const Configuration &config):
	_config(config)
{}

Status::~Status()
{}

int Status::dateTime() const
{
    return _dateTime;
}

void Status::setDateTime(int dateTime)
{
    _dateTime = dateTime;
}
