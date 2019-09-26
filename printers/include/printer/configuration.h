#ifndef MACSA_PRINTERS_CONFIGURATION_H
#define MACSA_PRINTERS_CONFIGURATION_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "datatypes.h"
#include "board.h"
#include "comms.h"

namespace Macsa {
	namespace Printers {		
		class Configuration
		{

			public:
				Configuration();
				virtual ~Configuration();

				virtual Photocell photocell() const;
				virtual void setPhotocell(const Photocell &photocell);

				virtual const Board* board(unsigned int idx) const;
				virtual void setBoards(const std::vector<Board> &boards);

				virtual PrinterComms comms() const;
				virtual void setComms(const PrinterComms &comms);

				//Operators
				bool operator == (const Configuration& other){return equal(other);}
				bool operator != (const Configuration& other){return !equal(other);}

			protected:
				PrinterComms		_comms;
				std::vector<Board>	_boards;
				LoggerLevel _logLevel;
				bool _traceLogs;
				bool _traceComms;


//				enum EKindOfLog traceLevel;
//				bool traceComDetails;

//				MLogDef();
//				void clear();

//				bool isEqualTo( const MLogDef& other_ ) const;
//				bool operator == ( const MLogDef& other_ ) const { return  isEqualTo(other_); }
//				bool operator != ( const MLogDef& other_ ) const { return !isEqualTo(other_); }

				bool equal(const Configuration& other);
		};
	}
}

#endif //MACSA_PRINTERS_CONFIGURATION_H
