#ifndef INPUTS_H
#define INPUTS_H

#include "iobase.h"
#include "datatypes.h"

namespace Macsa {
	namespace Printers {
		class Input : public IOBase
		{
			public:
				Input(uint32_t id);
				virtual ~Input();

				InputMode mode() const;
				void setMode(const InputMode& mode);
				void setMode(InputMode::N mode);
				void setMode(const std::string& mode);

				bool inverted() const;
				void setInverted(bool inverted);

				uint32_t filter() const;
				void setFilter(const uint32_t &filter);

				virtual void operator  = (const Input& other);
				virtual bool operator == (const Input& other)const {return  equal(other);}
				virtual bool operator != (const Input& other)const {return !equal(other);}

			private:
				InputMode	_mode;
				bool		_inverted;
				uint32_t	_filter;


				virtual bool equal(const Input &other )const;
		};
	}
}

#endif //INPUTS_H
