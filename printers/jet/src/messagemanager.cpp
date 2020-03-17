#include "jet/messagemanager.h"

using namespace Macsa::Printers;

/**************  Jet Message  **************/
JetMessage::JetMessage(const std::string name, unsigned int number) :
	_name(name)
{
	_number = number;
	_counter = 0;
}

JetMessage::JetMessage(const JetMessage &other) :
	_name(other._name)
{
	copy(other);
}

JetMessage::~JetMessage()
{}

std::string JetMessage::name() const
{
	return _name;
}

unsigned int JetMessage::counter()
{
	return _counter;
}

void JetMessage::setCounter(unsigned int counter)
{
	_counter = counter;
}

unsigned int JetMessage::number()
{
	return _number;
}

void JetMessage::setNumber(unsigned int number)
{
	_number = number;
}

bool JetMessage::equal(const JetMessage &other) const
{
	bool equal = false;
	if (_name == other._name) {
		equal = _counter == other._counter &&
				_number == other._number;
	}
	return equal;
}

void JetMessage::copy(const JetMessage &other)
{
	_counter = other._counter;
	_number = other._number;
}
/**************  Jet Message Manager  **************/
JetMessagesGroup::JetMessagesGroup(const std::string name) :
	_name(name)
{
	_currentMessage = nullptr;
}

JetMessagesGroup::JetMessagesGroup(const JetMessagesGroup& other) :
	_name(other._name)
{
	_currentMessage = nullptr;
	copy(other);
}

JetMessagesGroup::~JetMessagesGroup()
{
	_currentMessage = nullptr;
}

std::string JetMessagesGroup::name() const
{
	return _name;
}

std::string JetMessagesGroup::currentMessageName() const
{
	if (_currentMessage) {
		return _currentMessage->name();
	}
	return "";
}

unsigned int JetMessagesGroup::currentMessageNumber() const
{
	if (_currentMessage) {
		return _currentMessage->number();
	}
	return 0;
}

void JetMessagesGroup::setCurrentMessage(const std::string &name, unsigned int number)
{
	_currentMessage = nullptr;
	for (unsigned int message = 0; message < _messages.size(); message++) {
		if  (_messages.at(message).name() == name) {
			_currentMessage = &(_messages.at(message));
			_currentMessage->setNumber(number);
		}
	}
}

std::vector<std::string> JetMessagesGroup::messages()
{
	std::vector<std::string> messages;

	for (auto& message : _messages){
		messages.push_back(message.name());
	}

	return messages;
}

/**************  Jet Message Manager  **************/
JetMessagesManager::JetMessagesManager()
{
	_currentGroup = nullptr;
}

JetMessagesManager::JetMessagesManager(const JetMessagesManager& other)
{
	_currentGroup = nullptr;
	copy(other);
}

JetMessagesManager::~JetMessagesManager()
{
	_currentGroup = nullptr;
}

std::string JetMessagesManager::currentGroup() const
{
	if (_currentGroup != nullptr) {
		return _currentGroup->name();
	}

	return "";
}

void JetMessagesManager::setCurrentGroup(const std::string &currentGroup)
{
	_currentGroup = nullptr;
	for (unsigned int group = 0; group < _messageGroups.size(); group++) {
		if (_messageGroups.at(group).name() == currentGroup) {
			_currentGroup = &(_messageGroups.at(group));
		}
	}
}

int JetMessagesManager::currentMessageNumber() const
{
	if (_currentGroup) {
		return static_cast<int>(_currentGroup->currentMessageNumber());
	}
	return -1;
}

std::string JetMessagesManager::currentMessage() const
{
	if (_currentGroup) {
		return _currentGroup->currentMessageName();
	}
	return "";
}

void JetMessagesManager::setCurrentMessage(const std::string& name, unsigned int currentMessageNumber)
{
	if (_currentGroup) {
		_currentGroup->setCurrentMessage(name, currentMessageNumber);
	}
}

bool JetMessagesManager::equal(const JetMessagesManager &other) const
{
	return false;
}

void JetMessagesManager::copy(const JetMessagesManager &other)
{
	return;
}


