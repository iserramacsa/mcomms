#include "printerconfigview.h"
#include "QFormLayout"
#include <QTimer>
#include "printer/datatypes.h"

#include <QDebug>

#define TITLE_CSS "QLabel {Background-color:#333; color:#DDD; margin: 3px 3px 3px 3px;} "

using namespace Macsa::Printers;

PrinterConfigView::PrinterConfigView(QWidget *parent) :
	QWidget(parent)
{
	_controller = nullptr;
	build();
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

PrinterConfigView::~PrinterConfigView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void PrinterConfigView::setController(Macsa::TIJPrinterController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new TIJViewerController(controller);
	refresh();
}

void PrinterConfigView::refresh()
{
	if ((_controller != nullptr) && (_controller->printerStatus() != TIJViewerController::TIJStatus::DISCONNECTED)) {
		updateGeneralSettings();
		updatePrintSetup();
		updateTriggerSetup();
		updateBcdTable();
		updateDateCodes();
		updateCartridgeSettings();
		updateIOSettings();
	}
	else {
		printerDisconnected();
	}
}

void PrinterConfigView::build()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(getTitle("Printer General Settings:"));
	layout->addWidget(buildGeneralSettings());
	layout->addSpacing(10);
	layout->addWidget(getTitle("Print Setup"));
	layout->addWidget(buildPrintSetup());
	layout->addSpacing(10);
	layout->addWidget(getTitle("BCD Table"));
	layout->addWidget(buildBcdTable());
	layout->addSpacing(10);
	layout->addWidget(getTitle("Trigger Setup"));
	layout->addWidget(buildTriggerSetup());
	layout->addSpacing(10);
	layout->addWidget(getTitle("Date & Shift codes"));
	layout->addWidget(buildDateCodesSetup());
	layout->addSpacing(10);
	layout->addWidget(getTitle("Cartridge Setup"));
	layout->addWidget(buildCartridgeSetup());
	layout->addSpacing(10);
	layout->addWidget(getTitle("IO Setup"));
	layout->addWidget(buildIOSetup());
	layout->addStretch();
}

QWidget *PrinterConfigView::buildGeneralSettings()
{
	QWidget * generalSettings = new QWidget(this);
	QFormLayout* layout = new QFormLayout(generalSettings);
	layout->setSpacing(6);

	_butEnable = new QPushButton("Start", generalSettings);
        _butEnable->setFixedWidth(150);
		connect(_butEnable, SIGNAL(clicked(bool)), SLOT(onStartStop()));
	_printAutostart = new QCheckBox(generalSettings);
		connect(_printAutostart, SIGNAL(clicked(bool)), SLOT(onToggleAutoStart()));
	_lowLevelOutput = new QCheckBox(generalSettings);
		connect(_lowLevelOutput, SIGNAL(clicked(bool)), SLOT(onToggleLowLevel()));
	_blockCartridge = new QCheckBox(generalSettings);
		connect(_blockCartridge, SIGNAL(clicked(bool)), SLOT(onToggleBlockCartridge()));

	layout->addRow("Enable print:", _butEnable);
	layout->addRow("Autostart:", _printAutostart);
	layout->addRow("Enable low level output:", _lowLevelOutput);
	layout->addRow("Block cartridge:", _blockCartridge);

	return generalSettings;
}

