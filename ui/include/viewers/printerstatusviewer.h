#ifndef PRINTER_STATUS_VIEWER_H
#define PRINTER_STATUS_VIEWER_H

#include "printerviewer.h"
#include "printer/printer.h"

class PrinterStatusViewer : public PrinterViewer
{
	public:
		PrinterStatusViewer(Macsa::Printers::Printer& printer);
		virtual ~PrinterStatusViewer();

		virtual QVariant data(int descriptor);
	
};

#endif //PRINTER_STATUS_VIEWER_H
