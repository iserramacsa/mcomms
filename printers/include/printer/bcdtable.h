#ifndef PRINTER_BCD_CONFIG_H
#define PRINTER_BCD_CONFIG_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

//BCD modes definition
#define MAX_BCD_CODES   16
#define BCD_MODE_USER   "USER_MODE"
#define BCD_MODE_BCD_1  "BCD_MODE_1"
#define BCD_MODE_BCD_2  "BCD_MODE_2"

namespace Macsa {

	namespace Printers {

		class BcdTable
		{
			public:
				enum BCDMode_n{
					USER_MODE = 0,
					BCD_MODE_1,
					BCD_MODE_2
				};

			public:
				BcdTable();
				BCDMode_n bcdMode() const;
				std::string bcdModeStr() const;
				void setBcdMode(const BCDMode_n &bcdMode);
				void setBcdMode(const std::string &bcdMode);
				std::string bcdMessage(uint8_t code) const;
				void setbBcdMessage(const uint8_t &code, const std::string& message);
				void clear();

				//Operators
				bool operator == (const BcdTable& other){return equal(other);}
				bool operator == (const BcdTable* other){return (other != nullptr && equal(*other));}
				bool operator != (const BcdTable& other){return !equal(other);}
				bool operator != (const BcdTable* other){return (other != nullptr && !equal(*other));}

			private:
				BCDMode_n		_bcdMode;
				std::map<uint8_t, std::string> _table;

				bool equal(const BcdTable& other);
		};
	}
}

#endif
