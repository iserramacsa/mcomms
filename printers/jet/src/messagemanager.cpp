#include "jet/messagemanager.h"
#include <algorithm> //std::find

using namespace Macsa::Printers;

/**************  Jet Message  **************/
Message::Message(const std::string name, unsigned int number) :
	_name(name)
{
	_number = number;
	_counter = 0;
}

Message::Message(const Message &other) :
	_name(other._name)
{
	copy(other);
}

Message::~Message()
{}

std::string Message::name() const
{
	return _name;
}

unsigned int Message::counter() const
{
	return _counter;
}

void Message::setCounter(unsigned int counter)
{
	_counter = counter;
}

unsigned int Message::number() const
{
	return _number;
}

void Message::setNumber(unsigned int number)
{
	_number = number;
}

std::string Message::content() const
{
    return _content;
}

void Message::setContent(const std::string &content)
{
    _content = content;
}

bool Message::equal(const Message &other) const
{
    bool equal = false;
    if (_name == other._name) {
        equal = _counter == other._counter &&
				_number == other._number;
	}
	return equal;
}

void Message::copy(const Message &other)
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
			break;
		}
	}
}

void JetMessagesGroup::setCurrentMessage(unsigned int number)
{
	_currentMessage = nullptr;
	for (unsigned int message = 0; message < _messages.size(); message++) {
		if  (_messages.at(message).number() == number) {
			_currentMessage = &(_messages.at(message));
			break;
		}
	}
}

void JetMessagesGroup::setMessageCounter(unsigned int messageNumber, unsigned int counter)
{
	for(auto & message : _messages) {
		if (message.number() == messageNumber) {
			message.setCounter(counter);
			break;
		}
	}
}

std::vector<Message> JetMessagesGroup::messages() const
{
	return _messages;
}

void JetMessagesGroup::setMessages(const std::vector<std::string> &messages)
{
	std::string current = currentMessageName();
	_messages.clear();
	for (unsigned int i = 0; i < messages.size(); i++) {
		Message message(messages.at(i), i);
		_messages.push_back(message);
		if (current.length()){
			if (message.name() == current) {
				setCurrentMessage(message.name(), message.number());
			}
		}
	}
}

Message JetMessagesGroup::message(unsigned int msgNum) const
{
	for (auto& message : _messages) {
		if (message.number() == msgNum) {
			return message;
		}
	}
	return Message("");
}

void JetMessagesGroup::setMessageContent(const Message &msg)
{
	for (auto& message : _messages) {
		if (message.name() == msg.name() && message.number() == msg.number()) {
			message.setContent(msg.content());
		}
	}
}

void JetMessagesGroup::clear()
{
	_messages.clear();
}

void JetMessagesGroup::addMessage(const std::string &name, unsigned int num)
{
	std::vector<Message>::const_iterator it = std::find_if(_messages.begin(), _messages.end(), [name](Message& message){return (name == message.name());});
	if (it == _messages.end())
	{
		_messages.push_back(Message(name, num));
	}
}

Message JetMessagesGroup::message(const std::string &name) const
{
	for (auto& message : _messages) {
		if (message.name() == name) {
			return message;
		}
	}
	return Message(name);
}

bool JetMessagesGroup::equal(const JetMessagesGroup &other) const
{
	bool equal = false;

	if (_name == other._name) {
		if (_messages.size() == other._messages.size()) {
			for (unsigned int i = 0; i < _messages.size(); i++) {
				equal = (_messages.at(i) == other._messages.at(i));
				if (!equal) {
					break;
				}
			}
			if (equal) {
				if (_currentMessage != nullptr && other._currentMessage != nullptr) {
					equal = (_currentMessage->name() == other._currentMessage->name());
				}
				else {
					equal = (_currentMessage == nullptr && other._currentMessage == nullptr);
				}
			}
		}
	}

	return equal;
}

void JetMessagesGroup::copy(const JetMessagesGroup &other)
{
	_messages.clear();
	_messages = other._messages;
	if(other._currentMessage != nullptr) {
		setCurrentMessage(other._currentMessage->name(), other._currentMessage->number());
	}
}

/**************  Jet Message Manager  **************/
JetMessagesManager::JetMessagesManager()
{
	_currentGroup = nullptr;
	_messageGroups.push_back(JetMessagesGroup(""));
	setCurrentGroup("");
}

