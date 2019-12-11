#ifndef MACSA_PRINTERS_ERRORS_H
#define MACSA_PRINTERS_ERRORS_H

#include "datatypes.h"
#include <time.h>

namespace Macsa {
	namespace Printers {
		class Error
		{
			public:
				Error();
				Error(time_t timestamp, ErrorType type, ErrorCode code, unsigned int priority);
				~Error();

				time_t timestamp() const;
				void setTimestamp(const time_t &value);

				ErrorType type() const;
				void setType(const ErrorType &type);
				void setType(const std::string &type);

				ErrorCode code() const;
				void setCode(const ErrorCode &code);
				void setCode(const std::string &code);

				unsigned int priority() const;
				void setPriority(unsigned int priority);

				void clear();

				//Operators
				void operator = (const Error& other);
				bool operator == (const Error& other) const {return equal(other);}
				bool operator != (const Error& other) const {return !equal(other);}

			private:
				time_t	  _timestamp;
				ErrorType _type;
				ErrorCode _code;
				unsigned int _priority;

				bool equal(const Error& other) const;
		};
	}
}

#endif	//MACSA_PRINTERS_ERRORS_H
