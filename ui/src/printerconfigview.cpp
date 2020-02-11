#include "printerconfigview.h"
#include "QFormLayout"
#include <QTimer>

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
	}
	else {
		printerDisconnected();
	}
}

#include <QLine>

void PrinterConfigView::build()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(getTitle("Printer General Settings:"));
	layout->addWidget(buildGeneralSettings());
	layout->addSpacing(10);
	layout->addWidget(getTitle("Print Setup"));
	layout->addWidget(buildPrintSetup());
	layout->addWidget(buildTriggerSetup());
	layout->addWidget(buildBcdTable());
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
	layout->addRow("Enable low level output", _lowLevelOutput);
	layout->addRow("Block cartridge:", _blockCartridge);

	return generalSettings;
}

QWidget *PrinterConfigView::buildPrintSetup()
{
	QWidget * printSetup = new QWidget(this);
	QFormLayout* layout = new QFormLayout(printSetup);
	layout->setSpacing(6);

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
	QStringList cols;
	std::vector<std::string> colsList;
	_nozzlesCols->addItems(QStringList() << "Col A" << "Col B" << "Both");

	resLayout->addWidget(_printResolution);
	resLayout->addWidget(new QLabel("Nozzles column:"));
	resLayout->addWidget(_nozzlesCols);
	resLayout->addStretch();


	layout->addRow("Print Rotated:", _printRotated);
	layout->addRow("Resolution:", resolution);

	return printSetup;
}

QWidget *PrinterConfigView::buildTriggerSetup()
{
	QWidget * triggerSetup = new QWidget(this);
	return triggerSetup;
}

QWidget *PrinterConfigView::buildBcdTable()
{
	QWidget * bcdTable = new QWidget(this);
	return bcdTable;
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

#include <QDebug>
void PrinterConfigView::updatePrintSetup()
{
	_printRotated->setChecked(_controller->printRotated());
	qDebug() << _controller->nozzlesCol() << _controller->nozzlesCol();
}

void PrinterConfigView::updateTriggerSetup()
{

}

void PrinterConfigView::updateBcdTable()
{

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

QLabel *PrinterConfigView::getTitle(const QString &text)
{
	QLabel * title = new QLabel(text, this);
	title->setMargin(6);
	title->setStyleSheet(TITLE_CSS);
	return title;
}

void PrinterConfigView::onStartStop()
{
	if (_controller){
		if (_controller->setEnabled(!_controller->enabled())) {
			QTimer::singleShot(1000, this, SLOT(onTimerRequest()));
		}
	}
}

void PrinterConfigView::onToggleAutoStart()
{
	if (_controller){
		if (_controller->setAutoStart(_printAutostart->isChecked())) {
			QTimer::singleShot(1000, this, SLOT(onTimerRequest()));
		}
	}
}

void PrinterConfigView::onToggleLowLevel()
{
	if (_controller){
		if (_controller->setLowLevelOutput(_lowLevelOutput->isChecked())) {
			QTimer::singleShot(1000, this, SLOT(onTimerRequest()));
		}
	}
}

void PrinterConfigView::onToggleBlockCartridge()
{
	if (_controller){
		if (_controller->setBlocked(_blockCartridge->isChecked())) {
			QTimer::singleShot(1000, this, SLOT(onTimerRequest()));
		}
	}
}

void PrinterConfigView::onToggleRotated()
{
	if (_controller){
		if (_controller->setPrintRotated(!_controller->enabled())) {
			QTimer::singleShot(1000, this, SLOT(onTimerRequest()));
		}
	}
}
#include <unistd.h>
void PrinterConfigView::onTimerRequest()
{
	_controller->updatePrinterData();
	refresh();
}
