#ifndef MACSA_PRINTERS_CONFIGURATION_H
#define MACSA_PRINTERS_CONFIGURATION_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "datatypes.h"
#include "printer.h"
#include "board.h"

namespace Macsa {
//	namespace Printers {

//#if __cplusplus >= 201103L
//		using itBoard  = std::vector<Board>::iterator;
//		using citBoard = std::vector<Board>::const_iterator;
//#else
//		typedef std::vector<Board>::iterator		itBoard;
//		typedef std::vector<Board>::const_iterator	citBoard;
//#endif
//		class Configuration
//		{

//			public:
//				Configuration();
//				virtual ~Configuration();

//				virtual Photocell photocell() const;
//				virtual void setPhotocell(const Photocell &photocell);

//				virtual const std::vector<Board>& boards() const;
//				virtual const Board* board(int id) const;
//				virtual Board* board(int id);
//				virtual void setBoards(const std::vector<Board> &boards);
//				virtual void setBoard(const Board &board);

//				virtual PrinterComms comms() const;
//				virtual void setComms(const PrinterComms &comms);

//				//Operators
//				bool operator == (const Configuration& other){return equal(other);}
//				bool operator != (const Configuration& other){return !equal(other);}

//				LoggerLevel logLevel() const;
//				void setLogLevel(const LoggerLevel &logLevel);

//				bool traceLogs() const;
//				void setTraceLogs(bool traceLogs);

//				bool traceComms() const;
//				void setTraceComms(bool traceComms);

//			protected:
//				Printer& _printer;
//				LoggerLevel _logLevel;
//				bool _traceLogs;
//				bool _traceComms;


////				enum EKindOfLog traceLevel;
////				bool traceComDetails;

////				MLogDef();
////				void clear();

//				Configuration(const Configuration&){}
//				bool equal(const Configuration& other);
//		};
//	}
}

#endif //MACSA_PRINTERS_CONFIGURATION_H
