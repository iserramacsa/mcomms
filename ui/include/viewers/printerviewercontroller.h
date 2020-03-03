#ifndef PRINTER_VIEWER_CONTROLLER_H
#define PRINTER_VIEWER_CONTROLLER_H

#include "printer/printer.h"
#include <QVariant>

class PrinterViewerController
{
	public:
		virtual QVariant data(int descriptor) = 0;
		virtual bool setData(int descriptor, const QVariant& value) = 0;

};

#endif //PRINTER_VIEWER_CONTROLLER_H
