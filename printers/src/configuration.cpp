//#include "printer/configuration.h"

//using namespace Macsa;
//using namespace Macsa::Printers;
//using namespace std;


//Configuration::Configuration()
//{
//	_boards.clear();
//}

//Configuration::~Configuration()
//{}

//const std::vector<Board> &Configuration::boards() const
//{
//	return _boards;
//}

//const Board* Configuration::board(int id) const
//{
//	const Board* board = nullptr;
//	for (unsigned long i = 0; i < _boards.size(); i++)
//	{
//		if (_boards.at(i).id() == id)
//		{
//			board = &_boards[i];
//		}
//	}

//	return std::move(board);
//}

//Board *Configuration::board(int id)
//{
//	Board* board = nullptr;
//	for (unsigned long i = 0; i < _boards.size(); i++)
//	{
//		if (_boards.at(i).id() == id)
//		{
//			board = &_boards[i];
//		}
//	}

//	return std::move(board);
//}

//void Configuration::setBoards(const vector<Board> &boards)
//{
//	_boards.clear();
//	for (citBoard it = boards.begin(); it != boards.end(); it++) {
//		setBoard(*it);
//	}
//}

//void Configuration::setBoard(const Board &board)
//{
//	for (unsigned long i = 0; i < _boards.size(); i++)
//	{
//		if (_boards[i].id() == board.id())
//		{
//			_boards[i] = board;
//			return;
//		}
//	}
//	_boards.push_back(board);
//}

//PrinterComms Configuration::comms() const
//{
//	return _comms;
//}

//void Configuration::setComms(const PrinterComms &comms)
//{
//	_comms = comms;
//}

//LoggerLevel Configuration::logLevel() const
//{
//    return _logLevel;
//}

//void Configuration::setLogLevel(const LoggerLevel &logLevel)
//{
//    _logLevel = logLevel;
//}

//bool Configuration::traceLogs() const
//{
//    return _traceLogs;
//}

//void Configuration::setTraceLogs(bool traceLogs)
//{
//    _traceLogs = traceLogs;
//}

//bool Configuration::traceComms() const
//{
//    return _traceComms;
//}

//void Configuration::setTraceComms(bool traceComms)
//{
//    _traceComms = traceComms;
//}

//bool Configuration::equal(const Configuration &other)
//{
//    bool equal = false;
    
//    equal = (_boards.size() == other._boards.size());
//    if (equal){
//        for (unsigned int i = 0; i < _boards.size(); i++){
//			equal &= _boards.at(i) == other._boards.at(i);
//		}
//	}

//    return equal;
//}
