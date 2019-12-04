#ifndef PRINTER_BCD_CONFIG_H
#define PRINTER_BCD_CONFIG_H

#include <map>
#include "datatypes.h"

//BCD modes definition
#define MAX_BCD_CODES   16

namespace Macsa {
	namespace Printers {
		class BcdTable
		{
			public:
				BcdTable();
				BCDMode mode() const;
				void setMode(const BCDMode &mode);
				void setMode(const BCDMode_n &mode);
				void setMode(const std::string &mode);

				uint8_t current() const;
				void setCurrent(const uint8_t &current);

				std::string message(uint8_t code) const;
				void setMessage(const uint8_t &code, const std::string& message);
				std::string currentMessage() const;

				uint8_t count()const;

				void clear();

				//Operators
				void operator = (const BcdTable& other);
				bool operator == (const BcdTable& other)const {return equal(other);}
				bool operator != (const BcdTable& other)const {return !equal(other);}

			private:
				BCDMode	_bcdMode;
				uint8_t _current;
				std::map<uint8_t, std::string> _table;

				bool equal(const BcdTable& other)const;
		};
	}
}

#endif
