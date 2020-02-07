#include "printerconfigview.h"
#include "QFormLayout"

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
//	layout->setMargin(0);
	layout->addWidget(buildGeneralSettings());
	layout->addWidget(buildPrintSetup());
	layout->addWidget(buildTriggerSetup());
	layout->addWidget(buildBcdTable());
	layout->addStretch();
}

QWidget *PrinterConfigView::buildGeneralSettings()
{
	QWidget * generalSettings = new QWidget(this);
	QFormLayout* layout = new QFormLayout(generalSettings);
	layout->setMargin(0);
	layout->setSpacing(6);

	_butEnable = new QPushButton("Start", generalSettings);
        _butEnable->setFixedWidth(150);
		connect(_butEnable, SIGNAL(clicked(bool)), SLOT(onStartStop()));
	_printAutostart = new QCheckBox(generalSettings);
	_lowLevelOutput = new QCheckBox(generalSettings);
	_blockCartridge = new QCheckBox(generalSettings);

	layout->addRow("Enable print:", _butEnable);
	layout->addRow("Autostart:", _printAutostart);
	layout->addRow("Enable low level output", _lowLevelOutput);
	layout->addRow("Block cartridge:", _blockCartridge);

	return generalSettings;
}

QWidget *PrinterConfigView::buildPrintSetup()
{
	QWidget * printSetup = new QWidget(this);
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

void PrinterConfigView::updatePrintSetup()
{

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

void PrinterConfigView::onStartStop()
{
	_controller->setEnabled(!_controller->enabled());
}
