#include "tij/tijprinter.h"
#include <sstream>
#include <typeinfo>
#include <iostream>

using namespace Macsa;
using namespace Macsa::Printers;

#if __cplusplus >= 201103L
		using itBoard  = std::map<int, Board>::iterator;
		using citBoard = std::map<int, Board>::const_iterator;
#else
		typedef std::map<int, Board>::iterator		itBoard;
		typedef std::map<int, Board>::const_iterator	citBoard;
#endif

TIJPrinter::TIJPrinter()
{
	_type = "SM200";
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
	std::vector<Board> list;
	for (citBoard it = _boards.begin(); it != _boards.end(); it++) {
		list.push_back(it->second);
	}
	return list;
}

Board* TIJPrinter::board(int id)
{
	if (_boards.find(id) != _boards.end()) {
		return &(_boards[id]);
	}
	return nullptr;
}

const Board * TIJPrinter::board(int id) const
{
	if (_boards.find(id) != _boards.end()) {
		return  std::move(&_boards.at(id));
	}
	return nullptr;
}

void TIJPrinter::setBoard(const Board &board)
{
	if (_boards.find(board.id()) != _boards.end()) {
		Board& printerBoard = _boards[board.id()];
		printerBoard = board;
	}
	else {
		_boards.insert(std::pair<int, Board>(board.id(), board));
	}
}

void TIJPrinter::setBoards(const std::vector<Board> &boards)
{
	_boards.clear();
	for (unsigned long i = 0; i < boards.size(); i++) {
		_boards.insert(std::pair<int, Board>(boards.at(i).id(), boards.at(i)));
	}
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
