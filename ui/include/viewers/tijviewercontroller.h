#ifndef TIJ_VIEWER_CONTROLLER_H
#define TIJ_VIEWER_CONTROLLER_H

#include <QVariant>
#include "viewers/printerviewercontroller.h"
#include "tijprintercontroller.h"

class TIJViewerController : public PrinterViewerController
{
	public:
		enum class TIJDataDescriptors
		{
			LIVE = 0,
			STATUS,
			CONFIG,
			ALL_FILES,

			PRINTER_ID,
			PRINTER_ADDRS,
			PRINTER_STATUS,
			PRINTER_DT,
		};

	public:
		TIJViewerController(Macsa::TIJPrinterController& controller);
		virtual ~TIJViewerController(){}

		virtual QVariant data(int descriptor);
		virtual bool setData(int descriptor, const QVariant& value);

	protected:
		Macsa::TIJPrinterController& _controller;


};

#endif //TIJ_VIEWER_CONTROLLER_H
