#include "jetview.h"
#include "tij/datatypes.h"
#include <QScrollArea>

#define ERROR_ICON	":/icons/error.svg"
#define WARN_ICON	":/icons/warning.svg"
#define INFO_ICON	":/icons/notification.svg"

using JetLogList = Macsa::Printers::JetPrinter::logsList;

JetView::JetView(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	_controller = nullptr;

	connect(ui.butReqConfig, SIGNAL(clicked(bool)), SLOT(onRequestConfig()));
	connect(ui.butReqStatus, SIGNAL(clicked(bool)), SLOT(onRequestStatus()));
//	connect(ui.butFiles, SIGNAL(clicked(bool)), SLOT(onRequestFiles()));
	connect(ui.butConnect, SIGNAL(clicked(bool)), SLOT(onConnectClicked()));
//	connect(ui.butGetFonts, SIGNAL(clicked(bool)), SLOT(onRequestFonts()));
//	connect(ui.butGetImages, SIGNAL(clicked(bool)), SLOT(onRequestImages()));
//	connect(ui.butGetMessages, SIGNAL(clicked(bool)), SLOT(onRequestMessages()));
//	connect(ui.butGetErrors, SIGNAL(clicked(bool)), SLOT(onRequestErrorsLog()));

	_dtTimer.setParent(this);
	_dtTimer.setInterval(1000);
	connect(&_dtTimer, SIGNAL(timeout()), SLOT(onUpdateDateTime()));

	buildStatus();
	buildConfig();
	buildMessageManager();
//	buildComms();
	buildFiles();
	buildErrorsLog();
	setPrinterStatus(JetViewerController::JetStatus::DISCONNECTED);
}

JetView::~JetView()
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}
}

void JetView::setController(Macsa::MComms::JetController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}
	_controller = new JetViewerController(controller);
	_statusView->setController(controller);
	_configView->setController(controller);
	_messageManager->setController(controller);
//	_commsView->setController(controller);
	_filesView->setController(controller);
	refresh();
	if (!_dtTimer.isActive()) {
		_dtTimer.start();
	}
	connect(_controller, SIGNAL(printerStatusChanged()), SLOT(refresh()));
}

void JetView::refresh()
{
	this->setEnabled(_controller != nullptr);
	if (_controller) {
		QString name = _controller->id();
		QString addr = _controller->address();
		ui.lblPrinterName->setText(QString("%1: %2").arg(name).arg(addr));

		setPrinterStatus(_controller->printerStatus());

		onUpdateDateTime();

		ui.lblVersionPh->setText(_controller->printheadVersion().c_str());
//		ui.lblVersionSignal->setText(_controller->printheadVersion().c_str());

	}
	updateLogs();
}

void JetView::updateLogs()
{
	if (_printerErrorsLog != nullptr)
	{
		if (_controller) {

			JetLogList log = _controller->printerLogs();
			_printerErrorsLog->setRowCount(static_cast<int>(log.size()));

			int row = 0;
			for (JetLogList::const_iterator it = log.begin(); it != log.end(); it++, row++) {
				QDateTime dt = QDateTime::fromTime_t(static_cast<uint>(it->timestamp()));
				QTableWidgetItem* itTStamp = new QTableWidgetItem(QString("%1").arg(dt.toString(Qt::SystemLocaleShortDate)));
				QTableWidgetItem* itType = new QTableWidgetItem(it->type().toString().c_str());
				Macsa::Printers::JetLogType type = it->type();
				switch (type()) {
					case Macsa::Printers::nJetLogType::LOG_TYPE_WARN:
						itType->setIcon(QIcon(WARN_ICON));
						break;
					case Macsa::Printers::nJetLogType::LOG_TYPE_ERR:
						itType->setIcon(QIcon(ERROR_ICON));
						break;
					case Macsa::Printers::nJetLogType::LOG_TYPE_INFO:
					case Macsa::Printers::nJetLogType::LOG_TYPE_SUCCESS:
						itType->setIcon(QIcon(INFO_ICON));
						break;
					default:
						break;
				}
				QString message = QString::fromUtf8(it->message().c_str());
				QTableWidgetItem* itMessage = new QTableWidgetItem(message);
				int col = 0;
				_printerErrorsLog->setItem(row, col++, itTStamp);
				_printerErrorsLog->setItem(row, col++, itType);
				_printerErrorsLog->setItem(row, col++, itMessage);
			}
			resizeErrorsLog();
		}
		else {
			_printerErrorsLog->clear();
		}
	}
}

