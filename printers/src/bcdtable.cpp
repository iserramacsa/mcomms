#include "printer/bcdtable.h"

using namespace Macsa;
using namespace Macsa::Printers;
using namespace std;

BcdTable::BcdTable()
{
	clear();
}

BcdTable::BCDMode_n BcdTable::bcdMode() const
{
	return _bcdMode;
}

string BcdTable::bcdModeStr() const
{
	switch (_bcdMode) {
		case USER_MODE:     return BCD_MODE_USER;
		case BCD_MODE_1:    return BCD_MODE_BCD_1;
		case BCD_MODE_2:    return BCD_MODE_BCD_2;
	}
	return "";
}

void BcdTable::setBcdMode(const BCDMode_n &bcdMode)
{
	_bcdMode = bcdMode;
}

void BcdTable::setBcdMode(const string &bcdMode)
{
	BCDMode_n mode = _bcdMode;
	if      (bcdMode.compare(BCD_MODE_USER)  == 0)  { mode = USER_MODE;  }
	else if (bcdMode.compare(BCD_MODE_BCD_1) == 0)  { mode = BCD_MODE_1; }
	else if (bcdMode.compare(BCD_MODE_BCD_2) == 0)  { mode = BCD_MODE_2; }
	setBcdMode(mode);
}

string BcdTable::bcdMessage(uint8_t code) const
{
	return _table.at(code);
}

void BcdTable::setbBcdMessage(const uint8_t &code, const string &message)
{
	map<uint8_t, string>::iterator bcd = _table.find(code);
	if (bcd != _table.end()){
		bcd->second = message;
	}
	else {
		_table.insert(pair<uint8_t, string>(code, message));
	}
}

void BcdTable::clear()
{
	_table.clear();
	for (uint8_t code = 0; code < MAX_BCD_CODES; code++) {
		_table.insert(pair<uint8_t, string>(code, ""));
	}
	_bcdMode = USER_MODE;
}

bool BcdTable::equal(const BcdTable &other)
{
	bool equal = true;

	if (_bcdMode == other._bcdMode) {
		for (auto& bcd : _table) {
			equal = (bcd.second.compare(other._table.at(bcd.first)) == 0);
			if(!equal){
				break;
			}
		}
	}

	return equal;
}