QWidget *PrinterConfigView::buildPrintSetup()
{
	QWidget * printSetup = new QWidget(this);
	QFormLayout* layout = new QFormLayout(printSetup);
	layout->setSpacing(6);

	//Print rotated
	_printRotated = new QCheckBox(printSetup);
	connect(_printRotated, SIGNAL(clicked(bool)), SLOT(onToggleRotated()));

	//Print resolution
	QWidget* resolution = new QWidget(printSetup);
	QHBoxLayout* resLayout = new QHBoxLayout(resolution);
	resLayout->setMargin(0);
	resLayout->setSpacing(6);

	_printResolution = new QComboBox(printSetup);
	_printResolution->addItems(printResolutions());

	_nozzlesCols = new QComboBox(printSetup);
	_nozzlesCols->addItems(getPrinterEnumOptions(Macsa::Printers::NozzlesCol()));

	resLayout->addWidget(_printResolution);
	resLayout->addWidget(new QLabel("Nozzles column:"));
	resLayout->addWidget(_nozzlesCols);
	resLayout->addStretch();

	//Photocell
	_photocell = new QComboBox(printSetup);
	_photocell->addItems(getPrinterEnumOptions(Macsa::Printers::Photocell()));
	_photocell->setMaximumWidth(100);

	//Encoder
	_encoderMode = new QComboBox(printSetup);
	_encoderMode->addItems(getPrinterEnumOptions(Macsa::Printers::EncoderMode()));
	_encoderMode->setMaximumWidth(100);
		//Fixed
	QWidget *fixedEncoder = new QWidget(printSetup);
	QHBoxLayout* feLayout = new QHBoxLayout(fixedEncoder);
	feLayout->setMargin(0);
	feLayout->setSpacing(6);
	_fixedSpeed = new QDoubleSpinBox(fixedEncoder);
	_fixedSpeed->setRange(0, 200);
	_fixedSpeed->setDecimals(1);
	feLayout->addWidget(_fixedSpeed);
	feLayout->addWidget(new QLabel("m/min"));
	feLayout->addStretch();
		//External
	QWidget *externalEncoder = new QWidget(printSetup);
	QHBoxLayout* eeLayout = new QHBoxLayout(externalEncoder);
	eeLayout->setMargin(0);
	eeLayout->setSpacing(6);
	_encoderResolution = new QDoubleSpinBox(externalEncoder);
	_encoderResolution->setRange(0, 99999);
	_encoderResolution->setDecimals(0);
	_encoderWheelDiam = new QDoubleSpinBox(externalEncoder);
	_encoderWheelDiam->setRange(0, 200);
	_encoderWheelDiam->setDecimals(1);
	eeLayout->addWidget(new QLabel("Resolution:"));
	eeLayout->addWidget(_encoderResolution);
	eeLayout->addWidget(new QLabel("ppr"));
	eeLayout->addSpacing(15);
	eeLayout->addWidget(new QLabel("Wheel diameter:"));
	eeLayout->addWidget(_encoderWheelDiam);
	eeLayout->addWidget(new QLabel("mm"));
	eeLayout->addStretch();


	_printDirection = new QComboBox(printSetup);
	_printDirection->addItems(getPrinterEnumOptions(Macsa::Printers::PrinterDir()));
	_printDirection->setMaximumWidth(100);

	_bcdMode = new QComboBox(printSetup);
	_bcdMode->addItems(getPrinterEnumOptions(Macsa::Printers::BCDMode()));
	_bcdMode->setMaximumWidth(100);

	layout->addRow("Print Rotated:", _printRotated);
	layout->addRow("Resolution:", resolution);
	layout->addRow("Photocell input:", _photocell);
	layout->addRow("Encoder mode:", _encoderMode);
	layout->addRow("Fixed speed:", fixedEncoder);
	layout->addRow("External encoder:", externalEncoder);
	layout->addRow("Print direction:", _printDirection);
	layout->addRow("BCD mode:", _bcdMode);

	return printSetup;
}

QWidget *PrinterConfigView::buildTriggerSetup()
{
	QWidget * triggerSetup = new QWidget(this);
	QFormLayout* layout = new QFormLayout(triggerSetup);
	layout->setSpacing(6);

	_multiprint = new QCheckBox(triggerSetup);
	connect(_multiprint, SIGNAL(toggled(bool)), SLOT(validateTriggerSettings()));

	QWidget * multi = new QWidget(triggerSetup);
	QHBoxLayout* mLayout = new QHBoxLayout(multi);
	mLayout->setMargin(0);
	mLayout->setSpacing(6);
	_numPrints = new QSpinBox(triggerSetup);
	_repeatPrint = new QCheckBox(triggerSetup);
	mLayout->addWidget(_numPrints);
	mLayout->addSpacing(15);
	mLayout->addWidget(new QLabel("Repeat prints:", multi));
	mLayout->addWidget(_repeatPrint);
	mLayout->addStretch();

	layout->addRow("Enable multiprint:", _multiprint);
	layout->addRow("Num prints:", multi);
	layout->addRow("First delay", buildPrintDelay(triggerSetup, &_firstDelay));
	layout->addRow("Delay between prints:", buildPrintDelay(triggerSetup, &_nextDelay));

	return triggerSetup;
}

QWidget *PrinterConfigView::buildDateCodesSetup()
{
	QWidget * dateCodes = new QWidget(this);
	return dateCodes;
}

QWidget *PrinterConfigView::buildBcdTable()
{
	_bcdTable = new QTableWidget(this);
	_bcdTable->setColumnCount(4);
	_bcdTable->setAlternatingRowColors(true);
	_bcdTable->setHorizontalHeaderLabels(QStringList() << "Code" << "Message" << "Code" << "Message");
	_bcdTable->setMinimumHeight(264);
	return _bcdTable;
}

