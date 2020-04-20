#include "jet/jetlog.h"

using namespace Macsa::Printers;

LogItem::LogItem()
{
	clear();
}

LogItem::LogItem(time_t timestamp, JetLogType type, const std::string &message)
{
	_timestamp = timestamp;
	_type = type;
	_message = message;
}

LogItem::~LogItem()
{
	clear();
}

time_t LogItem::timestamp() const
{
	return _timestamp;
}

void LogItem::setTimestamp(const time_t &time)
{
	_timestamp = time;
}

JetLogType LogItem::type() const
{
	return _type;
}

void LogItem::setType(const JetLogType &type)
{
	_type = type;
}

void LogItem::setType(const std::string &type)
{
	_type = type;
}
std::string LogItem::message() const
{
	return _message;
}

void LogItem::setMessage(const std::string &message)
{
	_message = message;
}

void LogItem::clear()
{
	_timestamp = time(nullptr);
	_type = nJetLogType::LOG_TYPE_SUCCESS;
	_message = "";
}

bool LogItem::equal(const LogItem &other) const
{
	return  _timestamp == other._timestamp &&
			_type == other._type &&
			_message == other._message;
}

const LogItem &LogItem::copy(const LogItem &other)
{
	_timestamp = other._timestamp;
	_type = other._type;
	_message = other._message;
	return *this;
}

