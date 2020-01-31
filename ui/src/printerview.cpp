#include "printerview.h"


PrinterView::PrinterView(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	_controller = nullptr;

	connect(ui.butLive, SIGNAL(clicked(bool)), SLOT(onRequestLive()));
	connect(ui.butConfig, SIGNAL(clicked(bool)), SLOT(onRequestConfig()));
	connect(ui.butStatus, SIGNAL(clicked(bool)), SLOT(onRequestStatus()));
}

PrinterView::~PrinterView()
{}

void PrinterView::setController(Macsa::TIJPrinterController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new TIJViewerController(controller);
	refresh();
}

void PrinterView::refresh()
{
	this->setEnabled(_controller != nullptr);
	if (_controller) {
		QString name = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_ID)).toString();
		QString addr = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_ADDRS)).toString();
		ui.lblPrinterName->setText(QString("%1: %2").arg(name).arg(addr));

		QString status = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_STATUS)).toString();
		ui.lblPrinterStatus->setText(status);

		QString dt = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_DT)).toString();
		ui.lblDatetime->setText(dt);
	}
}

void PrinterView::onRequestLive()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::LIVE));
	}
	refresh();
}

void PrinterView::onRequestConfig()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::CONFIG));
	}
	refresh();
}

void PrinterView::onRequestStatus()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::STATUS));
	}
	refresh();
}
