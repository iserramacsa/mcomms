#include "printerstatusview.h"
#include "QFormLayout"

PrinterStatusView::PrinterStatusView(QWidget *parent) :
	QWidget(parent)
{
	_controller = nullptr;
	build();
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

PrinterStatusView::~PrinterStatusView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void PrinterStatusView::setController(Macsa::TIJPrinterController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new TIJViewerController(controller);
	refresh();
}

void PrinterStatusView::refresh()
{
	if ((_controller != nullptr) && (_controller->data(1).toString() != "Disconnected")) {
		_printerType->setText(_controller->boardType());
		_printerAutostart->setChecked(_controller->autoStart());
		_printerUserMessage->setText(_controller->userMessage());
		_printerBcdMode->setText(_controller->bcdMode());
		_printerBcdStatus->setText(QString("%1").arg(_controller->currentBcdCode()));

		QMap<QString, int> counters = _controller->counters();
		for (QMap<QString, int>::const_iterator cit = counters.begin(); cit != counters.end(); cit++) {
			_counters[cit.key()]->setText(QString("%1").arg(cit.value()));
		}
		updateInputs(_controller->inputs());
	}
	else {
		printerDisconnected();
	}
}

void PrinterStatusView::build()
{
	_printerType = new QLabel("---", this);
	_printerAutostart = new QCheckBox(this);
	_printerAutostart->setEnabled(false);
	_printerUserMessage = new QLabel("---", this);
	_printerBcdMode = new QLabel("---", this);
	_printerBcdStatus = new QLabel("---", this);

	QFormLayout* layout = new QFormLayout(this);
	layout->addRow("Type:", _printerType);
	layout->addRow("Autostart:", _printerAutostart);
	layout->addRow("User Message:", _printerUserMessage);
	layout->addRow("BCD Mode:", _printerBcdMode);
	layout->addRow("BCD Status:", _printerBcdStatus);

	//COUNTERS
	QWidget*  counters = new QWidget(this);
	counters->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	QGridLayout* countLayout = new QGridLayout(counters);
	_counters.insert("SYSTEM.TOTAL", new QLabel("0", counters));
	_counters.insert("SYSTEM.USER", new QLabel("0", counters));
	for (int i = 0; i < 16; i++) {
		_counters.insert(QString("BCD.%1").arg(i), new QLabel("0", counters));
	}
	countLayout->setMargin(0);
	countLayout->addWidget(new QLabel("Total"), 0, 0);
	countLayout->addWidget(_counters["SYSTEM.TOTAL"], 0, 1);
	countLayout->addWidget(new QLabel("User"), 0, 2);
	countLayout->addWidget(_counters["SYSTEM.USER"], 0, 3);

	int row = 1;
	for (int i = 0; i < 8; i++, row++) {
		QString cntr = QString("BCD.%1").arg(i);
		countLayout->addWidget(new QLabel(cntr), row, 0);
		countLayout->addWidget(_counters[cntr], row, 1);

		QString cntr2 = QString("BCD.%1").arg(i + 8);
		countLayout->addWidget(new QLabel(cntr2), row, 2);
		countLayout->addWidget(_counters[cntr2], row, 3);
	}

	layout->addRow("Counters:", counters);

	//Inputs
	_inputs = new QTableWidget(this);
	QStringList header;
	header << "Id" << "Descriptor" << "Mode" << "Inverted" << "Filter" << "Value";
	_inputs->setVerticalHeaderLabels(header);
	layout->addRow("Inputs:", _inputs);

}

void PrinterStatusView::printerDisconnected()
{
	_printerType->setText("---");
	_printerAutostart->setChecked(false);
	_printerUserMessage->setText("---");
	_printerBcdMode->setText("---");
	_printerBcdStatus->setText("---");
	_inputs->clear();
}

void PrinterStatusView::updateInputs(const QVector<TIJViewerController::PrinterInput>& inputs)
{
	_inputs->clear();
	QStringList header;
	header << "Id" << "Descriptor" << "Mode" << "Inverted" << "Filter" << "Value";
	_inputs->setVerticalHeaderLabels(header);

	for (int i = 0; i < inputs.size(); i++) {
		QTableWidgetItem* itId = new QTableWidgetItem(QString("%1").arg(inputs.at(i).id));
		QTableWidgetItem* itDescriptor = new QTableWidgetItem(inputs.at(i).descriptor);
		QTableWidgetItem* itMode = new QTableWidgetItem(inputs.at(i).mode);
		QTableWidgetItem* itInverted = new QTableWidgetItem((inputs.at(i).inverted?"true":"false"));
		QTableWidgetItem* itFilter = new QTableWidgetItem(QString("%1").arg(inputs.at(i).filter));
		QTableWidgetItem* itValue = new QTableWidgetItem((inputs.at(i).value?"ENABLED":"DISABLED"));

		_inputs->setItem(i, 0, itId);
		_inputs->setItem(i, 1, itDescriptor);
		_inputs->setItem(i, 2, itMode);
		_inputs->setItem(i, 3, itInverted);
		_inputs->setItem(i, 4, itFilter);
		_inputs->setItem(i, 5, itValue);
	}

}
