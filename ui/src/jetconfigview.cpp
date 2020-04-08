#include "jetconfigview.h"
#include "QFormLayout"
#include <QTimer>
#include "jet/datatypes.h"
//#include "jetmessageselector.h"

#include <QDebug>

#define TITLE_CSS "QLabel {Background-color:#333; color:#DDD; margin: 3px 3px 3px 3px;} "

using namespace Macsa::Printers;

JetConfigView::JetConfigView(QWidget *parent) :
	QWidget(parent)
{
	_controller = nullptr;
	build();
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

JetConfigView::~JetConfigView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void JetConfigView::setController(Macsa::MComms::JetController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new JetViewerController(controller);
	connect(_controller, SIGNAL(printerConfigChanged()), SLOT(refresh()));
	refresh();
}

void JetConfigView::refresh()
{
	if ((_controller != nullptr) && (_controller->printerStatus() != JetViewerController::JetStatus::DISCONNECTED)) {
		updateGeneralSettings();
		updatePrintSetup();
//		updateIOSettings();
	}
	else {
		printerDisconnected();
	}
}

void JetConfigView::build()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(getTitle("Printer General Settings:"));
	layout->addWidget(buildGeneralSettings());
	layout->addSpacing(10);
	layout->addWidget(getTitle("Print Setup"));
	layout->addWidget(buildPrintSetup());
	layout->addSpacing(10);
//	layout->addWidget(getTitle("IO Setup"));
//	layout->addWidget(buildIOSetup());
//	layout->addStretch();
}

QWidget *JetConfigView::buildGeneralSettings()
{
	QWidget * generalSettings = new QWidget(this);
	QFormLayout* layout = new QFormLayout(generalSettings);
	layout->setSpacing(6);

	_butEnable = new QPushButton("Start", generalSettings);
        _butEnable->setFixedWidth(150);
		connect(_butEnable, SIGNAL(clicked(bool)), SLOT(onStartStop()));

	_printingList = new QCheckBox(generalSettings);
//		connect(_printingList, SIGNAL(clicked(bool)), SLOT(onToggleLowLevel()));

		//General config
//		QCheckBox*   _sendMessageAfterPrint;
//		QCheckBox*   _useFifo;
//		QCheckBox*   _delayinPoints;
//		QCheckBox*   _stbIncSCC;
//		QCheckBox*   _stbResetList;
//		QCheckBox*   _OptimizeBarcode;
//		QLabel*		 _userMessage;
//		QPushButton* _butMessage;
//		QComboBox*   _overlappingMode;
//		QComboBox*   _printMode;
//		QComboBox*   _defaultFont;



	QWidget* userMessage =  new QWidget(generalSettings);
	QHBoxLayout	* umLayout = new QHBoxLayout(userMessage);
	umLayout->setMargin(0);
	umLayout->setSpacing(10);
	_userMessage = new QLabel(userMessage);
	_butMessage = new QPushButton(userMessage);
	_butMessage->setText("");
	_butMessage->setIcon(QIcon(":/icons/folder_open.svg"));
	_butMessage->setIconSize(QSize(24,24));
	_butMessage->setFixedSize(QSize(30, 30));
//	connect(_butMessage, SIGNAL(clicked(bool)), SLOT(onSelectUserMessage()));

	umLayout->addWidget(_userMessage);
	umLayout->addWidget(_butMessage);
	umLayout->addStretch();



	layout->addRow("Enable print:", _butEnable);
//	layout->addRow("Autostart:", _printInverted);
	layout->addRow("Use printing list:", _printingList);
	layout->addRow("Current message:", userMessage);

	return generalSettings;
}

