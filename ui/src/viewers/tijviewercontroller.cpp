#include "viewers/tijviewercontroller.h"
#include <QDateTime>

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
				return _controller.updateStatus() == Macsa::Printers::ErrorCode_n::SUCCESS;
		case TIJDataDescriptors::CONFIG:
				return _controller.updateConfig() == Macsa::Printers::ErrorCode_n::SUCCESS;
		case TIJDataDescriptors::PRINTER_ID:
				return _controller.id().c_str();
		case TIJDataDescriptors::PRINTER_ADDRS:
				return _controller.address().c_str();
		case TIJDataDescriptors::PRINTER_STATUS:
				return _controller.printerStatus().c_str();
		case TIJDataDescriptors::PRINTER_DT:
			{
				Macsa::Printers::TIJPrinter* tij = dynamic_cast<Macsa::Printers::TIJPrinter*>(_controller.printer());
				if (tij){
					time_t time = tij->dateTime();
					QDateTime dt = QDateTime::fromTime_t(static_cast<uint32_t>(time));
					return dt.toString();
				}
				return "";
			}
		default:
			return QVariant();
	}
}

bool TIJViewerController::setData(int /*descriptor*/, const QVariant &/*value*/)
{
	return false;
}

