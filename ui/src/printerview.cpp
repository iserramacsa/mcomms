#include "printerview.h"
#include <QScrollArea>

PrinterView::PrinterView(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	_controller = nullptr;

	connect(ui.butLive, SIGNAL(clicked(bool)), SLOT(onRequestLive()));
	connect(ui.butConfig, SIGNAL(clicked(bool)), SLOT(onRequestConfig()));
	connect(ui.butStatus, SIGNAL(clicked(bool)), SLOT(onRequestStatus()));

	buildStatus();
}

PrinterView::~PrinterView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void PrinterView::setController(Macsa::TIJPrinterController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new TIJViewerController(controller);
	_printerStatusView->setController(controller);
	refresh();
}

void PrinterView::refresh()
{
	this->setEnabled(_controller != nullptr);
	if (_controller) {
		QString name = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_ID)).toString();
		QString addr = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_ADDRS)).toString();
		ui.lblPrinterName->setText(QString("%1: %2").arg(name).arg(addr));

		int status = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_STATUS)).toInt();
		setPrinterStatus(status);

		QString dt = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_DT)).toString();
		ui.lblDatetime->setText(dt);

		ui.lblCtrlVersion->setText(_controller->boardControllerVersion());
		ui.lblFPGAVersion->setText(_controller->boardFPGAVersion());
		ui.lblCoreVersion->setText(_controller->boardAPIVersion());

	}
	_printerStatusView->refresh();
}
#include "tijprintercontroller.h"
void PrinterView::setPrinterStatus(int status)
{
	switch (static_cast<Macsa::TIJPrinterController::TIJPrinterStatus>(status)) {
		case Macsa::TIJPrinterController::TIJPrinterStatus::DISCONNECTED:
			ui.lblPrinterStatus->setText("Disconnected");
			ui.lblPrinterStatus->setStyleSheet("color:#333;");
			break;
		case Macsa::TIJPrinterController::TIJPrinterStatus::STOPPED:
			ui.lblPrinterStatus->setText("Stopped");
			ui.lblPrinterStatus->setStyleSheet("color:#900;");
			break;
		case Macsa::TIJPrinterController::TIJPrinterStatus::RUNNING:
			ui.lblPrinterStatus->setText("Running");
			ui.lblPrinterStatus->setStyleSheet("color:#050;");
			break;
		case Macsa::TIJPrinterController::TIJPrinterStatus::WARNING:
			ui.lblPrinterStatus->setText("Warning");
			ui.lblPrinterStatus->setStyleSheet("color:#303;");
			break;
		case Macsa::TIJPrinterController::TIJPrinterStatus::PRINTING:
			ui.lblPrinterStatus->setText("Printing");
			ui.lblPrinterStatus->setStyleSheet("color:#090;");
			break;
	}
}

void PrinterView::clear()
{
	setPrinterStatus(-1);
	ui.lblPrinterName->setText("");
	ui.lblDatetime->setText("");
	ui.lblCtrlVersion->setText("---");
	ui.lblCoreVersion->setText("---");
	ui.lblFPGAVersion->setText("---");
}

void PrinterView::buildStatus()
{
	QWidget* tabWidget = ui.tabStatus;
	QVBoxLayout* statusLayout = new QVBoxLayout(tabWidget);
	statusLayout->setMargin(0);
	statusLayout->addWidget(ui.scrollArea);


	QWidget* statusWidget = ui.scrollAreaWidgetContents;
	statusWidget->setLayout(new QVBoxLayout);

	//QWidget* statusWidget = new QWidget(tabWidget);
	QVBoxLayout* layout = dynamic_cast<QVBoxLayout*>(ui.scrollAreaWidgetContents->layout());
	layout->setMargin(0);

	_printerStatusView = new PrinterStatusView(statusWidget);
	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_printerStatusView);

	clear();
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