QWidget *PrinterConfigView::buildCartridgeSetup()
{
	QWidget * cartridgeSettings = new QWidget(this);
	QFormLayout* layout = new QFormLayout(cartridgeSettings);
	layout->setSpacing(6);

	//Cartridge
	_autoConfig = new QCheckBox(cartridgeSettings);
	connect(_autoConfig, SIGNAL(toggled(bool)), SLOT(validateCartridgeSettings()));
	_pulseWarm = new QCheckBox(cartridgeSettings);

	layout->addRow("Read from cartridge:",	_autoConfig);
	layout->addRow("Firing voltage:",		buildCartridgeSpinBox(cartridgeSettings, &_voltage, "V", 11, 30));
	layout->addRow("Pulse width:",			buildCartridgeSpinBox(cartridgeSettings, &_pulseWidth, "us", 1, 10));
	layout->addRow("Pulse warming:",		_pulseWarm);
	layout->addRow("Pulse warming temp.:",	buildCartridgeSpinBox(cartridgeSettings, &_pulseTemp, QString::fromUtf8("ºC"), 0, 200));
	layout->addRow("Adjusted Capacity:",	buildCartridgeSpinBox(cartridgeSettings, &_adjCapacity, QString::fromUtf8("%"), 0, 100, 0));

	return cartridgeSettings;
}

QWidget *PrinterConfigView::buildIOSetup()
{
	QWidget * ioSettings = new QWidget(this);
	QVBoxLayout* layout = new QVBoxLayout(ioSettings);
	layout->setSpacing(6);

	_inputs = new QTableWidget(ioSettings);
	QStringList inHeaders;
	inHeaders << "Id" << "Descriptor" << "Mode" << "Inverted" << "Filter";
	_inputs->setColumnCount(inHeaders.count());
	_inputs->setHorizontalHeaderLabels(inHeaders);


	_outputs = new QTableWidget(ioSettings);
	QStringList outHeaders;
	outHeaders << "Id" << "Descriptor" << "Type" << "Time" << "Initial value";
	_outputs->setColumnCount(outHeaders.count());
	_outputs->setHorizontalHeaderLabels(outHeaders);


	layout->addWidget(new QLabel("Inputs:"));
	layout->addWidget(_inputs);
	layout->addSpacing(8);
	layout->addWidget(new QLabel("Outputs:"));
	layout->addWidget(_outputs);

	return ioSettings;
}

void PrinterConfigView::updateGeneralSettings()
{
	if (_controller->enabled()) {
		_butEnable->setText("Stop");
	}
	else {
		_butEnable->setText("Print");
	}
	_printAutostart->setChecked(_controller->autoStart());
	_lowLevelOutput->setChecked(_controller->lowLevelOutput());
	_blockCartridge->setChecked(_controller->blocked());
}

void PrinterConfigView::updatePrintSetup()
{
	_printRotated->setChecked(_controller->printRotated());
	_nozzlesCols->setCurrentIndex(_controller->nozzlesCol()());

	_nozzlesCols->setDisabled((_controller->nozzlesCol() == Macsa::Printers::NozzlesCol_n::COL_BOTH));

	QString hres = _controller->configProperty(TIJViewerController::TIJConfigProperties::HRES);
	if (hres != "---"){
		int hresVal = std::atoi(hres.toStdString().c_str());
		switch (hresVal) {
			case 150:
				_printResolution->setCurrentIndex(0);
				break;
			case 200:
				_printResolution->setCurrentIndex(1);
				break;
			case 250:
				_printResolution->setCurrentIndex(2);
				break;
			case 300:
				if (_controller->nozzlesCol() != Macsa::Printers::NozzlesCol_n::COL_BOTH) {
					_printResolution->setCurrentIndex(3);
				}
				else {
					_printResolution->setCurrentIndex(4);
				}
				break;
			case 600:
				_printResolution->setCurrentIndex(5);
				break;
			default:
				break;
		}
	}

	_photocell->setCurrentIndex(_controller->photocell()());
	_encoderMode->setCurrentIndex(_controller->encoderMode()());
	_fixedSpeed->setValue(_controller->encoderFixedSpeed());
	_encoderWheelDiam->setValue(_controller->encoderDiameter());
	_encoderResolution->setValue(_controller->encoderResolution());
	_printDirection->setCurrentIndex(_controller->printDirection()());
	_bcdMode->setCurrentIndex(_controller->bcdMode()());

}