QWidget *JetConfigView::buildPrintSetup()
{
	QWidget * printSetup = new QWidget(this);
	QFormLayout* layout = new QFormLayout(printSetup);
	layout->setSpacing(6);

	//Print rotated
	_printInverted = new QCheckBox(printSetup);
	connect(_printInverted, SIGNAL(clicked(bool)), SLOT(onToggleInverted()));
	//Print direction
	_printDirection = new QComboBox(printSetup);
	_printDirection->addItems(getPrinterEnumOptions(Macsa::Printers::PrintDirection()));
	_printDirection->setMaximumWidth(100);

	_horizontalResolution = new QSpinBox(printSetup);
	_horizontalResolution->setRange(100, 600);

	//Encoder
	_encoderMode = new QComboBox(printSetup);
	QStringList encoderModes;
	Macsa::Printers::EncoderMode mode;
	mode = Macsa::Printers::nEncoderMode::FIXED_SPEED;
	encoderModes << mode.toString().c_str();
	mode = Macsa::Printers::nEncoderMode::EXTERNAL_ENCODER;
	encoderModes << mode.toString().c_str();
	_encoderMode->addItems(encoderModes);
	_encoderMode->setMaximumWidth(100);
		//Fixed
	QWidget *fixedEncoder = new QWidget(printSetup);
	QHBoxLayout* feLayout = new QHBoxLayout(fixedEncoder);
	feLayout->setMargin(0);
	feLayout->setSpacing(6);
	_fixedSpeed = new QSpinBox(fixedEncoder);
	_fixedSpeed->setRange(0, 200);
	feLayout->addWidget(_fixedSpeed);
	feLayout->addWidget(new QLabel("m/min"));
	feLayout->addStretch();
		//External
	QWidget *externalEncoder = new QWidget(printSetup);
	QHBoxLayout* eeLayout = new QHBoxLayout(externalEncoder);
	eeLayout->setMargin(0);
	eeLayout->setSpacing(6);
	_encoderPulses = new QSpinBox(externalEncoder);
	_encoderPulses->setRange(0, 99999);
	_encoderWheel = new QSpinBox(externalEncoder);
	_encoderWheel->setRange(0, 200);
	_encoderAbcPitch = new QSpinBox(externalEncoder);
	_encoderWheel->setRange(0, 200);
	eeLayout->addWidget(new QLabel("Pulses:"));
	eeLayout->addWidget(_encoderPulses);
	eeLayout->addSpacing(15);
	eeLayout->addWidget(new QLabel("Wheel diameter:"));
	eeLayout->addWidget(_encoderWheel);
	eeLayout->addWidget(new QLabel("mm"));
	eeLayout->addSpacing(15);
	eeLayout->addWidget(new QLabel("ABC Pitch:"));
	eeLayout->addWidget(_encoderAbcPitch);
	eeLayout->addStretch();

	layout->addRow("Print Rotated:", _printInverted);
	layout->addRow("H Resolution:", _horizontalResolution);
	layout->addRow("Encoder mode:", _encoderMode);
	layout->addRow("Fixed speed:", fixedEncoder);
	layout->addRow("External encoder:", externalEncoder);
	layout->addRow("Print direction:", _printDirection);

	return printSetup;
}

//QWidget *JetConfigView::buildIOSetup()
//{
//	QWidget * ioSettings = new QWidget(this);
//	QVBoxLayout* layout = new QVBoxLayout(ioSettings);
//	layout->setSpacing(6);

//	_inputs = new QTableWidget(ioSettings);
//	QStringList inHeaders;
//	inHeaders << "Id" << "Descriptor" << "Mode" << "Inverted" << "Filter" << "Id" << "Descriptor" << "Mode" << "Inverted" << "Filter";
//	_inputs->setColumnCount(inHeaders.count());
//	_inputs->setHorizontalHeaderLabels(inHeaders);
//	_inputs->setFixedHeight(264);


//	_outputs = new QTableWidget(ioSettings);
//	QStringList outHeaders;
//	outHeaders << "Id" << "Descriptor" << "Type" << "Time" << "Initial value";
//	_outputs->setColumnCount(outHeaders.count());
//	_outputs->setHorizontalHeaderLabels(outHeaders);
//	_outputs->setFixedHeight(175);


//	layout->addWidget(new QLabel("Inputs:"));
//	layout->addWidget(_inputs);
//	layout->addSpacing(8);
//	layout->addWidget(new QLabel("Outputs:"));
//	layout->addWidget(_outputs);

//	return ioSettings;
//}

void JetConfigView::updateGeneralSettings()
{
	_butEnable->setChecked(_controller->paused());
	if (!_controller->paused()) {
		_butEnable->setText("Stop");
	}
	else {
		_butEnable->setText("Print");
	}
	_printInverted->setChecked(_controller->bitmapInverted());
	_printingList->setChecked(_controller->printerPrinthead().printingList());

	_userMessage->setText(_controller->currentMessage().c_str());
}

void JetConfigView::updatePrintSetup()
{
	_printInverted->setChecked(_controller->bitmapInverted());
	_horizontalResolution->setValue(static_cast<int>(_controller->printerPrinthead().horizontalResolution()));
	_encoderMode->setCurrentIndex(_controller->printerPrinthead().encoder().mode()());
	_fixedSpeed->setValue(static_cast<int>(_controller->printerPrinthead().encoder().fixedSpeed()));
	_encoderWheel->setValue(static_cast<int>(_controller->printerPrinthead().encoder().diameter()));
	_encoderPulses->setValue(static_cast<int>(_controller->printerPrinthead().encoder().resolution()));
	_printDirection->setCurrentIndex(_controller->printDirection()());
}

