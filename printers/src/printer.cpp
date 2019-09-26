#include "printer/printer.h"
#include <sstream>

using namespace Macsa;
using namespace Macsa::Printers;


Printer::Printer() :
	_status(_configuration)
{
	_id = 0;
	_statusChanged = false;
	_configChanged = false;
	_filesChanged = false;
	_fontsChanged = false;
	_errorsChanged = false;
	_dateTime = 0;
	_lastUpdate = 0;
}

Printer::~Printer()
{}

std::string Printer::type() const {return _type;}

int Printer::id() const {return _id;}
void Printer::setId(int id) { _id = id;}

bool Printer::statusChanged() const {return _statusChanged;}
void Printer::setStatusChanged(bool changed){_statusChanged = changed;}

bool Printer::configChanged() const {return _configChanged;}
void Printer::setConfigChanged(bool changed){_configChanged = changed;}

bool Printer::filesChanged() const {return _filesChanged;}
void Printer::setFilesChanged(bool changed) {_filesChanged = changed;}

bool Printer::fontsChanged() const {return _fontsChanged;}
void Printer::setFontsChanged(bool changed) {_fontsChanged = changed;}

bool Printer::errorsChanged() const {return _errorsChanged;}
void Printer::setErrorsChanged(bool changed) {_errorsChanged = changed;}

std::time_t Printer::dateTime() const
{
	double diff = difftime(_lastUpdate, time(nullptr));
	return (_dateTime + static_cast<long>(diff));
}

std::string Printer::formatedDateTime() const
{
	std::stringstream dt;
	std::time_t time = dateTime();

	struct tm *date = localtime(&time);
	dt <<  date->tm_mday;
	dt << (date->tm_mon + 1);
	dt << (date->tm_year + 1900);
	dt <<  date->tm_hour;
	dt <<  date->tm_min;
	dt <<  date->tm_sec;

	return dt.str();
}
void Printer::setDateTime(const time_t &dateTime)
{
	_dateTime = dateTime;
	_lastUpdate = time(nullptr);
}

Configuration& Printer::configuration()
{
	return _configuration;
}

const Configuration& Printer::configuration() const
{
	return _configuration;
}

Status& Printer::status()
{
	return _status;
}

const Status& Printer::status() const
{
	return _status;
}

PrinterFiles& Printer::files()
{
	return _files;
}

const PrinterFiles& Printer::files() const
{
	return _files;
}

PrinterComms& Printer::comms()
{
	return _comms;
}

const PrinterComms &Printer::comms() const
{
	return _comms;
}