void PrinterConfigView::updateTriggerSetup()
{
	_multiprint->setChecked(_controller->shotMode()() > Macsa::Printers::SINGLE_SHOT);
	_numPrints->setValue(_controller->shotModeNumPrints());
	QVector<uint> delays = _controller->shotModeDelays();
	if (delays.count()) {
		_firstDelay->setValue(static_cast<int>(delays.at(0)));
		if(delays.count() > 1) {
			_nextDelay->setValue(static_cast<int>(delays.at(1)));
		}
	}


	validateTriggerSettings();
}

void PrinterConfigView::updateBcdTable()
{
	QMap<int, QString> table = _controller->bcdTable();
	_bcdTable->setRowCount(table.count() / 2);

	int row = 0;
	for (QMap<int, QString>::const_iterator code = table.begin(); code != table.end(); code++, row++) {
		QTableWidgetItem* itCode = new QTableWidgetItem(QString("%1").arg(code.key()));
		itCode->setTextAlignment(Qt::AlignCenter);
		if ((row / 8) == 0){
			_bcdTable->setItem(row, 0, itCode);
			_bcdTable->setItem(row, 1, new QTableWidgetItem(code.value()));
		}
		else {
			_bcdTable->setItem(row - 8, 2, itCode);
			_bcdTable->setItem(row - 8, 3, new QTableWidgetItem(code.value()));
		}
	}
}

void PrinterConfigView::updateDateCodes()
{
}

void PrinterConfigView::updateCartridgeSettings()
{
	_autoConfig->setChecked(_controller->cartridgeAutoSetup());
	_voltage->setValue(_controller->cartridgeFiringVoltage());
	_pulseWidth->setValue(_controller->cartridgePulseWidth());
	_pulseWarm->setChecked(_controller->cartridgePulseWarming());
	_pulseTemp->setValue(_controller->cartridgePulseWarmTemp());
	_adjCapacity->setValue(_controller->cartridgeAdjustedCapacity());

	validateCartridgeSettings();
}

void PrinterConfigView::updateIOSettings()
{
	QVector<TIJViewerController::PrinterInput> inputs = _controller->inputs();
	QVector<TIJViewerController::PrinterOutput> outputs = _controller->outputs();

	_inputs->setRowCount(inputs.count());
	_outputs->setRowCount(outputs.count());

	for (int i = 0; i < inputs.count(); ++i) {
		addInputRow(_inputs, i, inputs.at(i));
	}

	for (int o = 0; o < outputs.count(); ++o) {
		addOutputRow(_outputs, o, outputs.at(o));
	}

}

void PrinterConfigView::printerDisconnected()
{
	//General Settings
	_butEnable->setText("Disconnected");
	_printAutostart->setChecked(false);
	_lowLevelOutput->setChecked(false);
	_blockCartridge->setChecked(false);
}

QStringList PrinterConfigView::printResolutions() const
{
	QStringList res;
	res << "150h x 300v dpi";
	res << "200h x 300v dpi";
	res << "250h x 300v dpi";
	res << "300h x 300v dpi";
	res << "300h x 600v dpi";
	res << "600h x 600v dpi";
	return res;
}

QWidget* PrinterConfigView::buildPrintDelay(QWidget *parent, QSpinBox ** editor) const
{
	QWidget* delay = new QWidget(parent);
	QHBoxLayout* layout = new QHBoxLayout(delay);
	layout->setMargin(0);
	layout->setSpacing(15);

	*editor = new QSpinBox(delay);
	(*editor)->setRange(0, 1000);

	layout->addWidget(*editor);
	layout->addWidget(new QLabel("dots"));
	layout->addStretch();

	return delay;
}

QWidget *PrinterConfigView::buildCartridgeSpinBox(QWidget *parent, QDoubleSpinBox **editor, const QString &units, int min, int max, int decimals) const
{
	QWidget* spinner = new QWidget(parent);
	QHBoxLayout* layout = new QHBoxLayout(spinner);
	layout->setMargin(0);
	layout->setSpacing(15);

	*editor = new QDoubleSpinBox(spinner);
	(*editor)->setRange(min, max);
	(*editor)->setDecimals(decimals);

	layout->addWidget(*editor);
	layout->addWidget(new QLabel(units));
	layout->addStretch();

	return spinner;
}

QLabel *PrinterConfigView::getTitle(const QString &text)
{
	QLabel * title = new QLabel(text, this);
	title->setMargin(6);
	title->setStyleSheet(TITLE_CSS);
	return title;
}

