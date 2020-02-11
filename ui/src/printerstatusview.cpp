#include "printerstatusview.h"
#include "QFormLayout"

PrinterStatusView::PrinterStatusView(QWidget *parent) :
	QWidget(parent)
{
	_controller = nullptr;
	_inputs.clear();
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
	if ((_controller != nullptr) && (_controller->printerStatus() != TIJViewerController::TIJStatus::DISCONNECTED)) {
		_printerType->setText(_controller->boardType());
		_printerAutostart->setChecked(_controller->autoStart());
		_printerUserMessage->setText(_controller->userMessage());
		_printerBcdMode->setText(_controller->bcdMode());
		_printerBcdStatus->setText(QString("%1").arg(_controller->currentBcdCode()));

		updateErrors(_controller->errors());
		QMap<QString, int> counters = _controller->counters();
		for (QMap<QString, int>::const_iterator cit = counters.begin(); cit != counters.end(); cit++) {
			_counters[cit.key()]->setText(QString("%1").arg(cit.value()));
		}
		updateInputs(_controller->inputs());
		updateOutputs(_controller->outputs());
		updateProperties(_controller->properties());
	}
	else {
		printerDisconnected();
	}
}

#include <QLine>

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

	_errors = new QTableWidget(this);
	layout->addRow("Current errors:", _errors);

	//Counters
	layout->addRow("Counters:", buildCounters());

	//Inputs
	QWidget* inputs = new QWidget(this);
	inputs->setForegroundRole(QPalette::Dark);
	inputs->setMaximumWidth(500);
	_gridInputs = new QGridLayout(inputs);
	_gridInputs->setMargin(0);
	_gridInputs->setContentsMargins(0,10,0,10);
	layout->addRow("Inputs:", inputs);

	//Outputs
	QWidget* outputs = new QWidget(this);
	outputs->setMaximumWidth(200);
	_gridOutputs = new QGridLayout(outputs);
	_gridOutputs->setMargin(0);
	_gridOutputs->setContentsMargins(0,10,0,10);
	layout->addRow("Outputs:", outputs);

	//Properties
	QWidget* props = new QWidget(this);
	props->setMaximumWidth(400);
	_propLayout = new QFormLayout(props);
	_propLayout->setMargin(0);
	_propLayout->setContentsMargins(0,10,0,10);
	layout->addRow("Properties:", props);
}

QWidget* PrinterStatusView::buildCounters()
{
	QWidget*  counters = new QWidget(this);
	counters->setMaximumWidth(500);
	counters->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	_counters.insert("SYSTEM.TOTAL", new QLabel("0", counters));
	_counters.insert("SYSTEM.USER", new QLabel("0", counters));
	for (int i = 0; i < 16; i++) {
		_counters.insert(QString("BCD.%1").arg(i), new QLabel("0", counters));
	}

	QGridLayout* countLayout = new QGridLayout(counters);
	countLayout->setMargin(0);
	countLayout->setContentsMargins(0,10,0,10);

	int row = 0;
	int numCols = 4;
	int bcdCodes = (_counters.count() - 2);
	int numRows = bcdCodes / numCols;
	for (int i = 0; i < numRows ; i++, row++) {
		for (int j = 0, col = 0; j < numCols; ++j) {
			if((i * j) < bcdCodes) {
				QString cntr = QString("BCD.%1").arg(j * numCols + i);
				countLayout->addWidget(new QLabel(cntr), i, col++);
				countLayout->addWidget(_counters[cntr], i, col++);
			}
		}
	}

	countLayout->addWidget(new QLabel("User"), row, 0);
	countLayout->addWidget(_counters["SYSTEM.USER"], row, 1);
	countLayout->addWidget(new QLabel("Total"), row, 2);
	countLayout->addWidget(_counters["SYSTEM.TOTAL"], row, 3);

	return counters;
}

QWidget *PrinterStatusView::buildInputs()
{
	QWidget* inputs = new QWidget(this);
	inputs->setLayout(new QGridLayout());
	return inputs;
}

void PrinterStatusView::printerDisconnected()
{
	_printerType->setText("---");
	_printerAutostart->setChecked(false);
	_printerUserMessage->setText("---");
	_printerBcdMode->setText("---");
	_printerBcdStatus->setText("---");
	updateInputs(QVector<TIJViewerController::PrinterInput>());
	updateOutputs(QVector<TIJViewerController::PrinterOutput>());
	updateProperties(QMap<QString, QString>());
	updateErrors(QVector<TIJViewerController::PrinterError>());
}

void PrinterStatusView::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
	int cols = _errors->columnCount();
	if (cols == 4) {

		int w = 0;
		int c = 0;
		_errors->setColumnWidth(c++, 100); w += 100;
		_errors->setColumnWidth(c++, 70); w += 70;
		_errors->setColumnWidth(c++, 100); w += 100;
		w = _errors->width() - (w + 18);
		_errors->setColumnWidth(c, w);
	}

}

