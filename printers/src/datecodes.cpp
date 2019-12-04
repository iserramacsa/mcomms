#include "printer/datecodes.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>

#define MIN_CODE_FORMATER_LENGTH 6	//[DC:H]
using namespace Macsa::Printers;
using namespace Macsa::Printers::MDateCode;

DCInterval::DCInterval(std::string format)
{
	_format = format;
}

void DCInterval::setValue(std::string value)
{
	if (formatIs(CODE_FORMAT_MINUTE)){
		minute = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_HOUR)){
		hour = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_DOM)){
		dayOfMonth = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_DOW)){
		dayOfWeek = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_DOY)){
		dayOfYear = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_WOY)){
		weekOfYear = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_MONTH)){
		month = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_YEAR)){
		year = std::atoi(value.c_str());
	}
	else if (formatIs(CODE_FORMAT_SHIFT)){
		std::size_t d = value.find_first_of(".");
		std::size_t h = value.find_first_of(":");
		if ((d != std::string::npos) && (h != std::string::npos)){
			std::string dow = value.substr(0,d);
			std::string hh = value.substr(d+1,(h-d));
			std::string mm = value.substr(h+1);
			dayOfWeek = std::atoi(dow.c_str());
			hour = std::atoi(hh.c_str());
			minute = std::atoi(mm.c_str());
		}
	}
}

std::string DCInterval::getValue() const
{
	std::string out;
	if (formatIs(CODE_FORMAT_MINUTE)){
		out = toString(minute,2,'0');
	}
	else if (formatIs(CODE_FORMAT_HOUR)){
		out = toString(hour,2,'0');
	}
	else if (formatIs(CODE_FORMAT_DOM)){
		out = toString(dayOfMonth,2,'0');
	}
	else if (formatIs(CODE_FORMAT_DOW)){
		out = toString(dayOfWeek,2,'0');
	}
	else if (formatIs(CODE_FORMAT_DOY)){
		out = toString(dayOfYear,3,'0');
	}
	else if (formatIs(CODE_FORMAT_WOY)){
		out = toString(weekOfYear,2,'0');
	}
	else if (formatIs(CODE_FORMAT_MONTH)){
		out = toString(month,2,'0');
	}
	else if (formatIs(CODE_FORMAT_YEAR)){
		out = toString(year,4,'0');
	}
	else if (formatIs(CODE_FORMAT_SHIFT)){
		std::stringstream ss;
		std::string dow = toString(dayOfWeek);
		std::string hh = toString(hour,2,'0');
		std::string mm = toString(minute,2,'0');
		ss << dow << "." << hh << ":" << mm;
		out = ss.str();
	}
	return out;
}

int DCInterval::getMinute() const{return minute;}
int DCInterval::getHour() const{return hour;}
int DCInterval::getDayOfMonth() const{return dayOfMonth;}
int DCInterval::getDayOfWeek() const{return dayOfWeek;}
int DCInterval::getJulianDay() const{return dayOfYear;}
int DCInterval::getWeekOfYear() const{return weekOfYear;}
int DCInterval::getMonth() const{return month;}
int DCInterval::getYear() const{return year;}

void DCInterval::operator =(const DCInterval &other)
{
	copy(other);
}

bool DCInterval::operator <(const tm dateTime) const
{
	return  !greaterThan(dateTime);
}

bool DCInterval::operator >(const tm dateTime) const
{
	return greaterThan(dateTime);
}

void DCInterval::copy(const DCInterval &other)
{
	_format = other._format;
	minute = other.minute;
	hour = other.hour;
	dayOfMonth = other.dayOfMonth;
	dayOfWeek = other.dayOfWeek;
	dayOfYear = other.dayOfYear; //Julian day
	weekOfYear = other.weekOfYear;
	month = other.month;
	year = other.year;
}


bool DCInterval::formatIs(std::string format)const
{
	return (_format.compare(format) == 0);
}

