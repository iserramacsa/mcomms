#include "jet/jetprinter.h"
#include <sstream>
#include <typeinfo>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace Macsa;
using namespace Macsa::Printers;

int JetPrinter::jetLibraryVersionMajor()	 { return JET_LIBRARY_VERSION_MAJOR;}
int JetPrinter::jetLibraryVersionMinor()	 { return JET_LIBRARY_VERSION_MINOR;}
int JetPrinter::jetLibraryVersionRevision()  { return JET_LIBRARY_VERSION_PATCH;}
std::string JetPrinter::jetLibraryVersion()  { return JET_LIBRARY_VERSION_STR;  }

JetPrinter::JetPrinter() :
	_mutex(new std::mutex())
{
	_type = "idjet";
	_logs.clear();
	_librariesVersions.clear();
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
	dt << std::setfill ('0') << std::setw (2) << date->tm_mday;
	dt << std::setfill ('0') << std::setw (2) << (date->tm_mon + 1);
	dt << (date->tm_year + 1900);
	dt << std::setfill ('0') << std::setw (2) <<  date->tm_hour;
	dt << std::setfill ('0') << std::setw (2) <<  date->tm_min;
	dt << std::setfill ('0') << std::setw (2) <<  date->tm_sec;
	std::string formated = dt.str();
	return formated;
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

std::string JetPrinter::getLibraryVersion(const std::string &library) const
{
	if (_librariesVersions.find(library) != _librariesVersions.end()){
		return _librariesVersions.at(library);
	}
	return "";
}

std::map<std::string, std::string> JetPrinter::getLibrariesVersions() const
{
	return _librariesVersions;
}

void JetPrinter::clearLibrariesVersions()
{
	_librariesVersions.clear();
}

void JetPrinter::setLibrariesVersions(const std::map<std::string, std::string> &librariesVersions)
{
	_librariesVersions = librariesVersions;
}

void JetPrinter::setLibraryVersion(const std::string &library, const std::string &version)
{
	if (_librariesVersions.find(library) != _librariesVersions.end()){
		 _librariesVersions[library] = version;
	}
	else {
		_librariesVersions.insert(std::pair<std::string, std::string>(library, version));
	}
}

std::vector<unsigned int> JetPrinter::printheads() const
{
	std::vector<unsigned int> printheads;
	std::lock_guard<std::mutex>lock(*_mutex);
	for (auto & ph : _printheads){
		printheads.push_back(ph.first);
	}
	return printheads;
}

JetPrinthead JetPrinter::printhead(unsigned int id) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	if (_printheads.find(id) != _printheads.end()) {
		return _printheads.at(id);
	}
	return JetPrinthead(id);
}

void JetPrinter::setPrinthead(const JetPrinthead ph)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	std::map<unsigned int, JetPrinthead>::iterator it = _printheads.find(ph.id());
	if (it != _printheads.end()) {
		it->second = ph;
	}
	else {
		_printheads.insert(std::pair<unsigned int, JetPrinthead>(ph.id(), ph));
	}
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

JetPrinter::tanksMap JetPrinter::inkTanks() const
{
	return _inkTanks;
}

unsigned int JetPrinter::tankLevel(unsigned int id) const
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
	std::lock_guard<std::mutex>lock(*_mutex);
	return _printStatus;
}

void JetPrinter::setPrintStatus(bool printStatus)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_printStatus = printStatus;
}

JetMessagesManager &JetPrinter::messageManager()
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _messageManager;
}

const JetMessagesManager &JetPrinter::messageManager() const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	return _messageManager;
}

void JetPrinter::setMessageManager(const JetMessagesManager &manager)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_messageManager = manager;
}

bool JetPrinter::inputEnabled(const std::string &boardType, unsigned int boardNum, const std::string &inputId) const
{
	std::lock_guard<std::mutex>lock(*_mutex);

	std::vector<JetBoard>::const_iterator itBoard = getBoard(boardType, boardNum);
	if (itBoard != _boards.end()) {
		return itBoard->input(inputId);
	}
	return false;
}

void JetPrinter::setInputs(const std::string &boardType, unsigned int boardNum, const std::map<std::string, bool>& inputs)
{
	std::lock_guard<std::mutex>lock(*_mutex);

	std::vector<JetBoard>::iterator itBoard = getBoard(boardType, boardNum);
	if (itBoard != _boards.end()) {
		JetBoard& board = *itBoard;
		board.setInputs(inputs);
	}
}

JetBoard JetPrinter::board(const std::string &boardType, unsigned int boardNum) const
{
	std::vector<JetBoard>::const_iterator itBoard = getBoard(boardType, boardNum);
	if (itBoard != _boards.end()) {
		return *itBoard;
	}
	return JetBoard(boardType, boardNum);
}