void JetView::setPrinterStatus(JetViewerController::JetStatus status)
{
	bool connected = false;
	switch (status) {
		case JetViewerController::JetStatus::DISCONNECTED:
			ui.lblPrinterStatus->setText("Disconnected");
			ui.lblPrinterStatus->setStyleSheet("color:#333;");
			break;
		case JetViewerController::JetStatus::CONNECTING:
			ui.lblPrinterStatus->setText("Connectiong");
			ui.lblPrinterStatus->setStyleSheet("color:#F80;");
			break;
		case JetViewerController::JetStatus::STOPPED:
			connected = true;
			ui.lblPrinterStatus->setText("Stopped");
			ui.lblPrinterStatus->setStyleSheet("color:#900;");
			break;
		case JetViewerController::JetStatus::ERROR:
			connected = true;
			ui.lblPrinterStatus->setText("Error");
			ui.lblPrinterStatus->setStyleSheet("color:#900;");
			break;
		case JetViewerController::JetStatus::RUNNING:
			connected = true;
			ui.lblPrinterStatus->setText("Running");
			ui.lblPrinterStatus->setStyleSheet("color:#050;");
			break;
		case JetViewerController::JetStatus::PRINTING:
			connected = true;
			ui.lblPrinterStatus->setText("Printing");
			ui.lblPrinterStatus->setStyleSheet("color:#090;");
			break;
	}

	ui.butConnect->setText(((connected) ? "Disconnect" : "Connect"));
	ui.butConnect->setChecked(connected);

}

void JetView::clear()
{
	if (_controller != nullptr) {
		delete _controller;
		_controller = nullptr;
	}

	setPrinterStatus(JetViewerController::JetStatus::DISCONNECTED);
	ui.lblPrinterName->setText("");
	ui.lblTime->setText("-:-:-");
	ui.lblDate->setText("-/-/-");
	ui.lblVersionPh->setText("---");
}

void JetView::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	resizeErrorsLog();
}

void JetView::buildStatus()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsStatus);
	layout->setMargin(0);

	_statusView = new JetStatusView(ui.WidgetContentsStatus);
	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_statusView);

	clear();
}

void JetView::buildConfig()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsConfig);
	layout->setMargin(0);

	_configView = new JetConfigView(ui.WidgetContentsConfig);

	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_configView);

	clear();
}

void JetView::buildMessageManager()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsMessages);
	layout->setMargin(0);

	_messageManager = new JetMessageManager(ui.WidgetContentsMessages);

	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout->addWidget(_messageManager);
	clear();
}

//void JetView::buildComms()
//{
//	QVBoxLayout* layout = new QVBoxLayout(ui.WidgetContentsNetwork);
//	layout->setMargin(0);

//	_printerCommsView = new PrinterCommsView(ui.WidgetContentsConfig);

//	layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
//	layout->addWidget(_printerCommsView);

//	clear();

//}

void JetView::buildFiles()
{
	_filesView = new JetFilesView(this);
	QVBoxLayout *layout = new QVBoxLayout(ui.tabFiles);
	layout->setMargin(0);
	layout->addWidget(_filesView);
}

void JetView::buildErrorsLog()
{
	QVBoxLayout* layout = new QVBoxLayout(ui.tabLogs);
	layout->setMargin(3);
	_printerErrorsLog = new QTableWidget(ui.tabLogs);
	layout->addWidget(_printerErrorsLog);

	QStringList headers;
	headers << "Timestamp" << "Type" << "Message";
	_printerErrorsLog->setColumnCount(headers.count());
	_printerErrorsLog->setHorizontalHeaderLabels(headers);
	resizeErrorsLog();
}

void JetView::resizeErrorsLog()
{
	if(_printerErrorsLog != nullptr && _printerErrorsLog->rowCount()) {
	   int w = 0;
	   int c = 0;
	   _printerErrorsLog->setColumnWidth(c++, 110); w += 110;
	   _printerErrorsLog->setColumnWidth(c++, 100); w += 100;
	   if (_printerErrorsLog->width() > w + 26){
		   w = _printerErrorsLog->width() - (w + 26);
	   }
	   else {
		   w = 400;
	   }
	   _printerErrorsLog->setColumnWidth(c, w);
	}
}

void JetView::onRequestConfig()
{
	if (_controller) {
		_controller->getConfig();
	}
}

void JetView::onRequestStatus()
{
	if (_controller) {
		_controller->getStatus();
	}
}

//void JetView::onRequestFiles()
//{
//	if (_controller) {
//		_controller->requestAllFiles();
//	}
//	refresh();
//}

//void JetView::onRequestFonts()
//{
//	if (_controller) {
//		_controller->requestFontFiles();
//	}
//	refresh();
//}

//void JetView::onRequestImages()
//{
//	if (_controller) {
//		_controller->requestImagesFiles();
//	}
//	refresh();
//}

//void JetView::onRequestMessages()
//{
//	if (_controller) {
//		_controller->requestMessagesFiles();
//	}
//	refresh();
//}

//void JetView::onRequestErrorsLog()
//{
//	if (_controller) {
//		_controller->requestErrorsList();
//	}
//	refresh();

//}

void JetView::onConnectClicked()
{
	if (_controller != nullptr) {
		JetViewerController::JetStatus status = _controller->printerStatus();
		if (status == JetViewerController::JetStatus::DISCONNECTED){
			if (_controller->controller().connect()){
				refresh();
			}
		}
		else {
			_controller->controller().disconnect();
		}
	}
}

void JetView::onUpdateDateTime()
{
	if (_controller) {
		QDateTime dt = QDateTime::fromTime_t(static_cast<uint>(_controller->dateTime()));

		ui.lblTime->setText(dt.toString("hh:mm:ss"));
		ui.lblDate->setText(dt.toString("yyyy/MM/dd"));
	}
	else {
		_dtTimer.stop();
	}
}
