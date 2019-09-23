#ifndef INPUTS_H
#define INPUTS_H

#include "iobase.h"
#include "printerTypes.h"

namespace Macsa {
	namespace Printers {
		class Inputs : public IOBase
		{
			public:
				Inputs(uint32_t id);
				virtual ~Inputs();

				InputMode_n mode() const;
				void setMode(const InputMode_n &mode);

				bool inverted() const;
				void setInverted(bool inverted);

				uint32_t filter() const;
				void setFilter(const uint32_t &filter);

			private:
				InputMode_n	_mode;
				bool		_inverted;
				uint32_t	_filter;


				virtual bool equal(const Inputs &other )const;
		};
	}
}

#endif //INPUTS_H
