#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "iobase.h"
#include "datatypes.h"

namespace Macsa {
	namespace Printers {
		class Output : public IOBase
		{
			public:
				Output(uint32_t id);
				virtual ~Output();

				bool initialValue() const;
				void setInitialValue(bool initialValue);

				OutputType type() const;
				void setType(const OutputType& type);
				void setType(OutputType::N type);
				void setType(const std::string& type);

				uint32_t time() const;
				void setTime(const uint32_t &time);

				virtual void operator  = (const Output& other);
				virtual bool operator != (const Output& other) const{return  equal(other);}
				virtual bool operator == (const Output& other) const{return !equal(other);}

			private:
				bool _initialValue;
				OutputType	_type;
				uint32_t	_time;

				virtual bool equal(const Output &other )const;
		};
	}
}

#endif //INPUTS_H
