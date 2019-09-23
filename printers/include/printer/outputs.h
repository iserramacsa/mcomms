#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "iobase.h"
#include "printerTypes.h"

namespace Macsa {
	namespace Printers {
		class Outputs : public IOBase
		{
			public:
				Outputs(uint32_t id);
				virtual ~Outputs();

				bool initialValue() const;
				void setInitialValue(bool initialValue);

				OutputType_n type() const;
				void setType(const OutputType_n &type);

				uint32_t time() const;
				void setTime(const uint32_t &time);

				virtual bool operator != (const Outputs&) const;
				virtual bool operator == (const Outputs&) const;

			private:
				bool _initialValue;
				OutputType_n _type;
				uint32_t _time;

				virtual bool equal(const Outputs &other )const;
		};
	}
}

#endif //INPUTS_H
