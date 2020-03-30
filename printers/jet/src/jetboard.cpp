#include "jet/jetboard.h"

using namespace Macsa::Printers;


JetBoard::JetBoard(const std::string &type, unsigned int num) :
	_type(type),
	_number(num)
{
	_inputs.clear();
	_version = "";
}

JetBoard::JetBoard(const JetBoard &other) :
	_type(other._type),
	_number(other._number)
{
	copy(other);
}

JetBoard::~JetBoard()
{}

JetBoardType JetBoard::type() const
{
	return _type;
}

std::string JetBoard::id() const
{
	return _id;
}

void JetBoard::setId(const std::string &id)
{
	_id = id;
}

std::string JetBoard::version() const
{
	return _version;
}

void JetBoard::setVersion(const std::string &version)
{
	_version = version;
}

bool JetBoard::input(const std::string &id) const
{
	std::vector<JetIO>::const_iterator input = getInput(id);
	if (input != _inputs.end()) {
		return input->value();
	}
	return false;
}

void JetBoard::setInputs(const std::map<std::string, bool> &inputs)
{
	_inputs.clear();
	for (std::map<std::string, bool>::const_iterator it = inputs.begin(); it != inputs.end(); it++) {
		JetIO input(it->first);
		input.setValue(it->second);
		_inputs.push_back(input);
	}
}

unsigned int JetBoard::number() const
{
	return _number;
}

std::vector<JetIO>::const_iterator JetBoard::getInput(const std::string &id) const
{
	std::vector<JetIO>::const_iterator input;
	for(input = _inputs.begin(); input != _inputs.end(); input++) {
		if (input->id() == id){
			break;
		}
	}
	return input;
}

bool JetBoard::equal(const JetBoard &other) const
{
	bool equal = false;
	if (_type == other._type) {
		equal = (_number == other._number);
		equal &= (_version == other._version);
		equal &= (_id == other._id);
		if(equal) {
			equal = (_inputs == other._inputs);
		}
	}
	return equal;
}

void JetBoard::copy(const JetBoard &other)
{
	if (_type == other._type) {
		_number = other._number;
		_version = other._version;
		_id = other._id;
		_inputs = other._inputs;
	}
}