JetMessagesManager::JetMessagesManager(const JetMessagesManager& other)
{
	copy(other);
}

JetMessagesManager::~JetMessagesManager()
{
	_currentGroup = nullptr;
	_messageGroups.clear();
}

std::vector<std::string> JetMessagesManager::groups() const
{
	std::vector<std::string> groups;
	for (unsigned int i = 0; i < _messageGroups.size(); i++) {
		groups.push_back(_messageGroups.at(i).name());
	}
	return groups;
}

std::vector<Message> JetMessagesManager::messages(const std::string &group) const
{
	for (unsigned int i = 0; i < _messageGroups.size(); i++) {
		if (_messageGroups.at(i).name() == group){
			return _messageGroups.at(i).messages();
		}
	}
	return std::vector<Message>();
}

Message JetMessagesManager::message(unsigned int num) const
{
	if (_currentGroup != nullptr) {
		return _currentGroup->message(num);
	}
	return Message("");
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
	if (_currentGroup == nullptr || _currentGroup->name() != currentGroup) {
		std::vector<JetMessagesGroup>::iterator it = findGroup(currentGroup);
		if (it != _messageGroups.end()) {
			_currentGroup = &(*it);
		}
	}
}

bool JetMessagesManager::groupExist(const std::string &group) const
{
	return (findGroup(group) != _messageGroups.end());
}

bool JetMessagesManager::addNewGroup(const std::string &group)
{
	bool added = false;
	if(!groupExist(group)) {
		_messageGroups.push_back(JetMessagesGroup(group));
		added = true;
	}
	return added;
}

JetMessagesGroup * JetMessagesManager::group(const std::string &group)
{
	JetMessagesGroup * pGroup = nullptr;
	std::vector<JetMessagesGroup>::iterator it = findGroup(group);
	if (it != _messageGroups.end()) {
		pGroup = &(*it);
	}
	return pGroup;
}

bool JetMessagesManager::deleteGroup(const std::string &group)
{
	std::vector<JetMessagesGroup>::iterator it = findGroup(group);
	if (it != _messageGroups.end()) {
		(*it).clear();
		_messageGroups.erase(it);
		return true;
	}
	return false;
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

void JetMessagesManager::setCurrentMessage(unsigned int currentMessageNumber)
{
	if (_currentGroup) {
		_currentGroup->setCurrentMessage(currentMessageNumber);
	}
}

void JetMessagesManager::setMessageCounter(unsigned int messageNumber, unsigned int counter)
{
	if (_currentGroup) {
		_currentGroup->setMessageCounter(messageNumber, counter);
	}
}

void JetMessagesManager::setMessageContent(const Message &msg)
{
	if (_currentGroup){
		_currentGroup->setMessageContent(msg);
	}
}

void JetMessagesManager::clear()
{
	_currentGroup = nullptr;
	_messageGroups.clear();
}

bool JetMessagesManager::equal(const JetMessagesManager &other) const
{
	bool equal = false;
	if (_messageGroups.size() == other._messageGroups.size()) {
		for (unsigned int i = 0; i < _messageGroups.size(); i++) {
			equal = (_messageGroups.at(i) == other._messageGroups.at(i));
			if (!equal) {
				break;
			}
		}
		if (equal) {
			if (_currentGroup != nullptr && other._currentGroup != nullptr) {
				equal = (_currentGroup->name() == other._currentGroup->name());
			}
			else {
				equal = (_currentGroup == nullptr && other._currentGroup == nullptr);
			}
		}
	}
	return equal;
}

void JetMessagesManager::copy(const JetMessagesManager &other)
{
	_currentGroup = nullptr;
	_messageGroups.clear();
	_messageGroups = other._messageGroups;
	if (other._currentGroup != nullptr) {
		setCurrentGroup(other._currentGroup->name());
	}
}

std::vector<JetMessagesGroup>::iterator JetMessagesManager::findGroup(const std::string &group)
{
	return std::find_if(_messageGroups.begin(), _messageGroups.end(), [group](JetMessagesGroup& item) {return (item.name() == group);});
}

std::vector<JetMessagesGroup>::const_iterator JetMessagesManager::findGroup(const std::string &group) const
{
	std::vector<JetMessagesGroup>::const_iterator it = _messageGroups.begin();
	for (; it != _messageGroups.end(); it++) {
		if (it->name() == group) {
			break;
		}
	}
	return it;
}


