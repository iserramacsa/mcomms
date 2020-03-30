#ifndef MACSA_PRINTER_JET_INPUT_OUTPUT_H
#define MACSA_PRINTER_JET_INPUT_OUTPUT_H

#include <string>

namespace Macsa {
	namespace Printers {

		class JetIO
		{
			public:
				JetIO(const std::string& id);
				JetIO(const JetIO& other);

				std::string id() const;
				bool value() const;
				void setValue(bool value);

				JetIO& operator = (const JetIO& other);
				inline bool operator == (const JetIO& other) const {return equal(other);}
				inline bool operator != (const JetIO& other) const {return !equal(other);}

			private:
				const std::string _id;
				bool _value;

				bool equal(const JetIO& other) const;
		};
	}
}

#endif
