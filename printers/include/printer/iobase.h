#ifndef IO_BASE_H
#define IO_BASE_H

#include <cstdint>
#include <string>

namespace Macsa {
	namespace Printers {
		class IOBase
		{
			public:
				IOBase(uint32_t id);
				virtual ~IOBase();

				virtual uint32_t id() const;

				virtual std::string descriptor() const;
				virtual void setDescriptor(const std::string &descriptor);

				virtual bool value() const;
				virtual void setValue(bool value);

				virtual bool operator < (const IOBase& other) const;
				virtual bool operator > (const IOBase& other) const;

				virtual bool operator == (const IOBase& other) const {return equal(other);}
				virtual bool operator != (const IOBase& other) const {return !equal(other);}

				virtual void operator = (const IOBase& other) {return copy(other);}

			protected:
				uint32_t _id;
				std::string _descriptor;
				bool _value;

				virtual bool equal(const IOBase& other) const = 0;
				virtual void copy(const IOBase& other) = 0;
		};
	}
}

#endif //IO_BASE_H
