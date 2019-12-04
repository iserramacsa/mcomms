#include "printer/bcdtable.h"

using namespace Macsa::Printers;
using namespace std;

BcdTable::BcdTable()
{
	clear();
}

void BcdTable::setMode(const BCDMode &bcdMode)
{
	_bcdMode = bcdMode;
}

BCDMode BcdTable::mode() const
{
	return _bcdMode;
}

void BcdTable::setMode(const BCDMode_n &bcdMode)
{
	_bcdMode = bcdMode;
}

void BcdTable::setMode(const string &bcdMode)
{
	_bcdMode = bcdMode;
}

uint8_t BcdTable::current() const
{
	return _current;
}

void BcdTable::setCurrent(const uint8_t &current)
{
	_current = current;
}

string BcdTable::message(uint8_t code) const
{
	return _table.at(code);
}

void BcdTable::setMessage(const uint8_t &code, const string &message)
{
	map<uint8_t, string>::iterator bcd = _table.find(code);
	if (bcd != _table.end()){
		bcd->second = message;
	}
	else {
		_table.insert(pair<uint8_t, string>(code, message));
	}
}

string BcdTable::currentMessage() const
{
	if (_bcdMode != BCDMode_n::USER_MODE && _current < MAX_BCD_CODES)
	{
		return message(_current);
	}
	else
	{
		return "";
	}
}

uint8_t BcdTable::count() const
{
	return MAX_BCD_CODES;
}

void BcdTable::clear()
{
	_table.clear();
	for (uint8_t code = 0; code < MAX_BCD_CODES; code++) {
		_table.insert(pair<uint8_t, string>(code, ""));
	}
	_bcdMode = BCDMode_n::USER_MODE;
	_current = 0;
}

void BcdTable::operator = (const BcdTable &other)
{
	_bcdMode = other._bcdMode;
	_table.clear();
	_table.insert(other._table.begin(), other._table.end());
}

bool BcdTable::equal(const BcdTable &other) const
{
	bool equal = false;

	if (_bcdMode == other._bcdMode && _table.size() == other._table.size()) {
		for (auto& bcd : _table) {
			equal = (bcd.second.compare(other._table.at(bcd.first)) == 0);
			if(!equal){
				break;
			}
		}
	}

	return equal;
}
