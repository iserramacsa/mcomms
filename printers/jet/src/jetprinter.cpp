#include "jet/jetprinter.h"
#include <sstream>
#include <typeinfo>
#include <iostream>

using namespace Macsa;
using namespace Macsa::Printers;



int JetPrinter::libraryVersionMajor()	  { return JET_LIBRARY_VERSION_MAJOR;}
int JetPrinter::libraryVersionMinor()	  { return JET_LIBRARY_VERSION_MINOR;}
int JetPrinter::libraryVersionRevision() { return JET_LIBRARY_VERSION_PATCH;}
std::string JetPrinter::libraryVersion() { return JET_LIBRARY_VERSION_STR;  }


JetPrinter::JetPrinter() :
	_mutex(new std::mutex())
{
	_type = "idjet";
}

JetPrinter::JetPrinter(const JetPrinter &other) :
	_mutex(new std::mutex())
{
	copy(other);
}

JetPrinter::~JetPrinter()
{
	if (_mutex) {
		delete _mutex;
	}
}

PrinterFiles *JetPrinter::files()
{
	return &_files;
}

const PrinterFiles *JetPrinter::files() const
{
	return &_files;
}

PrinterComms *JetPrinter::comms()
{
	return &_comms;
}

const PrinterComms *JetPrinter::comms() const
{
	return &_comms;
}

std::string JetPrinter::formatedDateTime() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return formatedDateTime(_dt);
}

std::string JetPrinter::formatedDateTime(time_t time) const
{
	std::stringstream dt;

	struct tm *date = localtime(&time);
	dt <<  date->tm_mday;
	dt << (date->tm_mon + 1);
	dt << (date->tm_year + 1900);
	dt <<  date->tm_hour;
	dt <<  date->tm_min;
	dt <<  date->tm_sec;

	return dt.str();
}

time_t JetPrinter::dateTimeFromString(const std::string& dt) const
{
	time_t rawtime;
	struct tm * timeInfo;

	time(&rawtime);
	timeInfo = localtime(&rawtime);

	if (dt.length() >= 8)
	{
		timeInfo->tm_mday = std::atoi(dt.substr(0, 2).c_str());
		timeInfo->tm_mon  = std::atoi(dt.substr(2, 2).c_str()) - 1;
		timeInfo->tm_year = std::atoi(dt.substr(4, 4).c_str()) - 1900;

		if (dt.length() >= 10)
		{
			timeInfo->tm_hour = std::atoi(dt.substr(8, 2).c_str());
		}
		else {
			timeInfo->tm_hour = 0;
		}
		if (dt.length() >= 12)
		{
			timeInfo->tm_min  = std::atoi(dt.substr(10, 2).c_str());
		}
		else{
			timeInfo->tm_min = 0;
		}
		if (dt.length() >= 14)
		{
			timeInfo->tm_sec  = std::atoi(dt.substr(12, 2).c_str());
		}
		else
		{
			timeInfo->tm_sec  = 0;
		}
		rawtime = mktime ( timeInfo );
	}

	return rawtime;
}

void JetPrinter::setDateTime(const time_t &dateTime)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return Printer::setDateTime(dateTime);
}

void JetPrinter::setDateTime(const std::string &formatedDatetime)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	time_t rawtime = dateTimeFromString(formatedDatetime);
	Printer::setDateTime(rawtime);
}

unsigned int JetPrinter::printheadTemperature(unsigned int id)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (_printheads.find(id) != _printheads.end()) {
		return _printheads.at(id).temperature();
	}
	return 0;
}

void JetPrinter::setPrintheadTemperature(unsigned int id, unsigned int temperature)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (_printheads.find(id) != _printheads.end()) {
		_printheads.at(id).setTemperature(temperature);
	}
}

unsigned int JetPrinter::tankLevel(unsigned int id)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (_inkTanks.find(id) != _inkTanks.end()) {
		return _inkTanks.at(id);
	}
	return 0;
}

void JetPrinter::setTankLevel(unsigned int id, unsigned int level)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (_inkTanks.find(id) == _inkTanks.end()) {
		_inkTanks.insert(std::pair<unsigned int, unsigned int>(id, level));
	}
	else {
		_inkTanks.at(id) = level;
	}
}

bool JetPrinter::paused() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
    return _paused;
}

void JetPrinter::setPause(bool paused)
{
	std::lock_guard<std::mutex>lock(*_mutex);
    _paused = paused;
}

bool JetPrinter::printStatus() const
{
	return _printStatus;
}

void JetPrinter::setPrintStatus(bool printStatus)
{
	_printStatus = printStatus;
}

JetMessagesManager &JetPrinter::messageManager()
{
	return _messageManager;
}

void JetPrinter::setMessageManager(const JetMessagesManager &manager)
{
	_messageManager = manager;
}

bool JetPrinter::equal(const Printer &other) const
{
	bool equal = false;

	return equal;
}

void JetPrinter::copy(const JetPrinter &other)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_type = other._type;

	_files = PrinterFiles();
	_files = other._files;
	_comms = other._comms;
}

