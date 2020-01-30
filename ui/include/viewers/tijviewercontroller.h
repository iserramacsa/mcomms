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
			STATUS = 0,
			LIVE,
			ALL_FILES,
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