void PrinterConfigView::addInputRow(QTableWidget *table, int row, const TIJViewerController::PrinterInput &input)
{
	QTableWidgetItem * item  = new QTableWidgetItem(QString("%1").arg(input.id));
	item->setTextAlignment(Qt::AlignCenter);
	table->setItem(row, 0, item);

	table->setItem(row, 1, new QTableWidgetItem(input.descriptor));

	item  = new QTableWidgetItem(input.mode);
	item->setTextAlignment(Qt::AlignCenter);
	table->setItem(row, 2, item);

	item  = new QTableWidgetItem((input.inverted ? "Inverted" : "Normal"));
	item->setTextAlignment(Qt::AlignCenter);
	table->setItem(row, 3, item);

	item  = new QTableWidgetItem(QString("%1").arg(input.filter));
	item->setTextAlignment(Qt::AlignCenter);
	table->setItem(row, 4, item);

}

void PrinterConfigView::addOutputRow(QTableWidget *table, int row, const TIJViewerController::PrinterOutput &output)
{
	QTableWidgetItem * item  = new QTableWidgetItem(QString("%1").arg(output.id));
	item->setTextAlignment(Qt::AlignCenter);
	table->setItem(row, 0, item);

	table->setItem(row, 1, new QTableWidgetItem(output.descriptor));

	item  = new QTableWidgetItem(output.type);
	item->setTextAlignment(Qt::AlignCenter);
	table->setItem(row, 2, item);

	item  = new QTableWidgetItem(QString("%1").arg(output.time));
	table->setItem(row, 3, item);

	item  = new QTableWidgetItem((output.initialValue ? "ON" : "OFF"));
	item->setTextAlignment(Qt::AlignCenter);
	table->setItem(row, 4, item);

}

void PrinterConfigView::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	int cols = _bcdTable->columnCount();
	if (cols == 4) {
		_bcdTable->setColumnWidth(0, 60);
		int w = (_bcdTable->width() - 60 * 2 - 45) / 2;
		_bcdTable->setColumnWidth(1, w);
		_bcdTable->setColumnWidth(2, 60);
		_bcdTable->setColumnWidth(3, w);
	}
}

void PrinterConfigView::validateTriggerSettings()
{
	_repeatPrint->setEnabled(_multiprint->isChecked());
	_numPrints->setEnabled(_multiprint->isChecked());
	_nextDelay->setEnabled(_multiprint->isChecked());

	if (_multiprint->isChecked()) {
		_numPrints->setMinimum(2);
	}
	else{
		_numPrints->setMinimum(1);
		_numPrints->setValue(1);
	}
}

void PrinterConfigView::validateCartridgeSettings()
{
	_voltage->setDisabled(_autoConfig->isChecked());
	_pulseWidth->setDisabled(_autoConfig->isChecked());
	_pulseWarm->setDisabled(_autoConfig->isChecked());
	_pulseTemp->setDisabled(_autoConfig->isChecked());
}

void PrinterConfigView::onStartStop()
{
	if (_controller) {
		if (_controller->setEnabled(!_controller->enabled())) {
			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
		}
	}
}

void PrinterConfigView::onToggleAutoStart()
{
	if (_controller) {
		if (_controller->setAutoStart(_printAutostart->isChecked())) {
			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
		}
	}
}

void PrinterConfigView::onToggleLowLevel()
{
	if (_controller) {
		if (_controller->setLowLevelOutput(_lowLevelOutput->isChecked())) {
			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
		}
	}
}

void PrinterConfigView::onToggleBlockCartridge()
{
	if (_controller) {
		if (_controller->setBlocked(_blockCartridge->isChecked())) {
			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
		}
	}
}

void PrinterConfigView::onToggleRotated()
{
	if (_controller) {
		if (_controller->setPrintRotated(!_controller->enabled())) {
			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
		}
	}
}

void PrinterConfigView::onRequestChanges()
{
	emit configChangeRequested();
}

void PrinterConfigView::onChangeResolution(int idx)
{
	if (_controller) {

//		if (_controller->setPrintRotated(!_controller->enabled())) {
//			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
//		}
	}
}

void PrinterConfigView::onChangeNozzlesCols(int idx)
{
	if (_controller) {
//		if (_controller->setPrintRotated(!_controller->enabled())) {
//			QTimer::singleShot(1000, this, SLOT(onRequestChanges()));
//		}
	}
}

template<typename N>
QStringList PrinterConfigView::getPrinterEnumOptions(const Macsa::Printers::SmartEnum<N> &e) const
{
	QStringList list;
	std::vector<std::string> eList = e.stringList();
	for (uint var = 0; var < eList.size(); ++var) {
		list << eList.at(var).c_str();
	}
	return list;
}
