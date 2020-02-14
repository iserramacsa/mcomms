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
	connect(ui.butGetFonts, SIGNAL(clicked(bool)), SLOT(onRequestFonts()));
	connect(ui.butGetImages, SIGNAL(clicked(bool)), SLOT(onRequestImages()));
	connect(ui.butGetMessages, SIGNAL(clicked(bool)), SLOT(onRequestMessages()));
	connect(ui.butGetErrors, SIGNAL(clicked(bool)), SLOT(onRequestErrorsLog()));


	buildStatus();
	buildConfig();
	buildComms();
	buildFiles();
	buildErrorsLog();
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
	_printerCommsView->setController(controller);
	_printerFilesView->setController(controller);
	_controller->updatePrinterData();
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

		QString dt = _controller->printerDateTime("");
		ui.lblDatetime->setText(dt);

		ui.lblCtrlVersion->setText(_controller->boardControllerVersion());
		ui.lblFPGAVersion->setText(_controller->boardFPGAVersion());
		ui.lblCoreVersion->setText(_controller->boardAPIVersion());

	}
	_printerStatusView->refresh();
	_printerConfigView->refresh();
	_printerCommsView->refresh();
	_printerFilesView->refresh();
	updateLogs();
}

void PrinterView::updateLogs()
{
	if (_printerErrorsLog != nullptr)
	{
		if (_controller) {
			QVector<TIJViewerController::PrinterError> log = _controller->errorsLog();
			_printerErrorsLog->setRowCount(log.count());

			for (int i = 0; i < log.count(); i++) {
				QTableWidgetItem* itBoard = new QTableWidgetItem(static_cast<int>(log.at(i).boardId));
				QTableWidgetItem* itTStamp = new QTableWidgetItem(QString("%1").arg(log.at(i).timestamp.toString(Qt::SystemLocaleShortDate)));
				QTableWidgetItem* itType = new QTableWidgetItem(log.at(i).type);
				QTableWidgetItem* itPriority = new QTableWidgetItem(QString("%1").arg(log.at(i).priority));
				QTableWidgetItem* itCode = new QTableWidgetItem(log.at(i).code);

				int col = 0;
				_printerErrorsLog->setItem(i, col++, itTStamp);
				_printerErrorsLog->setItem(i, col++, itBoard);
				_printerErrorsLog->setItem(i, col++, itType);
				_printerErrorsLog->setItem(i, col++, itPriority);
				_printerErrorsLog->setItem(i, col++, itCode);
			}
			resizeErrorsLog();
		}
		else {
			_printerErrorsLog->clear();
		}
	}
}

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

void PrinterView::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	resizeErrorsLog();
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
	connect(_printerConfigView, SIGNAL(configChangeRequested()), SLOT(onRequestedChanges()), Qt::QueuedConnection);

	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_printerConfigView);

	clear();
}

void PrinterView::buildComms()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsNetwork);
	layout->setMargin(0);

	_printerCommsView = new PrinterCommsView(ui.WidgetContentsConfig);

	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_printerCommsView);

	clear();

}

void PrinterView::buildFiles()
{
	_printerFilesView = new PrinterFilesView(this);
	QVBoxLayout *layout = new QVBoxLayout(ui.tabFiles);
	layout->setMargin(0);
	layout->addWidget(_printerFilesView);
}

void PrinterView::buildErrorsLog()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.tabLogs);
	layout->setMargin(3);
	_printerErrorsLog = new QTableWidget(ui.tabLogs);
	layout->addWidget(_printerErrorsLog);

	QStringList headers;
	headers << "Timestamp" << "Board Id"  << "Type" << "Priority" << "Code";
	_printerErrorsLog->setColumnCount(headers.count());
	_printerErrorsLog->setHorizontalHeaderLabels(headers);
	resizeErrorsLog();
}

void PrinterView::resizeErrorsLog()
{
	if(_printerErrorsLog != nullptr && _printerErrorsLog->rowCount()) {
	   int w = 0;
	   int c = 0;
	   _printerErrorsLog->setColumnWidth(c++, 100); w += 100;
	   _printerErrorsLog->setColumnWidth(c++, 70); w += 70;
	   _printerErrorsLog->setColumnWidth(c++, 100); w += 100;
	   _printerErrorsLog->setColumnWidth(c++, 70); w += 70;
	   if (_printerErrorsLog->width() > 400){
		   w = _printerErrorsLog->width() - (w + 19);
	   }
	   else {
		   w = 400;
	   }
	   _printerErrorsLog->setColumnWidth(c, w);
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

void PrinterView::onRequestFiles()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::ALL_FILES));
	}
	refresh();
}

void PrinterView::onRequestFonts()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::FONTS_FILES));
	}
	refresh();
}

void PrinterView::onRequestImages()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::IMAGES_FILES));
	}
	refresh();
}

void PrinterView::onRequestMessages()
{
	if (_controller) {
		_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::MESSAGES_FILES));
	}
	refresh();
}

void PrinterView::onRequestErrorsLog()
{
	if (_controller) {
		_controller->requestErrorsList();
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

void PrinterView::onRequestedChanges()
{
	if (_controller != nullptr) {
		_controller->updatePrinterData();
		refresh();
	}
}
