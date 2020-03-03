#ifndef DATECODES_H
#define DATECODES_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

#define CODE_FORMAT_MINUTE	"m"
#define CODE_FORMAT_HOUR	"H"
#define CODE_FORMAT_DOM		"d"
#define CODE_FORMAT_DOW		"ddd"
#define CODE_FORMAT_DOY		"J"	//Julian day
#define CODE_FORMAT_WOY		"w"
#define CODE_FORMAT_MONTH	"M"
#define CODE_FORMAT_YEAR	"Y"
#define CODE_FORMAT_SHIFT	"S"


namespace Macsa {
	namespace Printers {
		namespace DateCode {
			class DCInterval{
				public:
					DCInterval(std::string format);
					void setValue(std::string value);
					std::string getValue()const;
					int getMinute()const;
					int getHour()const;
					int getDayOfMonth()const;
					int getDayOfWeek()const;
					int getJulianDay()const; //Julian day
					int getWeekOfYear()const;
					int getMonth()const;
					int getYear()const;

					void operator = (const DCInterval& other);
					bool operator < (const tm dateTime) const;
					bool operator > (const tm dateTime) const;

				private:
					std::string _format;
					int minute;
					int hour;
					int dayOfMonth;
					int dayOfWeek;
					int dayOfYear; //Julian day
					int weekOfYear;
					int month;
					int year;

					void copy (const DCInterval& other);
					bool formatIs(std::string format)const;
					bool greaterThan(const tm dateTime)const;
					template<typename T>
					std::string toString(const T& value, int size = 0, const char fillchar = ' ')const;
			};

			class DateCodeGeneric
			{
				public:
					DateCodeGeneric(std::string format);
					virtual ~DateCodeGeneric(){}
					virtual void setIntervalStart(std::string interval);
					virtual std::string getIntervalStart()const;
					virtual const DCInterval &getInterval()const;
					virtual void setCode(std::string code);
					virtual std::string getCode()const;
					virtual std::string getFormat()const;

					void operator = (const DateCodeGeneric& other);
					bool operator == (const DateCodeGeneric& other) const;
					bool operator != (const DateCodeGeneric& other) const;
					bool operator < (const DateCodeGeneric& other) const;
					bool operator <= (const DateCodeGeneric& other) const;
					bool operator > (const DateCodeGeneric& other) const;
					bool operator >= (const DateCodeGeneric& other) const;

				protected:
					std::string _format;
					std::string _code;
					DCInterval _interval;

					virtual void copy(const DateCodeGeneric& other);
					virtual bool compare(const DateCodeGeneric& other)const;
					virtual bool gt(const DateCodeGeneric& other)const;
			};

			class DCMinute : public DateCodeGeneric{
				public:
					DCMinute();
			};
			class DCHour : public DateCodeGeneric {
				public:
					DCHour();
			};
			class DCDay : public DateCodeGeneric {
				public:
					DCDay();
			};
			class DCWeekDay : public DateCodeGeneric {
				public:
					DCWeekDay();
			};
			class DCJulian : public DateCodeGeneric {
				public:
					DCJulian();
			};
			class DCWeekOfYear : public DateCodeGeneric {
				public:
					DCWeekOfYear();
			};
			class DCMonth : public DateCodeGeneric {
				public:
					DCMonth();
			};
			class DCYear : public DateCodeGeneric {
				public:
					DCYear();
			};
			class DCShift : public DateCodeGeneric {
				public:
					DCShift();
			};
		}

		class DateCodes
		{
			public:
				DateCodes();
				virtual ~DateCodes();

				bool addCode(const std::string& code, const std::string& format, const std::string& interval);
				bool setCode(const std::string& format, const std::string &interval, std::string code);
				bool removeCode(std::string format, std::string interval);
				void clear();

				const std::vector<DateCode::DCMinute>& getMinuteCodes() const;
				const std::vector<DateCode::DCHour>& getHourCodes() const;
				const std::vector<DateCode::DCDay>& getDayCodes() const;
				const std::vector<DateCode::DCWeekDay>& getDayOfWeekCodes() const;
				const std::vector<DateCode::DCJulian>& getJulianCodes() const;
				const std::vector<DateCode::DCWeekOfYear>& getWeekOfYearCodes() const;
				const std::vector<DateCode::DCMonth>& getMonthCodes() const;
				const std::vector<DateCode::DCYear>& getYearCodes() const;
				const std::vector<DateCode::DCShift>& getShiftCodes() const;
				std::vector<DateCode::DateCodeGeneric> getAllCodes() const;
				void setMinuteCodes(const std::vector<DateCode::DCMinute>& minuteCodes);
				void setHourCodes(const std::vector<DateCode::DCHour>& hourCodes);
				void setDayCodes(const std::vector<DateCode::DCDay>& dayCodes);
				void setDayOfWeekCodes(const std::vector<DateCode::DCWeekDay>& dowCodes);
				void setJulianCodes(const std::vector<DateCode::DCJulian>& julianCodes);
				void setWeekOfYearCodes(const std::vector<DateCode::DCWeekOfYear>& woyCodes);
				void setMonthCodes(const std::vector<DateCode::DCMonth>& monthCodes);
				void setYearCodes(const std::vector<DateCode::DCYear>& yearCodes);
				void setShiftCodes(const std::vector<DateCode::DCShift>& shiftCodes);


				void parserDateTime(std::string & dateTimeFormat, const std::tm date) const;
				bool isValid(std::string &dateTimeFormat_, int initialPos = 0) const;
				std::string dateTimeCodeFormater(std::string codeFormat) const;
				std::string getCodeByFormat(const std::string &format, const tm date) const;

				void operator = (const DateCodes& other);
				bool operator == (const DateCodes& other) const;
				bool operator != (const DateCodes& other) const;


			protected:
				std::vector<DateCode::DCMinute>	 _minuteCodes;
				std::vector<DateCode::DCHour>		 _hourCodes;
				std::vector<DateCode::DCDay>		 _dayCodes;
				std::vector<DateCode::DCWeekDay>	 _dayOfWeekCodes;
				std::vector<DateCode::DCJulian>	 _julianCodes;
				std::vector<DateCode::DCWeekOfYear> _weekOfYearCodes;
				std::vector<DateCode::DCMonth>		 _monthCodes;
				std::vector<DateCode::DCYear>		 _yearCodes;
				std::vector<DateCode::DCShift>		 _shiftCodes;
				std::map <std::string, std::string>  _codeFormaters;

				std::string getFormatByCodeFormater(const std::string& formater) const;

				bool equal(const DateCodes& other) const;
				void copy(const DateCodes& other);
				template<class T>
				int find(const std::vector<T>& data, std::string format, std::string interval) const;
				template<class T>
				bool exist(const std::vector<T>& data, std::string format, std::string interval) const;
				template<class T>
				void sort(std::vector<T>& data) const;
				template<class T>
				std::string getCode(const std::vector<T>& data, const tm dateTime) const;
				template<class T>
				DateCode::DateCodeGeneric* pushCode(std::vector<T> &data, T &dc, const std::string& interval, const std::string& code);

		};
	}
}
#endif //DATECODES_H
