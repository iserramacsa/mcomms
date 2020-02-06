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
	connect(ui.butFiles, SIGNAL(clicked(bool)), SLOT(onRequestFiles()));
	connect(ui.butConnect, SIGNAL(clicked(bool)), SLOT(onConnectClicked()));

	buildStatus();
	buildConfig();
	buildFiles();
}

PrinterView::~PrinterView()
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}
}

void PrinterView::setController(Macsa::TIJPrinterController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}
	_controller = new TIJViewerController(controller);
	_printerStatusView->setController(controller);
	_printerConfigView->setController(controller);
	_printerFilesView->setController(controller);
	refresh();
}

void PrinterView::refresh()
{
	this->setEnabled(_controller != nullptr);
	if (_controller) {
		QString name = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_ID)).toString();
		QString addr = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_ADDRS)).toString();
		ui.lblPrinterName->setText(QString("%1: %2").arg(name).arg(addr));

		setPrinterStatus(_controller->printerStatus());

		QString dt = _controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_DT)).toString();
		ui.lblDatetime->setText(dt);

		ui.lblCtrlVersion->setText(_controller->boardControllerVersion());
		ui.lblFPGAVersion->setText(_controller->boardFPGAVersion());
		ui.lblCoreVersion->setText(_controller->boardAPIVersion());

	}
	_printerStatusView->refresh();
	_printerConfigView->refresh();
	_printerFilesView->refresh();
}
#include "tijprintercontroller.h"
void PrinterView::setPrinterStatus(TIJViewerController::TIJStatus status)
{
	bool connected = false;
	switch (status) {
		case TIJViewerController::TIJStatus::DISCONNECTED:
			ui.lblPrinterStatus->setText("Disconnected");
			ui.lblPrinterStatus->setStyleSheet("color:#333;");
			break;
		case TIJViewerController::TIJStatus::STOPPED:
			connected = true;
			ui.lblPrinterStatus->setText("Stopped");
			ui.lblPrinterStatus->setStyleSheet("color:#900;");
			break;
		case TIJViewerController::TIJStatus::RUNNING:
			connected = true;
			ui.lblPrinterStatus->setText("Running");
			ui.lblPrinterStatus->setStyleSheet("color:#050;");
			break;
		case TIJViewerController::TIJStatus::WARNING:
			connected = true;
			ui.lblPrinterStatus->setText("Warning");
			ui.lblPrinterStatus->setStyleSheet("color:#F80;");
			break;
		case TIJViewerController::TIJStatus::PRINTING:
			connected = true;
			ui.lblPrinterStatus->setText("Printing");
			ui.lblPrinterStatus->setStyleSheet("color:#090;");
			break;
	}

	ui.butConnect->setText(((connected) ? "Disconnect" : "Connect"));
	ui.butConnect->setChecked(connected);

}

void PrinterView::clear()
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}

	setPrinterStatus(TIJViewerController::TIJStatus::DISCONNECTED);
	ui.lblPrinterName->setText("");
	ui.lblDatetime->setText("");
	ui.lblCtrlVersion->setText("---");
	ui.lblCoreVersion->setText("---");
	ui.lblFPGAVersion->setText("---");
}

void PrinterView::buildStatus()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsStatus);
	layout->setMargin(0);

	_printerStatusView = new PrinterStatusView(ui.WidgetContentsStatus);
	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_printerStatusView);

	clear();
}

void PrinterView::buildConfig()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsConfig);
	layout->setMargin(0);

	_printerConfigView = new PrinterConfigView(ui.WidgetContentsConfig);
	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_printerConfigView);

	clear();
}

void PrinterView::buildFiles()
{
	_printerFilesView = new PrinterFilesView(this);
	QVBoxLayout *layout = new QVBoxLayout(ui.tabFiles);
	layout->setMargin(0);
	layout->addWidget(_printerFilesView);
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

void PrinterView::onRequestFiles()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::ALL_FILES));
	}
	refresh();
}

void PrinterView::onConnectClicked()
{
	if (_controller != nullptr) {
		TIJViewerController::TIJStatus status = static_cast<TIJViewerController::TIJStatus>(_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::PRINTER_STATUS)).toInt());
		if (status == TIJViewerController::TIJStatus::DISCONNECTED){
			_controller->controller().connect();
		}
		else {
			_controller->controller().disconnect();
		}
		refresh();
	}
}
