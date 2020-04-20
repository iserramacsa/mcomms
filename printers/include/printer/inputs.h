#ifndef INPUTS_H
#define INPUTS_H

#include "iobase.h"
#include "tij/datatypes.h"

namespace Macsa {
	namespace Printers {
		class Input : public IOBase
		{
			public:
				Input(uint32_t id);

				InputMode mode() const;
				void setMode(const InputMode& mode);
				void setMode(nInputMode mode);
				void setMode(const std::string& mode);

				bool inverted() const;
				void setInverted(bool inverted);

				uint32_t filter() const;
				void setFilter(const uint32_t &filter);

			private:
				InputMode	_mode;
				bool		_inverted;
				uint32_t	_filter;


				virtual bool equal(const IOBase& other) const;
				virtual void copy(const IOBase& other);
		};
	}
}

#endif //INPUTS_H