void PrinterStatusView::updateInputs(const QVector<TIJViewerController::PrinterInput> &inputs)
{
	if (_inputs.size() == 0){
		int in = 0;
		int numCols = 3;
		int numRows = inputs.count() / numCols;
		for (int i = 0; i < numRows; i++) {
			int col = 0;
			for (int j = 0; j < numCols; j++) {
				if (in < inputs.count()){
					QLabel* lblName = new QLabel(inputs.at(in).descriptor);
					QLabel* lblValue = new QLabel(inputs.at(in).value ? "ON" : "OFF");
					_inputs.insert(inputs.at(in).descriptor, lblValue);
					_gridInputs->addWidget(lblName, i, col++);
					_gridInputs->addWidget(lblValue, i, col++);
					in++;
				}
			}
		}
	}

	if (_inputs.count()){
		for (int i = 0; i < inputs.count(); i++) {
			QLabel* lbl = _inputs[inputs.at(i).descriptor];
			bool val = inputs.at(i).value;
			if (lbl){
				lbl->setText(val ? "ON" : "OFF");
				QFont f = lbl->font();
				f.setBold(val);
				lbl->setFont(f);
			}
		}
	}
}

void PrinterStatusView::updateOutputs(const QVector<TIJViewerController::PrinterOutput> &outputs)
{
	if (_outputs.size() == 0){
		int in = 0;
		int numCols = 1;
		int numRows = outputs.count() / numCols;
		for (int i = 0; i < numRows; i++) {
			int col = 0;
			for (int j = 0; j < numCols; j++) {
				if (in < outputs.count()){
					QLabel* lblName = new QLabel(outputs.at(in).descriptor);
					QLabel* lblValue = new QLabel(outputs.at(in).value ? "ON" : "OFF");
					_outputs.insert(outputs.at(in).descriptor, lblValue);
					_gridOutputs->addWidget(lblName, i, col++);
					_gridOutputs->addWidget(lblValue, i, col++);
					in++;
				}
			}
		}
	}

	if (_outputs.count()){
		for (int i = 0; i < outputs.count(); i++) {
			QLabel* lbl = _outputs[outputs.at(i).descriptor];
			bool val = outputs.at(i).value;
			if (lbl){
				lbl->setText(val ? "ON" : "OFF");
				QFont f = lbl->font();
				f.setBold(val);
				lbl->setFont(f);
			}
		}
	}
}

void PrinterStatusView::updateProperties(const QMap<QString, QString> &props)
{
	if (_props.size() == 0 && props.count()) {
		for (QMap<QString, QString>::const_iterator it = props.begin(); it != props.end(); it++) {
			QLabel* propValue = new QLabel(it.value());
			_propLayout->addRow(it.key(), propValue);
			_props.insert(it.key(), propValue);
		}
	}

	if (_props.count()) {
		for (QMap<QString, QString>::const_iterator it = props.begin(); it != props.end(); it++) {
			QLabel* lbl = _props[it.key()];
			if(lbl) {
				lbl->setText(it.value());
			}
		}
	}

}

void PrinterStatusView::updateErrors(const QVector<TIJViewerController::PrinterError>& errors)
{
	_errors->clear();
	QStringList header;
	header << "Timestamp" << "Type" << "Priority" << "code";
	_errors->setColumnCount(header.count());
	_errors->setRowCount(errors.size());
	_errors->setHorizontalHeaderLabels(header);

	for (int i = 0; i < errors.size(); i++) {
		QTableWidgetItem* itTStamp = new QTableWidgetItem(QString("%1").arg(errors.at(i).timestamp.toString(Qt::SystemLocaleShortDate)));
		QTableWidgetItem* itType = new QTableWidgetItem(errors.at(i).type);
		QTableWidgetItem* itPriority = new QTableWidgetItem(QString("%1").arg(errors.at(i).priority));
		QTableWidgetItem* itCode = new QTableWidgetItem(errors.at(i).code);

		_errors->setItem(i, 0, itTStamp);
		_errors->setItem(i, 1, itType);
		_errors->setItem(i, 2, itPriority);
		_errors->setItem(i, 3, itCode);
	}

}
/*
void PrinterStatusView::updateInputs(const QVector<TIJViewerController::PrinterInput>& inputs)
{
	_inputs->clear();
	QStringList header;
	header << "Id" << "Descriptor" << "Mode" << "Inverted" << "Filter" << "Value";
	_inputs->setColumnCount(header.count());
	_inputs->setRowCount(inputs.size());
	_inputs->setHorizontalHeaderLabels(header);

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
*/
