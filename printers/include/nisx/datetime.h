#ifndef MACSA_LABELS_NISX_DATETIME_H
#define MACSA_LABELS_NISX_DATETIME_H

#include <string>

namespace Macsa {
	namespace Nisx {
		class DateTime{
			public:
				DateTime(const std::string &format = "");
				DateTime(const std::string &format, int dayOffset, int monthOffset, int yearOffset, uint8_t startOfDay = 0);
				~DateTime();

				std::string format() const;
				void setFormat(const std::string &format);

				int dayOffset() const;
				void setDayOffset(int dayOffset);

				int monthOffset() const;
				void setMonthOffset(int monthOffset);

				int yearOffset() const;
				void setYearOffset(int yearOffset);

				uint8_t startOfDay() const;
				void setStartOfDay(const uint8_t &startOfDay);

				void operator = (const DateTime& other)  { return copy(other); }
				bool operator == (const DateTime& other) { return compare(other); }
				bool operator != (const DateTime& other) { return !compare(other); }

			private:
				std::string _format;
				int _dayOffset;
				int _monthOffset;
				int _yearOffset;
				uint8_t _startOfDay;

				void clear();
				void copy(const DateTime& other);
				bool compare(const DateTime& other);

		};

	}
}
#endif //MACSA_LABELS_NISX_DATETIME_H
