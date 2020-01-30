#include "printerview.h"


PrinterView::PrinterView(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	_controller = nullptr;
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
	//	_controller = new TIJViewerController();
}

void PrinterView::refresh()
{
	if (_controller) {
		QString status = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::STATUS)).toString();
		ui.lblPrinterStatus->setText(status);
	}
}