bool DCInterval::greaterThan(const tm dateTime) const
{
	bool gt = false;

	if (formatIs(CODE_FORMAT_MINUTE)){
		gt = minute > dateTime.tm_min;
	}
	else if (formatIs(CODE_FORMAT_HOUR)){
		gt = hour > dateTime.tm_hour;
	}
	else if (formatIs(CODE_FORMAT_DOM)){
		gt = dayOfMonth > dateTime.tm_mday;
	}
	else if (formatIs(CODE_FORMAT_DOW)){
		int day = ((dateTime.tm_wday - 1) >= 0) ? (dateTime.tm_wday - 1) : 6;
		gt = dayOfWeek > day;
	}
	else if (formatIs(CODE_FORMAT_DOY)){
		gt = dayOfYear > dateTime.tm_yday;
	}
	else if (formatIs(CODE_FORMAT_WOY)){
		gt = weekOfYear > (dateTime.tm_yday / 7);
	}
	else if (formatIs(CODE_FORMAT_MONTH)){
		gt = month > (dateTime.tm_mon + 1);
	}
	else if (formatIs(CODE_FORMAT_YEAR)){
		gt = year > (dateTime.tm_year + 1900);
	}
	else if (formatIs(CODE_FORMAT_SHIFT)){
		int day = ((dateTime.tm_wday - 1) >= 0) ? (dateTime.tm_wday - 1) : 6;
		gt = (dayOfWeek > day);
		if (dayOfWeek == day) {
			gt = (hour > dateTime.tm_hour);
			if (hour == dateTime.tm_hour){
				gt = (minute > dateTime.tm_min);
			}
		}
	}

	return gt;
}

template<typename T>
std::string DCInterval::toString(const T& value, int size, const char fillchar)const
{
	std::ostringstream oss;
	oss.clear();
	if(size){
		oss << std::setw(size);
		oss << std::setfill (fillchar);
	}
	oss << value;
	return oss.str();
}

DateCodeGeneric::DateCodeGeneric(std::string format) :
	_interval(format)
{
	_format = format;
	_code = "";
}

void DateCodeGeneric::setIntervalStart(std::string interval)
{
	return _interval.setValue(interval);
}

std::string DateCodeGeneric::getIntervalStart()const
{
	return  _interval.getValue();
}

const DCInterval &DateCodeGeneric::getInterval() const
{
	return _interval;
}

void DateCodeGeneric::setCode(std::string code)
{
	_code = code;
}

std::string DateCodeGeneric::getCode()const
{
	return _code;
}

std::string DateCodeGeneric::getFormat() const
{
	return _format;
}

void DateCodeGeneric::operator =(const DateCodeGeneric &other)
{
	copy(other);
}

bool DateCodeGeneric::operator ==(const DateCodeGeneric &other) const
{
	return compare(other);
}

bool DateCodeGeneric::operator !=(const DateCodeGeneric &other) const
{
	return !compare(other);
}

bool DateCodeGeneric::operator <(const DateCodeGeneric &other) const
{
	bool greater = gt(other);
	if (!greater) {
		return !compare(other);
	}
	return false;
}

bool DateCodeGeneric::operator <=(const DateCodeGeneric &other) const
{
	bool greater = gt(other);
	if (!greater) {
		return compare(other);
	}
	return false;
}

bool DateCodeGeneric::operator >(const DateCodeGeneric &other) const
{
	return gt(other);
}

bool DateCodeGeneric::operator >=(const DateCodeGeneric &other) const
{
	return (gt(other) || compare(other));
}

void DateCodeGeneric::copy(const DateCodeGeneric &other)
{
	_format = other._format;
	_code = other._code;
	_interval = other._interval;
}

bool DateCodeGeneric::compare(const DateCodeGeneric &other)const
{
	return ((getFormat().compare(other.getFormat()) == 0) &&
			(getIntervalStart().compare(other.getIntervalStart()) == 0));
}

bool DateCodeGeneric::gt(const DateCodeGeneric &other) const
{
	bool greater = false;
	if (_format.compare(CODE_FORMAT_SHIFT) !=  0){
		greater = (std::atoi(_interval.getValue().c_str()) >
				  std::atoi(other._interval.getValue().c_str()));
	}
	else {
		greater = (_interval.getDayOfWeek() > other._interval.getDayOfWeek());
		if(_interval.getDayOfWeek() == other._interval.getDayOfWeek()){
			greater = (_interval.getHour() > other._interval.getHour());
			if(_interval.getHour() == other._interval.getHour()){
				greater = (_interval.getMinute() > other._interval.getMinute());
			}
		}
	}

	return greater;
}

