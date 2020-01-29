#ifndef PRINTER_VIEWER_H
#define PRINTER_VIEWER_H

#include "printer/printer.h"
#include "printerviewercontroller.h"
#include <QVariant>

class PrinterViewer : public PrinterViewerController
{
	public:
		explicit PrinterViewer(Macsa::Printers::Printer& printer) :
			PrinterViewerController(printer){}
		virtual ~PrinterViewer(){}

		virtual QVariant data(int descriptor) = 0;

	private:
		virtual bool setData(int, const QVariant&){return false;}

};

#endif //PRINTER_VIEWER_H
