#include "tijview.h"
#include "tij/datatypes.h"
#include <QScrollArea>

#define ERROR_ICON	":/icons/error.svg"
#define WARN_ICON	":/icons/warning.svg"
#define INFO_ICON	":/icons/notification.svg"

TijView::TijView(QWidget *parent) :
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

	_dtTimer.setParent(this);
	_dtTimer.setInterval(1000);
	connect(&_dtTimer, SIGNAL(timeout()), SLOT(onUpdateDateTime()));

	buildStatus();
	buildConfig();
	buildComms();
	buildFiles();
	buildErrorsLog();
}

TijView::~TijView()
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}
}

void TijView::setController(Macsa::MComms::TijController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}
	_controller = new TIJViewerController(controller);
	_statusView->setController(controller);
	_configView->setController(controller);
	_commsView->setController(controller);
	_filesView->setController(controller);
	refresh();
	if (!_dtTimer.isActive()) {
		_dtTimer.start();
	}
	connect(_controller, SIGNAL(printerStatusChanged()), SLOT(refresh()));
}

void TijView::refresh()
{
	this->setEnabled(_controller != nullptr);
	if (_controller) {
		QString name = _controller->id();
		QString addr = _controller->address();
		ui.lblPrinterName->setText(QString("%1: %2").arg(name).arg(addr));

		setPrinterStatus(_controller->printerStatus());

		onUpdateDateTime();

		ui.lblCtrlVersion->setText(_controller->boardControllerVersion());
		ui.lblFPGAVersion->setText(_controller->boardFPGAVersion());
		ui.lblCoreVersion->setText(_controller->boardAPIVersion());

	}
	updateLogs();
}

void TijView::updateLogs()
{
	if (_errorsLogTable != nullptr)
	{
		if (_controller) {
			QVector<TIJViewerController::PrinterError> log = _controller->errorsLog();
			_errorsLogTable->setRowCount(log.count());

			for (int i = 0; i < log.count(); i++) {
				QTableWidgetItem* itBoard = new QTableWidgetItem(QString("%1").arg(log.at(i).boardId));
				itBoard->setTextAlignment(Qt::AlignCenter);
				QTableWidgetItem* itTStamp = new QTableWidgetItem(QString("%1").arg(log.at(i).timestamp.toString(Qt::SystemLocaleShortDate)));
				QTableWidgetItem* itType = new QTableWidgetItem(log.at(i).type);
				Macsa::Printers::ErrorType type;
				type  = log.at(i).type.toStdString();
				switch (type()) {
					case Macsa::Printers::nErrorType::ERROR:
						itType->setIcon(QIcon(ERROR_ICON));
						break;
					case Macsa::Printers::nErrorType::WARNING:
						itType->setIcon(QIcon(WARN_ICON));
						break;
					case Macsa::Printers::nErrorType::INFORMATION:
						itType->setIcon(QIcon(INFO_ICON));
						break;
					default:
						break;
				}
				QTableWidgetItem* itPriority = new QTableWidgetItem(QString("%1").arg(log.at(i).priority));
				itPriority->setTextAlignment(Qt::AlignCenter);
				QTableWidgetItem* itCode = new QTableWidgetItem(log.at(i).code);
				int col = 0;
				_errorsLogTable->setItem(i, col++, itTStamp);
				_errorsLogTable->setItem(i, col++, itBoard);
				_errorsLogTable->setItem(i, col++, itType);
				_errorsLogTable->setItem(i, col++, itPriority);
				_errorsLogTable->setItem(i, col++, itCode);
			}
			resizeErrorsLog();
		}
		else {
			_errorsLogTable->clear();
		}
	}
}

void TijView::setPrinterStatus(TIJViewerController::TijStatus status)
{
	bool connected = false;
	switch (status) {
		case TIJViewerController::TijStatus::DISCONNECTED:
			ui.lblPrinterStatus->setText("Disconnected");
			ui.lblPrinterStatus->setStyleSheet("color:#333;");
			break;
		case TIJViewerController::TijStatus::CONNECTING:
			ui.lblPrinterStatus->setText("Connectiong");
			ui.lblPrinterStatus->setStyleSheet("color:#F80;");
			break;
		case TIJViewerController::TijStatus::STOPPED:
			connected = true;
			ui.lblPrinterStatus->setText("Stopped");
			ui.lblPrinterStatus->setStyleSheet("color:#900;");
			break;
		case TIJViewerController::TijStatus::RUNNING:
			connected = true;
			ui.lblPrinterStatus->setText("Running");
			ui.lblPrinterStatus->setStyleSheet("color:#050;");
			break;
		case TIJViewerController::TijStatus::WARNING:
			connected = true;
			ui.lblPrinterStatus->setText("Warning");
			ui.lblPrinterStatus->setStyleSheet("color:#F80;");
			break;
		case TIJViewerController::TijStatus::PRINTING:
			connected = true;
			ui.lblPrinterStatus->setText("Printing");
			ui.lblPrinterStatus->setStyleSheet("color:#090;");
			break;
	}

	ui.butConnect->setText(((connected) ? "Disconnect" : "Connect"));
	ui.butConnect->setChecked(connected);

}

