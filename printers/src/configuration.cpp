#include "printer/configuration.h"

using namespace Macsa;
using namespace Macsa::Printers;
using namespace std;


Configuration::Configuration()
{}

Configuration::~Configuration()
{}

const Board* Configuration::board(unsigned int idx) const
{
	const Board* board = nullptr;
	if (idx < _boards.size()) {
		board = &_boards[static_cast<unsigned long>(idx)];
	}
	return std::move(board);
}


void Configuration::setBoards(const std::vector<Board> &boards)
{
	_boards.clear();
	for (auto& board : boards) {
		_boards.push_back(board);
	}
}

PrinterComms Configuration::comms() const
{
	return _comms;
}

void Configuration::setComms(const PrinterComms &comms)
{
	_comms = comms;
}

bool Configuration::equal(const Configuration &other)
{
	bool equal = false;

	equal = (_boards.size() == other._boards.size());
	if (equal){
		for (unsigned int i = 0; i < _boards.size(); i++){
			equal &= _boards.at(i) == other._boards.at(i);
		}
	}

    return equal;
}
