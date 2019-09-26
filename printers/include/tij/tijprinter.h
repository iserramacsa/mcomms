#ifndef TIJ_PRINTER_H
#define TIJ_PRINTER_H

#include "printer/printer.h"

namespace Macsa {
	namespace Printers {
		class TIJPrinter : public Printer{
			public:
				TIJPrinter();
				virtual ~TIJPrinter();
		};
	}
}

#endif
