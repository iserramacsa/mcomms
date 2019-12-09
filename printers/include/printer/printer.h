#ifndef PRINTER_DEFINITIONS_H
#define PRINTER_DEFINITIONS_H

#include <string>
#include <ctime>
#include "files.h"
#include "comms.h"

namespace Macsa {
	namespace Printers {
		class Printer {
			public:
				Printer();
				virtual ~Printer();

				virtual std::string type() const;

				virtual int id() const;
				virtual void setId(int id);

				std::time_t dateTime() const;
				void setDateTime(const std::time_t &dateTime);

				virtual PrinterFiles* files() = 0;
				virtual const PrinterFiles* files() const = 0;

				virtual PrinterComms* comms() = 0;
				virtual const PrinterComms* comms() const = 0;


				virtual bool operator == (const Printer& other) const {return equal(other);}
				virtual bool operator != (const Printer& other) const {return !equal(other);}

			protected:
				int _id;
				std::string _type;

				virtual bool equal (const Printer& other) const = 0;

		};
	}
}

#endif
