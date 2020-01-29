#ifndef PRINTER_VIEWER_CONTROLLER_H
#define PRINTER_VIEWER_CONTROLLER_H

#include "printer/printer.h"
#include <QVariant>

using namespace Macsa;
using namespace Macsa::Printers;

class PrinterViewerController
{
	public:
		explicit PrinterViewerController(Macsa::Printers::Printer& printer) :
			_printer(printer) {}
		virtual ~PrinterViewerController(){}
		virtual QVariant data(int descriptor) = 0;
		virtual bool setData(int descriptor, const QVariant& value) = 0;

	protected:
		Printer& _printer;

};

#endif //PRINTER_VIEWER_CONTROLLER_H