void TijView::clear()
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}

	setPrinterStatus(TIJViewerController::TijStatus::DISCONNECTED);
	ui.lblPrinterName->setText("");
	ui.lblTime->setText("");
	ui.lblDate->setText("");
	ui.lblCtrlVersion->setText("---");
	ui.lblCoreVersion->setText("---");
	ui.lblFPGAVersion->setText("---");
}

void TijView::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	resizeErrorsLog();
}

void TijView::buildStatus()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsStatus);
	layout->setMargin(0);

	_statusView = new TijStatusView(ui.WidgetContentsStatus);
	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_statusView);

	clear();
}

void TijView::buildConfig()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsConfig);
	layout->setMargin(0);

	_configView = new TijConfigView(ui.WidgetContentsConfig);
	connect(_configView, SIGNAL(configChangeRequested()), SLOT(onRequestedChanges()), Qt::QueuedConnection);

	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_configView);

	clear();
}

void TijView::buildComms()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsNetwork);
	layout->setMargin(0);

	_commsView = new TijCommsView(ui.WidgetContentsConfig);

	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_commsView);

	clear();

}

void TijView::buildFiles()
{
	_filesView = new TijFilesView(this);
	QVBoxLayout *layout = new QVBoxLayout(ui.tabFiles);
	layout->setMargin(0);
	layout->addWidget(_filesView);
}

void TijView::buildErrorsLog()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.tabLogs);
	layout->setMargin(3);
	_errorsLogTable = new QTableWidget(ui.tabLogs);
	layout->addWidget(_errorsLogTable);

	QStringList headers;
	headers << "Timestamp" << "Board Id"  << "Type" << "Priority" << "Code";
	_errorsLogTable->setColumnCount(headers.count());
	_errorsLogTable->setHorizontalHeaderLabels(headers);
	resizeErrorsLog();
}

void TijView::resizeErrorsLog()
{
	if(_errorsLogTable != nullptr && _errorsLogTable->rowCount()) {
	   int w = 0;
	   int c = 0;
	   _errorsLogTable->setColumnWidth(c++, 100); w += 100;
	   _errorsLogTable->setColumnWidth(c++, 70); w += 70;
	   _errorsLogTable->setColumnWidth(c++, 100); w += 100;
	   _errorsLogTable->setColumnWidth(c++, 70); w += 70;
	   if (_errorsLogTable->width() > 400){
		   w = _errorsLogTable->width() - (w + 19);
	   }
	   else {
		   w = 400;
	   }
	   _errorsLogTable->setColumnWidth(c, w);
	}
}

void TijView::onRequestLive()
{
	if (_controller) {
		_controller->requestLive();
	}
	refresh();
}

void TijView::onRequestConfig()
{
	if (_controller) {
		_controller->requestConfig();
	}
	refresh();
}

void TijView::onRequestStatus()
{
	if (_controller) {
		_controller->requestStatus();
	}
	refresh();
}

void TijView::onRequestFiles()
{
	if (_controller) {
		_controller->requestAllFiles();
	}
	refresh();
}

void TijView::onRequestFonts()
{
	if (_controller) {
		_controller->requestFontFiles();
	}
	refresh();
}

void TijView::onRequestImages()
{
	if (_controller) {
		_controller->requestImagesFiles();
	}
	refresh();
}

void TijView::onRequestMessages()
{
	if (_controller) {
		_controller->requestMessagesFiles();
	}
	refresh();
}

void TijView::onRequestErrorsLog()
{
	if (_controller) {
		_controller->requestErrorsList();
	}
	refresh();

}

void TijView::onConnectClicked()
{
	if (_controller != nullptr) {
		TIJViewerController::TijStatus status = _controller->printerStatus();
		if (status == TIJViewerController::TijStatus::DISCONNECTED){
			_controller->controller().connect();
		}
		else {
			_controller->controller().disconnect();
		}
		refresh();
	}
}

void TijView::onRequestedChanges()
{
	if (_controller != nullptr) {
//		_controller->updatePrinterData(); //Deprecated
		refresh();
	}
}

void TijView::onUpdateDateTime()
{
	if (_controller) {
		ui.lblTime->setText(_controller->printerDateTime("hh:mm:ss"));
		ui.lblDate->setText(_controller->printerDateTime("yyyy/MM/dd"));
	}
	else {
		_dtTimer.stop();
	}
}
