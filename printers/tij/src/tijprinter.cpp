#include "tij/tijprinter.h"
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

TIJPrinter::TIJPrinter()
{
	_type = "SM200";
}

TIJPrinter::TIJPrinter(const TIJPrinter &other)
{
	copy(other);
}

TIJPrinter::~TIJPrinter()
{}

PrinterFiles *TIJPrinter::files()
{
	return &_files;
}

const PrinterFiles *TIJPrinter::files() const
{
	return &_files;
}

PrinterComms *TIJPrinter::comms()
{
	return &_comms;
}

const PrinterComms *TIJPrinter::comms() const
{
	return &_comms;
}

std::string TIJPrinter::formatedDateTime() const
{
	return formatedDateTime(_dt);
}

std::string TIJPrinter::formatedDateTime(time_t time) const
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

time_t TIJPrinter::dateTimeFromString(std::string dt) const
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

void TIJPrinter::setDateTime(const time_t &dateTime)
{
	return Printer::setDateTime(dateTime);
}

void TIJPrinter::setDateTime(const std::string &formatedDatetime)
{
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

std::string TIJPrinter::controllerVersion() const {return _controllerVersion;}
std::string TIJPrinter::apiVersion() const {return _apiVersion;}
std::string TIJPrinter::fpgaVersion() const {return _fpgaVersion;}

void TIJPrinter::setVersions(const std::string &controllerVersion, const std::string &apiVersion, const std::string &fpgaVersion)
{
	_controllerVersion = controllerVersion;
	_apiVersion = apiVersion;
	_fpgaVersion = fpgaVersion;
}

DateCodes TIJPrinter::dateCodes() const
{
	return _dateCodes;
}

void TIJPrinter::setDateCodes(const DateCodes &dateCodes)
{
	_dateCodes = dateCodes;
}

std::vector<Board> TIJPrinter::boards() const
{
	return _boards;
}

Board* TIJPrinter::board(int id)
{
	Board* board = nullptr;
	for (unsigned int i = 0; i < _boards.size(); i++) {
		if (_boards.at(i).id() == id){
			board = &_boards[i];
			break;
		}
	}
	return board;
}

const Board * TIJPrinter::board(int id) const
{
	const Board* board = nullptr;
	for (unsigned int i = 0; i < _boards.size(); i++) {
		if (_boards.at(i).id() == id){
			board = &_boards.at(i);
			break;
		}
	}
	return board;
}

void TIJPrinter::setBoard(const Board &board)
{
	for (unsigned int i = 0; i < _boards.size(); i++) {
		if (_boards.at(i).id() == board.id()){
			_boards[i] = board;
			break;
		}
	}

}

void TIJPrinter::setBoards(const std::vector<Board> &boards)
{
	_boards = boards;
}

std::vector<Error> TIJPrinter::errorsLog() const
{
	return _errorsLog;
}

void TIJPrinter::setErrorsLog(const std::vector<Error> &errorsLog)
{
	_errorsLog = errorsLog;
}

bool TIJPrinter::logsEnabled() const
{
	return _traceLogs;
}

void TIJPrinter::setlogsEnabled(bool enable)
{
	_traceLogs = enable;
}

bool TIJPrinter::logComsEnabled() const
{
	return  _traceComms;
}

void TIJPrinter::setlogComsEnabled(bool enable)
{
	_traceComms = enable;
}

LoggerLevel TIJPrinter::loggerLevel() const
{
	return _logLevel;
}

void TIJPrinter::setloggerLevel(const LoggerLevel &logLevel)
{
	_logLevel = logLevel;
}

void TIJPrinter::setloggerLevel(const std::string &logLevel)
{
	_logLevel = logLevel;
}

bool TIJPrinter::equal(const Printer &other) const
{
	bool equal = false;

	try {
		const TIJPrinter& printer = dynamic_cast<const TIJPrinter&>(other);

		equal = (_dateCodes == printer._dateCodes);
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return equal;
}

void TIJPrinter::copy(const TIJPrinter &other)
{
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
