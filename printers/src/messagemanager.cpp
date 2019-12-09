#include "printer/messagemanager.h"

using namespace Macsa::Printers;

MessageManager::MessageManager()
{
	clear();
}

MessageManager::~MessageManager()
{}

BCDMode MessageManager::mode() const
{
	return _mode;
}

void MessageManager::setMode(const BCDMode &mode)
{
	_mode = mode;
}

void MessageManager::setMode(const BCDMode_n &mode)
{
	_mode = mode;
}

void MessageManager::setMode(const std::string &mode)
{
	_mode = mode;
}

std::string MessageManager::userMessage() const
{
	return _userMessage;
}

void MessageManager::setUserMessage(const std::string &userMessage)
{
	_userMessage = userMessage;
}

const BCDTable &MessageManager::bcdTable() const
{
	return _bcdTable;
}

void MessageManager::setBcdTable(const std::vector<std::string> &bcdTable)
{
	if (bcdTable.size() <= MAX_BCD_CODES) {
		for (unsigned long i = 0; i < bcdTable.size(); i++) {
			_bcdTable[i] = bcdTable.at(i);
		}
	}
}

void MessageManager::setBcdTable(const BCDTable& bcdTable)
{
	_bcdTable = bcdTable;
}

void MessageManager::setBcdMessage(uint8_t code, const std::string &message)
{
	if (code < MAX_BCD_CODES){
		_bcdTable[code] = message;
	}
}

const std::string &MessageManager::bcdMessage(uint8_t code)
{
	return _bcdTable.at(code);
}

uint8_t MessageManager::currentBcdCode() const
{
	return _currentBcdCode;
}

void MessageManager::setCurrentBcdCode(const uint8_t &currentBcdCode)
{
	if (currentBcdCode < MAX_BCD_CODES) {
		_currentBcdCode = currentBcdCode;
	}
}

std::string MessageManager::currentMessage() const
{
	std::string msg = "";
	if (_mode == Printers::BCDMode_n::USER_MODE) {
		msg = _userMessage;
	}
	else {
		msg = _bcdTable.at(_currentBcdCode);
	}

	return msg;
}

void MessageManager::clear()
{
	_currentBcdCode = 0;
	_userMessage = "";
	for (unsigned long i = 0; i < MAX_BCD_CODES; i++) {
		_bcdTable[i] = "";
	}

}

bool MessageManager::equal(const MessageManager &other) const
{
	bool equal = false;

	equal = (_mode == other._mode);
	equal &= (_currentBcdCode == other._currentBcdCode);
	equal &= (_userMessage.compare(other._userMessage) == 0);

	if(equal) {
		for (unsigned long i = 0; i < MAX_BCD_CODES; i++) {
			equal = (_bcdTable.at(i).compare(other._bcdTable.at(i)) == 0);
			if(!equal) {
				break;
			}
		}
	}

	return equal;
}

void MessageManager::copy(const MessageManager &other)
{
	_mode = other._mode;
	_currentBcdCode = other._currentBcdCode;
	_userMessage = other._userMessage;
	for (unsigned long i = 0; i < MAX_BCD_CODES; i++) {
		_bcdTable[i] = other._bcdTable.at(i);
	}
}
