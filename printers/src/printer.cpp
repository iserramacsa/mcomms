#include "printer/printer.h"
#include <sstream>

using namespace Macsa;
using namespace Macsa::Printers;


Printer::Printer()
{
	_id = 0;
	_lastUpdate = time(nullptr);
	_dt = time(nullptr);
}

Printer::~Printer()
{}

std::string Printer::type() const {return _type;}

int Printer::id() const {return _id;}
void Printer::setId(int id) { _id = id;}

std::time_t Printer::dateTime() const
{
	time_t now = time(nullptr);
	double update = difftime(now, _lastUpdate);

	time_t dateTime = static_cast<time_t>(_dt + update);

	return dateTime;
}

void Printer::setDateTime(const std::time_t& dateTime)
{
	_dt = dateTime;
	_lastUpdate = time(nullptr);
}