DCMinute::DCMinute() : DateCodeGeneric (CODE_FORMAT_MINUTE){}
DCHour::DCHour() : DateCodeGeneric (CODE_FORMAT_HOUR){}
DCDay::DCDay() : DateCodeGeneric (CODE_FORMAT_DOM){}
DCWeekDay::DCWeekDay() : DateCodeGeneric (CODE_FORMAT_DOW){}
DCJulian::DCJulian() : DateCodeGeneric (CODE_FORMAT_DOY){}
DCWeekOfYear::DCWeekOfYear() : DateCodeGeneric (CODE_FORMAT_WOY){}
DCMonth::DCMonth() : DateCodeGeneric (CODE_FORMAT_MONTH){}
DCYear::DCYear() : DateCodeGeneric (CODE_FORMAT_YEAR){}
DCShift::DCShift() : DateCodeGeneric (CODE_FORMAT_SHIFT){}

/************************************************************************************/

DateCodes::DateCodes()
{
	_codeFormaters.clear();
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_MINUTE,	"[DC:m]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_HOUR,		"[DC:H]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_DOM,		"[DC:dd]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_DOW,		"[DC:ddd]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_DOY,		"[DC:J]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_WOY,		"[DC:w]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_MONTH,	"[DC:M]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_YEAR,		"[DC:Y]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(CODE_FORMAT_SHIFT,	"[DC:S]"));

	clear();
}

DateCodes::~DateCodes()
{
	clear();
	_codeFormaters.clear();
}

