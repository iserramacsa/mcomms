#ifndef MACSA_JET_PRINTERS_LOGS_H
#define MACSA_JET_PRINTERS_LOGS_H

#include "jet/datatypes.h"
#include <time.h>

namespace Macsa {
	namespace Printers {
		class LogItem
		{
			public:
				LogItem();
				LogItem(time_t timestamp, JetLogType type, const std::string& message);
				~LogItem();

				time_t timestamp() const;
				void setTimestamp(const time_t &time);

				JetLogType type() const;
				void setType(const JetLogType &type);
				void setType(const std::string &type);

				std::string message() const;
				void setMessage(const std::string &message);

				void clear();

				//Operators
				inline const LogItem& operator = (const LogItem& other) {return copy(other);}
				inline bool operator == (const LogItem& other) const {return equal(other);}
				inline bool operator != (const LogItem& other) const {return !equal(other);}
				inline bool operator > (const LogItem& other) const {return gt(other);}
				inline bool operator >= (const LogItem& other) const {return (gt(other) || eq(other));}
				inline bool operator < (const LogItem& other) const {return lt(other);}
				inline bool operator <= (const LogItem& other) const {return (lt(other) || eq(other));}


			private:
				time_t	    _timestamp;
				JetLogType  _type;
				std::string _message;

				bool equal(const LogItem& other) const;
				const LogItem& copy(const LogItem& other);
				inline bool gt(const LogItem& other) const { return (_timestamp > other._timestamp); }
				inline bool eq(const LogItem& other) const { return (_timestamp == other._timestamp); }
				inline bool lt(const LogItem& other) const { return (_timestamp < other._timestamp); }
		};

	}
}

#endif	//MACSA_JET_PRINTERS_LOGS_H
