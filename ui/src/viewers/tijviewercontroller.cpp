#include "viewers/tijviewercontroller.h"

 TIJViewerController::TIJViewerController(Macsa::TIJPrinterController &controller) :
	_controller(controller)
 {

 }

QVariant TIJViewerController::data(int descriptor)
{
	switch (static_cast<TIJDataDescriptors>(descriptor))
	{
		case TIJDataDescriptors::LIVE:
				return _controller.getLive() == Macsa::Printers::ErrorCode_n::SUCCESS;
		case TIJDataDescriptors::STATUS:
				return _controller.printerStatus().c_str();
		default:
			return QVariant();
	}
}

bool TIJViewerController::setData(int /*descriptor*/, const QVariant &/*value*/)
{
	return false;
}