bool DateCodes::addCode(const std::string& code, const std::string& format, const std::string& interval)
{
	DateCodeGeneric* ref = nullptr;

	if (format.compare(CODE_FORMAT_MINUTE) == 0) {
		if ((_minuteCodes.size() < 60) && !exist(_minuteCodes, format, interval)) {
			DCMinute dc;
			ref = pushCode(_minuteCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_HOUR) == 0) {
		if ((_hourCodes.size() < 24) &&	!exist(_hourCodes, format, interval)) {
			DCHour dc;
			ref = pushCode(_hourCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_DOM) == 0) {
		if ((_dayCodes.size() < 31) &&	!exist(_dayCodes, format, interval)) {
			DCDay dc;
			ref = pushCode(_dayCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_DOW) == 0) {
		if ((_dayOfWeekCodes.size() < 7) && !exist(_dayOfWeekCodes, format, interval)) {
			DCWeekDay dc;
			ref = pushCode(_dayOfWeekCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_DOY) == 0) {
		if (!exist(_julianCodes, format, interval)) {
			DCJulian dc;
			ref = pushCode(_julianCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_WOY) == 0) {
		if (!exist(_weekOfYearCodes, format, interval)) {
			DCWeekOfYear dc;
			ref = pushCode(_weekOfYearCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_MONTH) == 0) {
		if (!exist(_monthCodes, format, interval)) {
			DCMonth dc;
			ref = pushCode(_monthCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_YEAR) == 0) {
		if (!exist(_yearCodes, format, interval)) {
			DCYear dc;
			ref = pushCode(_yearCodes, dc, interval, code);
		}
	}
	else if (format.compare(CODE_FORMAT_SHIFT) == 0) {
		if (!exist(_shiftCodes, format, interval)) {
			DCShift dc;
			ref = pushCode(_shiftCodes, dc, interval, code);
		}
	}

	return (ref!= nullptr);
}

bool DateCodes::setCode(const std::string &format, const std::string& interval, std::string code)
{
	int i = -1;
	if (format.compare(CODE_FORMAT_MINUTE) == 0) {
		i = find(_minuteCodes, format, interval);
		if (i != -1) {
			_minuteCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_HOUR) == 0) {
		i = find(_hourCodes, format, interval);
		if (i != -1) {
			_hourCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_DOM) == 0) {
		i = find(_dayCodes, format, interval);
		if (i != -1) {
			_dayCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_DOW) == 0) {
		i = find(_dayOfWeekCodes, format, interval);
		if (i != -1) {
			_dayOfWeekCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_DOY) == 0) {
		i = find(_julianCodes, format, interval);
		if (i != -1) {
			_julianCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_WOY) == 0) {
		i = find(_weekOfYearCodes, format, interval);
		if (i != -1) {
			_weekOfYearCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_MONTH) == 0) {
		i = find(_monthCodes, format, interval);
		if (i != -1) {
			_monthCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_YEAR) == 0) {
		i = find(_yearCodes, format, interval);
		if (i != -1) {
			_yearCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(CODE_FORMAT_SHIFT) == 0) {
		i = find(_shiftCodes, format, interval);
		if (i != -1) {
			_shiftCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	return (i = -1);
}

bool DateCodes::removeCode(std::string format, std::string interval)
{
	bool removed = false;

	if (format.compare(CODE_FORMAT_MINUTE) == 0) {
		int idx = find(_minuteCodes, format, interval);
		if (idx != -1) {
			_minuteCodes.erase(_minuteCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_HOUR) == 0) {
		int idx = find(_hourCodes, format, interval);
		if (idx != -1) {
			_hourCodes.erase(_hourCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_DOM) == 0) {
		int idx = find(_dayCodes, format, interval);
		if (idx != -1) {
			_dayCodes.erase(_dayCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_DOW) == 0) {
		int idx = find(_dayOfWeekCodes, format, interval);
		if (idx != -1) {
			_dayOfWeekCodes.erase(_dayOfWeekCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_DOY) == 0) {
		int idx = find(_julianCodes, format, interval);
		if (idx != -1) {
			_julianCodes.erase(_julianCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_WOY) == 0) {
		int idx = find(_weekOfYearCodes, format, interval);
		if (idx != -1) {
			_weekOfYearCodes.erase(_weekOfYearCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_MONTH) == 0) {
		int idx = find(_monthCodes, format, interval);
		if (idx != -1) {
			_monthCodes.erase(_monthCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_YEAR) == 0) {
		int idx = find(_yearCodes, format, interval);
		if (idx != -1) {
			_yearCodes.erase(_yearCodes.begin()+idx);
			removed = true;
		}
	}
	else if (format.compare(CODE_FORMAT_SHIFT) == 0) {
		int idx = find(_shiftCodes, format, interval);
		if (idx != -1) {
			_shiftCodes.erase(_shiftCodes.begin()+idx);
			removed = true;
		}
	}
	return removed;
}

void DateCodes::clear()
{
	_minuteCodes.clear();
	_hourCodes.clear();
	_dayCodes.clear();
	_dayOfWeekCodes.clear();
	_julianCodes.clear();
	_weekOfYearCodes.clear();
	_monthCodes.clear();
	_yearCodes.clear();
	_shiftCodes.clear();
}

const std::vector<DCMinute>		&DateCodes::getMinuteCodes()		const{return _minuteCodes;}
const std::vector<DCHour>		&DateCodes::getHourCodes()			const{return _hourCodes;}
const std::vector<DCDay>		&DateCodes::getDayCodes()			const{return _dayCodes;}
const std::vector<DCWeekDay>	&DateCodes::getDayOfWeekCodes()		const{return _dayOfWeekCodes;}
const std::vector<DCJulian>		&DateCodes::getJulianCodes()		const{return _julianCodes;}
const std::vector<DCWeekOfYear> &DateCodes::getWeekOfYearCodes()	const{return _weekOfYearCodes;}
const std::vector<DCMonth>		&DateCodes::getMonthCodes()			const{return _monthCodes;}
const std::vector<DCYear>		&DateCodes::getYearCodes()			const{return _yearCodes;}
const std::vector<DCShift>		&DateCodes::getShiftCodes()			const{return _shiftCodes;}

std::vector<DateCodeGeneric> DateCodes::getAllCodes() const
{
	std::vector<DateCodeGeneric> codes;
	codes.clear();

	for (unsigned int i = 0; i < _minuteCodes.size(); i++)		{codes.push_back(_minuteCodes.at(i));}
	for (unsigned int i = 0; i < _hourCodes.size(); i++)		{codes.push_back(_hourCodes.at(i));}
	for (unsigned int i = 0; i < _dayCodes.size(); i++)			{codes.push_back(_dayCodes.at(i));}
	for (unsigned int i = 0; i < _dayOfWeekCodes.size(); i++)	{codes.push_back(_dayOfWeekCodes.at(i));}
	for (unsigned int i = 0; i < _julianCodes.size(); i++)		{codes.push_back(_julianCodes.at(i));}
	for (unsigned int i = 0; i < _weekOfYearCodes.size(); i++)	{codes.push_back(_weekOfYearCodes.at(i));}
	for (unsigned int i = 0; i < _monthCodes.size(); i++)		{codes.push_back(_monthCodes.at(i));}
	for (unsigned int i = 0; i < _yearCodes.size(); i++)		{codes.push_back(_yearCodes.at(i));}
	for (unsigned int i = 0; i < _shiftCodes.size(); i++)		{codes.push_back(_shiftCodes.at(i));}

	return codes;
}

void DateCodes::setMinuteCodes(const std::vector<DCMinute>& minuteCodes){ _minuteCodes = minuteCodes;}
void DateCodes::setHourCodes(const std::vector<DCHour>& hourCodes){  _hourCodes = hourCodes;}
void DateCodes::setDayCodes(const std::vector<DCDay>& dayCodes){ _dayCodes = dayCodes;}
void DateCodes::setDayOfWeekCodes(const std::vector<DCWeekDay>& dowCodes){	_dayOfWeekCodes = dowCodes;}
void DateCodes::setJulianCodes(const std::vector<DCJulian>& julianCodes){	_julianCodes = julianCodes;}
void DateCodes::setWeekOfYearCodes(const std::vector<DCWeekOfYear>& woyCodes) {	_weekOfYearCodes = woyCodes;}
void DateCodes::setMonthCodes(const std::vector<DCMonth>& monthCodes){ _monthCodes = monthCodes;}
void DateCodes::setYearCodes(const std::vector<DCYear>& yearCodes) { _yearCodes = yearCodes;}
void DateCodes::setShiftCodes(const std::vector<DCShift>& shiftCodes){ _shiftCodes = shiftCodes; }

void DateCodes::parserDateTime(std::string &dateTimeFormat, const tm date) const
{
	size_t pos = dateTimeFormat.find_first_of("[");
	if (pos != std::string::npos) {

		if ((dateTimeFormat.substr(pos).size() >= MIN_CODE_FORMATER_LENGTH) &&
			(dateTimeFormat.substr(pos + 1, 3).compare("DC:") == 0))
		{
			size_t end = 0;
			while  (end <= pos) {
				end = dateTimeFormat.find_first_of("]");
			}
			if (end != std::string::npos){
				size_t size = (end - pos) + 1;
				std::string dc = dateTimeFormat.substr(pos, size);
				std::string format = getFormatByCodeFormater(dc);
				std::string code = getCodeByFormat(format, date);
				if (!code.length()) {
					code = dc;
				}
				dateTimeFormat.replace(pos, size, code);
			}
		}

	}
}

bool DateCodes::isValid(std::string &dateTimeFormat_, int initalPos) const
{
	size_t pos = dateTimeFormat_.find("[DC:", static_cast<size_t>(initalPos));
	if (static_cast<int>(pos) >= 0){
		std::map<std::string, std::string>::const_iterator it;
		for (it = _codeFormaters.begin(); it != _codeFormaters.end(); it++){
			size_t ret = dateTimeFormat_.find(it->second, pos);
			if (ret != std::string::npos){
				return true;
			}
		}
	}
	return false;
}

std::string DateCodes::dateTimeCodeFormater(std::string codeFormat) const
{
	return _codeFormaters.at(codeFormat);
}

std::string DateCodes::getCodeByFormat(const std::string &format, const tm date) const
{
	std::string code = "";
	if (format.compare(CODE_FORMAT_MINUTE) == 0) {
		code = getCode(_minuteCodes, date);
	}
	else if (format.compare(CODE_FORMAT_HOUR) == 0) {
		code = getCode(_hourCodes, date);
	}
	else if (format.compare(CODE_FORMAT_DOM) == 0) {
		code = getCode(_dayCodes, date);
	}
	else if (format.compare(CODE_FORMAT_DOW) == 0) {
		code = getCode(_dayOfWeekCodes, date);
	}
	else if (format.compare(CODE_FORMAT_DOY) == 0) {
		code = getCode(_julianCodes, date);
	}
	else if (format.compare(CODE_FORMAT_WOY) == 0) {
		code = getCode(_weekOfYearCodes, date);
	}
	else if (format.compare(CODE_FORMAT_MONTH) == 0) {
		code = getCode(_monthCodes, date);
	}
	else if (format.compare(CODE_FORMAT_YEAR) == 0) {
		code = getCode(_yearCodes, date);
	}
	else if (format.compare(CODE_FORMAT_SHIFT) == 0) {
		code = getCode(_shiftCodes, date);
	}

	return  code;
}

void DateCodes::operator =(const DateCodes &other)
{
	copy(other);
}

bool DateCodes::operator ==(const DateCodes &other) const
{
	return equal(other);
}
bool DateCodes::operator !=(const DateCodes &other) const
{
	return !equal(other);
}

std::string DateCodes::getFormatByCodeFormater(const std::string &formater) const
{
	std::string format = "";
	for (std::map<std::string,std::string>::const_iterator it = _codeFormaters.begin();
		 it != _codeFormaters.end(); it++){
		if (it->second.compare(formater) == 0){
			format = it->first;
			break;
		}
	}
	return format;
}

bool DateCodes::equal(const DateCodes& other) const
{
	return  (_minuteCodes	  == other._minuteCodes)	 &&
			(_hourCodes		  == other._hourCodes)		 &&
			(_dayCodes		  == other._dayCodes)		 &&
			(_dayOfWeekCodes  == other._dayOfWeekCodes)	 &&
			(_julianCodes	  == other._julianCodes)	 &&
			(_weekOfYearCodes == other._weekOfYearCodes) &&
			(_monthCodes	  == other._monthCodes)		 &&
			(_yearCodes		  == other._yearCodes)		 &&
			(_shiftCodes	  == other._shiftCodes) ;

}

void DateCodes::copy(const DateCodes &other)
{
	_minuteCodes = other._minuteCodes;
	_hourCodes = other._hourCodes;
	_dayCodes = other._dayCodes;
	_dayOfWeekCodes = other._dayOfWeekCodes;
	_julianCodes = other._julianCodes;
	_weekOfYearCodes = other._weekOfYearCodes;
	_monthCodes	= other._monthCodes;
	_yearCodes = other._yearCodes;
	_shiftCodes = other._shiftCodes;
}

template<class T>
bool DateCodes::exist(const std::vector<T> &data, std::string format, std::string interval) const
{
	return (find(data,format,interval) != -1);
}

template<class T>
DateCodeGeneric* DateCodes::pushCode(std::vector<T> &data, T &dc, const std::string& interval, const std::string& code)
{
	dc.setIntervalStart(interval);
	dc.setCode(code);
	data.push_back(dc);
	sort(data);
	return &dc;
}

template<class T>
int DateCodes::find(const std::vector<T> &data, std::string format, std::string interval) const
{
	DateCodeGeneric item(format);
	item.setIntervalStart(interval);
	for (unsigned int i = 0; i < data.size(); i++){
		if (data.at(i) == item){
			return static_cast<int>(i);
		}
	}
	return -1;
}

template<class T>
void DateCodes::sort(std::vector<T> &data) const
{
	T temp;
	for (unsigned int i = 0; i <= data.size() -1; i++){
		for (unsigned int j = 0; j < data.size() -1; j++){
			if (data.at(j) > data.at(j + 1)){
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}
	}
}

template<class T>
std::string DateCodes::getCode(const std::vector<T> &data,  const tm dateTime) const
{
	std::string code = "";
	if (data.size()) {
		int i = static_cast<int>(data.size() - 1);
		while (i >= 0 &&  data.at(static_cast<unsigned long>(i)).getInterval() > dateTime) {
			i--;
		}
		if (i == -1){
			i = static_cast<int>(data.size() - 1);
		}
		code = data.at(static_cast<unsigned long>(i)).getCode();
	}

	return code;
}