JetBoard JetPrinter::board(JetBoardType boardType, unsigned int boardNum) const
{
	std::vector<JetBoard>::const_iterator itBoard = getBoard(boardType, boardNum);
	if (itBoard != _boards.end()) {
		return *itBoard;
	}
	return JetBoard(boardType, boardNum);
}

void JetPrinter::setBoard(const JetBoard &board)
{
	std::vector<JetBoard>::iterator itBoard = getBoard(board.type(), board.number());
	if (itBoard != _boards.end()) {
		*itBoard = board;
	}
	else {
		_boards.push_back(board);
	}
}

std::vector<JetIO> JetPrinter::outputs() const
{
	return _outputs;
}

bool JetPrinter::outputEnabled(const std::string &outputId) const
{
	std::lock_guard<std::mutex>lock(*_mutex);
	for (unsigned int o = 0; o < _outputs.size(); o++) {
		if (_outputs.at(o).id() == outputId) {
			return _outputs.at(o).value();
		}
	}
	return false;
}

void JetPrinter::setOutputs(const std::vector<JetIO> &outputs)
{
	std::lock_guard<std::mutex>lock(*_mutex);
	_outputs = outputs;
}

bool JetPrinter::isInError() const
{
	return _isInError;
}

void JetPrinter::setIsInError(bool isInError)
{
	_isInError = isInError;
}

void JetPrinter::updateLogs(std::list<LogItem>logs)
{
	if (logs.size()){
		logs.sort();

		time_t firstNewLog = logs.begin()->timestamp();
		for (std::list<LogItem>::iterator it = _logs.begin(); it != _logs.end(); it++) {
			if (it->timestamp() >= firstNewLog) {
				_logs.erase(it, _logs.end());
				break;
			}
		}
		_logs.insert(_logs.end(), logs.begin(), logs.end());
	}
}

JetPrinter::logsList JetPrinter::logs(time_t from, time_t to) const
{

	std::list<LogItem> list;
	if (from < to && _logs.size()){
		std::list<LogItem>::const_iterator first = _logs.begin();
		std::list<LogItem>::const_iterator last = std::prev(_logs.end());
		while (first != _logs.end() && first->timestamp() < from){
			first++;
		}
		while (std::distance(first, last) > 0 && last->timestamp() > to) {
			last--;
		}
		list.assign(first, last);
	}
	return list;
}

JetPrinter::logsList JetPrinter::logs() const
{
	return _logs;
}

PrintDirection JetPrinter::printDir() const
{
	return _printDir;
}

void JetPrinter::setPrintDir(const PrintDirection &printDir)
{
	_printDir = printDir;
}

uint64_t JetPrinter::sscc() const
{
	return _sscc;
}

void JetPrinter::setSscc(uint64_t sscc)
{
	_sscc = sscc;
}

bool JetPrinter::bitmapInverted() const
{
	return _bmpInverted;
}

void JetPrinter::setBitmapInverted(bool bmpInverted)
{
	_bmpInverted = bmpInverted;
}

std::vector<JetBoard>::iterator JetPrinter::getBoard(JetBoardType boardType, unsigned int boardNum)
{
	auto search = [&](const JetBoard& board)
	{
		return board.type() == boardType && board.number() == boardNum;
	};

	return std::find_if(_boards.begin(), _boards.end(), search);
}

std::vector<JetBoard>::const_iterator JetPrinter::getBoard(JetBoardType boardType, unsigned int boardNum) const
{
	auto search = [&](const JetBoard& board)
	{
		return board.type() == boardType && board.number() == boardNum;
	};

	return std::find_if(_boards.begin(), _boards.end(), search);
}

bool JetPrinter::equal(const Printer &other) const
{
	try {
		const JetPrinter& printer = dynamic_cast<const JetPrinter&>(other);
		//todo
		if (_comms				!= printer._comms)				{return false;}
		if (_printheads			!= printer._printheads)			{return false;}
		if (_inkTanks			!= printer._inkTanks)			{return false;}
		if (_boards				!= printer._boards)				{return false;}
		if (_outputs			!= printer._outputs)			{return false;}
		if (_messageManager		!= printer._messageManager)		{return false;}
		if (_paused				!= printer._paused)				{return false;}
		if (_printStatus		!= printer._printStatus)		{return false;}
		if (_librariesVersions	!= printer._librariesVersions)	{return false;}

		return true;
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return false;
}

void JetPrinter::copy(const JetPrinter &other)
{
	std::lock_guard<std::mutex>lock(*_mutex);

	_type = other._type;
	_files = PrinterFiles();
	_files = other._files;
	_comms = other._comms;
	_printheads = other._printheads;
	_inkTanks = other._inkTanks;
	_boards = other._boards;
	_outputs = other._outputs;
	_messageManager = other._messageManager;
	_paused	= other._paused;
	_printStatus = other._printStatus;
	_logs = other._logs;
	_librariesVersions = other._librariesVersions;
}


