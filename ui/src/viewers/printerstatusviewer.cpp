#include "printerstatusviewer.h"

PrinterStatusViewer::PrinterStatusViewer(Macsa::Printers::Printer &printer) :
	PrinterViewer(printer)
{

}

PrinterStatusViewer::~PrinterStatusViewer()
{

}

QVariant PrinterStatusViewer::data(int descriptor)
{
	Q_UNUSED(descriptor)
	return QVariant();
}
