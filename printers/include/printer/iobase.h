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

			protected:
				const uint32_t _id;
				std::string _descriptor;
				bool _value;
		};
	}
}

#endif //IO_BASE_H
