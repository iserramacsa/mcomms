#ifndef MACSA_LABELS_NISX_COUNTER_H
#define MACSA_LABELS_NISX_COUNTER_H

#include <string>

namespace Macsa {
	namespace Nisx {
		class Counter{
			public:
				Counter(int leadingZeros = 0, int min = 0, int max = 0, int step = 0, bool repeat = false);
				~Counter();

				int leadingZeros() const;
				void setLeadingZeros(int leadingZeros);
				std::string format() const;					//Compatibility with old parameter
				void setformat(const std::string& format);	//Compatibility with old parameter

				int min() const;
				void setMin(int min);

				int max() const;
				void setMax(int max);

				int step() const;
				void setStep(int step);

				bool repeat() const;
				void setRepeat(bool repeat);

				void operator = (const Counter& other)  { return copy(other); }
				bool operator == (const Counter& other) { return compare(other); }
				bool operator != (const Counter& other) { return !compare(other); }

			private:
				int _leadingZeros;
				int _min;
				int _max;
				int _step;
				bool _repeat;

				void copy(const Counter& other);
				bool compare(const Counter& other);
		};

	}
}
#endif //MACSA_LABELS_NISX_DATETIME_H
