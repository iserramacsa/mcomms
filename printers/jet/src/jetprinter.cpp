#include "jet/jetprinter.h"
#include <sstream>
#include <typeinfo>
#include <iostream>

using namespace Macsa;
using namespace Macsa::Printers;

#if __cplusplus >= 201103L
		using itBoard  = std::vector<Printers::Board>::iterator;
		using citBoard = std::vector<Printers::Board>::const_iterator;
#else
		typedef std::vector<Printers::Board>::iterator			itBoard;
		typedef std::vector<Printers::Board>::const_iterator	citBoard;
#endif


int JetPrinter::libraryVersionMajor()	  { return JET_LIBRARY_VERSION_MAJOR;}
int JetPrinter::libraryVersionMinor()	  { return JET_LIBRARY_VERSION_MINOR;}
int JetPrinter::libraryVersionRevision() { return JET_LIBRARY_VERSION_PATCH;}
std::string JetPrinter::libraryVersion() { return JET_LIBRARY_VERSION_STR;  }


JetPrinter::JetPrinter() :
	_mutex(new std::mutex())
{
	_type = "SM200";
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

time_t JetPrinter::dateTimeFromString(std::string dt) const
{
	time_t rawtime;
	struct tm * timeInfo;

	time(&rawtime);
	timeInfo = localtime(&rawtime);

	if (dt.length() == 14)
	{
		timeInfo->tm_mday = std::atoi(dt.substr(0, 2).c_str());
		timeInfo->tm_mon  = std::atoi(dt.substr(2, 2).c_str()) - 1;
		timeInfo->tm_year = std::atoi(dt.substr(4, 4).c_str()) - 1900;
		timeInfo->tm_hour = std::atoi(dt.substr(8, 2).c_str());
		timeInfo->tm_min  = std::atoi(dt.substr(10, 2).c_str());
		timeInfo->tm_sec  = std::atoi(dt.substr(12, 2).c_str());
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
	time_t rawtime;
	struct tm * timeInfo;

	time(&rawtime);
	timeInfo = localtime(&rawtime);

	if (formatedDatetime.length() == 14)
	{
		timeInfo->tm_mday = std::atoi(formatedDatetime.substr(0, 2).c_str());
		timeInfo->tm_mon  = std::atoi(formatedDatetime.substr(2, 2).c_str()) - 1;
		timeInfo->tm_year = std::atoi(formatedDatetime.substr(4, 4).c_str()) - 1900;
		timeInfo->tm_hour = std::atoi(formatedDatetime.substr(8, 2).c_str());
		timeInfo->tm_min  = std::atoi(formatedDatetime.substr(10, 2).c_str());
		timeInfo->tm_sec  = std::atoi(formatedDatetime.substr(12, 2).c_str());
		rawtime = mktime ( timeInfo );
		Printer::setDateTime(rawtime);
	}
}

std::string JetPrinter::controllerVersion() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _controllerVersion;
}

std::string JetPrinter::apiVersion() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _apiVersion;
}

std::string JetPrinter::fpgaVersion() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _fpgaVersion;
}

void JetPrinter::setVersions(const std::string &controllerVersion, const std::string &apiVersion, const std::string &fpgaVersion)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_controllerVersion = controllerVersion;
	_apiVersion = apiVersion;
	_fpgaVersion = fpgaVersion;
}

DateCodes JetPrinter::dateCodes() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _dateCodes;
}

void JetPrinter::setDateCodes(const DateCodes &dateCodes)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_dateCodes = dateCodes;
}

std::vector<Board> JetPrinter::boards() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _boards;
}

Board* JetPrinter::board(int id)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	Board* board = nullptr;
	for (unsigned int i = 0; i < _boards.size(); i++) {
		if (_boards.at(i).id() == id){
			board = &_boards[i];
			break;
		}
	}
	return board;
}

const Board * JetPrinter::board(int id) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	const Board* board = nullptr;
	for (unsigned int i = 0; i < _boards.size(); i++) {
		if (_boards.at(i).id() == id){
			board = &_boards.at(i);
			break;
		}
	}
	return board;
}

void JetPrinter::setBoard(const Board &board)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	for (unsigned int i = 0; i < _boards.size(); i++) {
		if (_boards.at(i).id() == board.id()){
			_boards[i] = board;
			break;
		}
	}

}

void JetPrinter::setBoards(const std::vector<Board> &boards)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_boards = boards;
	for (std::vector<Board>::iterator board = _boards.begin(); board != _boards.end(); board++) {
//		board->setParent(this);
	}
}

std::vector<Error> JetPrinter::errorsLog() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _errorsLog;
}

void JetPrinter::setErrorsLog(const std::vector<Error> &errorsLog)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_errorsLog = errorsLog;
}

bool JetPrinter::logsEnabled() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _traceLogs;
}

void JetPrinter::setlogsEnabled(bool enable)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_traceLogs = enable;
}

bool JetPrinter::logComsEnabled() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return  _traceComms;
}

void JetPrinter::setlogComsEnabled(bool enable)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_traceComms = enable;
}

LoggerLevel JetPrinter::loggerLevel() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _logLevel;
}

void JetPrinter::setloggerLevel(const LoggerLevel &logLevel)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_logLevel = logLevel;
}

void JetPrinter::setloggerLevel(const std::string &logLevel)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_logLevel = logLevel;
}

bool JetPrinter::equal(const Printer &other) const
{
	bool equal = false;

	try {
		const JetPrinter& printer = dynamic_cast<const JetPrinter&>(other);
		//TODO
		equal = (_dateCodes == printer._dateCodes);
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return equal;
}

void JetPrinter::copy(const JetPrinter &other)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_type = other._type;

	_files = PrinterFiles();
	_files = other._files;
	_comms = other._comms;

	_controllerVersion = other._controllerVersion;
	_apiVersion = other._apiVersion;
	_fpgaVersion = other._fpgaVersion;
	_dateCodes = other._dateCodes;

	_boards.assign(other._boards.begin(), other._boards.end());
	_logLevel = other._logLevel;
	_traceLogs = other._traceLogs;
	_traceComms = other._traceComms;
}