//void JetConfigView::updateIOSettings()
//{
//	QVector<JetViewerController::PrinterInput> inputs = _controller->inputs();
//	QVector<JetViewerController::PrinterOutput> outputs = _controller->outputs();

//	_inputs->setRowCount((inputs.count() / 2) + 1);
//	_outputs->setRowCount(outputs.count());
//	for (int i = 0, row = 0; i < inputs.count(); ++i, row++) {
//		row = (row >= 8) ? 0 : row;
//		int fCol = (i / 8 == 0) ? 0 : _inputs->columnCount() / 2;
//		addInputRow(_inputs, row, fCol, inputs.at(i));
//	}

//	for (int o = 0; o < outputs.count(); ++o) {
//		addOutputRow(_outputs, o, outputs.at(o));
//	}

//}

void JetConfigView::printerDisconnected()
{
	//General Settings
	_butEnable->setText("Disconnected");
	_printInverted->setChecked(false);
	_printingList->setChecked(false);
}


QLabel *JetConfigView::getTitle(const QString &text)
{
	QLabel * title = new QLabel(text, this);
	title->setMargin(6);
	title->setStyleSheet(TITLE_CSS);
	return title;
}

//void JetConfigView::addInputRow(QTableWidget *table, int row, int iniCol, const JetViewerController::PrinterInput &input)
//{
//	QTableWidgetItem * item  = new QTableWidgetItem(QString("%1").arg(input.id));
//	item->setTextAlignment(Qt::AlignCenter);
//	table->setItem(row, iniCol++, item);

//	table->setItem(row, iniCol++, new QTableWidgetItem(input.descriptor));

//	item  = new QTableWidgetItem(input.mode);
//	item->setTextAlignment(Qt::AlignCenter);
//	table->setItem(row, iniCol++, item);

//	item  = new QTableWidgetItem((input.inverted ? "Inverted" : "Normal"));
//	item->setTextAlignment(Qt::AlignCenter);
//	table->setItem(row, iniCol++, item);

//	item  = new QTableWidgetItem(QString("%1").arg(input.filter));
//	item->setTextAlignment(Qt::AlignCenter);
//	table->setItem(row, iniCol++, item);

//}

//void JetConfigView::addOutputRow(QTableWidget *table, int row, const JetViewerController::PrinterOutput &output)
//{
//	QTableWidgetItem * item  = new QTableWidgetItem(QString("%1").arg(output.id));
//	item->setTextAlignment(Qt::AlignCenter);
//	table->setItem(row, 0, item);

//	table->setItem(row, 1, new QTableWidgetItem(output.descriptor));

//	item  = new QTableWidgetItem(output.type);
//	item->setTextAlignment(Qt::AlignCenter);
//	table->setItem(row, 2, item);

//	item  = new QTableWidgetItem(QString("%1").arg(output.time));
//	table->setItem(row, 3, item);

//	item  = new QTableWidgetItem((output.initialValue ? "ON" : "OFF"));
//	item->setTextAlignment(Qt::AlignCenter);
//	table->setItem(row, 4, item);

//}

//void JetConfigView::resizeEvent(QResizeEvent *event)
//{
//	QWidget::resizeEvent(event);
//}

void JetConfigView::onStartStop()
{
	if (_controller) {
		_controller->setPause(!_controller->paused());
	}
}

void JetConfigView::onToggleInverted()
{
	if (_controller) {
		_controller->setPrintBitmapInverted(_printInverted->isChecked());
	}
}

void JetConfigView::onChangeResolution(int hres)
{
	if (_controller) {

//		if (_controller->setPrintRotated(!_controller->enabled())) {
//			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
//		}
	}
}

//void JetConfigView::onSelectUserMessage()
//{
//	if (_controller){
//		TijMessageSelectorDialog selector(_controller->controller(), this);
//		if (selector.exec()){
//			QString msg = selector.selectedMessage();
//			if (msg.length()){
//				_controller->controller().setUserMessage(msg.toStdString());
//			}
//		}
//	}
//}

template<typename N>
QStringList JetConfigView::getPrinterEnumOptions(const Macsa::Utils::SmartEnum<N> &e) const
{
	QStringList list;
	std::vector<std::string> eList = e.stringList();
	for (uint var = 0; var < eList.size(); ++var) {
		list << eList.at(var).c_str();
	}
	return list;
}

