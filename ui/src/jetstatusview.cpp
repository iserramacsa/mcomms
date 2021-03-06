#include "jetstatusview.h"
#include "QFormLayout"
#include "tij/datatypes.h"

#define ERROR_ICON	":/icons/error.svg"
#define WARN_ICON	":/icons/warning.svg"
#define INFO_ICON	":/icons/notification.svg"

#define RED_COLOR	"color:#800000;"
#define GREEN_COLOR	"color:#008000;"

JetStatusView::JetStatusView(QWidget *parent) :
	QWidget(parent)
{
	_controller = nullptr;
//	_inputs.clear();
	build();
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

JetStatusView::~JetStatusView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void JetStatusView::setController(Macsa::MComms::JetController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new JetViewerController(controller);
	connect(_controller, SIGNAL(printerConfigChanged()), SLOT(refresh()));
	connect(_controller, SIGNAL(printerStatusChanged()), SLOT(refresh()));
	refresh();
}

void JetStatusView::refresh()
{
	if ((_controller != nullptr) && (_controller->printerStatus() != JetViewerController::JetStatus::DISCONNECTED)) {
		_type->setText(_controller->printerType().c_str());
		_sscc->setText(QString("%1").arg(_controller->sscc()));
		_inverted->setChecked(_controller->bitmapInverted());
		_paused->setChecked(_controller->paused());
		_printStatus->setChecked(_controller->printStatus());
		_isInError->setChecked(_controller->isInError());

//		_bcdMode->setText(_controller->bcdMode().toString().c_str());
//		_bcdStatus->setText(QString("%1").arg(_controller->currentBcdCode()));

//		updateErrors(_controller->printerErrors());
//		QMap<QString, int> counters = _controller->counters();
//		for (QMap<QString, int>::const_iterator cit = counters.begin(); cit != counters.end(); cit++) {
//			_counters[cit.key()]->setText(QString("%1").arg(cit.value()));
//		}
//		updateInputs(_controller->inputs());
//		updateOutputs(_controller->outputs());
//		updateProperties(_controller->statusProperties());
	}
	else {
		printerDisconnected();
	}
}


void JetStatusView::build()
{
	_type = new QLabel("---", this);
	_sscc = new QLabel("---", this);
	_inverted = new QCheckBox(this);
	_inverted->setEnabled(false);
	_paused = new QCheckBox(this);
	_paused->setEnabled(false);
	_printStatus = new QCheckBox(this);
	_printStatus->setEnabled(false);
	_isInError = new QCheckBox(this);
	_isInError->setEnabled(false);

	QFormLayout* layout = new QFormLayout(this);
	layout->addRow("Type:", _type);
	layout->addRow("SSCC:", _sscc);
	layout->addRow("Print inverted:", _inverted);
	layout->addRow("Print paused:", _paused);
	layout->addRow("Print status:", _printStatus);
	layout->addRow("Printer is in error:", _isInError);

	_errors = new QTableWidget(this);
	layout->addRow("Current errors:", _errors);

//	//Counters
//	layout->addRow("Counters:", buildCounters());

//	//Inputs
//	QWidget* inputs = new QWidget(this);
//	inputs->setForegroundRole(QPalette::Dark);
//	inputs->setMaximumWidth(500);
//	_gridInputs = new QGridLayout(inputs);
//	_gridInputs->setMargin(0);
//	_gridInputs->setContentsMargins(0,10,0,10);
//	layout->addRow("Inputs:", inputs);

//	//Outputs
//	QWidget* outputs = new QWidget(this);
//	outputs->setMaximumWidth(200);
//	_gridOutputs = new QGridLayout(outputs);
//	_gridOutputs->setMargin(0);
//	_gridOutputs->setContentsMargins(0,10,0,10);
//	layout->addRow("Outputs:", outputs);

//	//Properties
//	QWidget* props = new QWidget(this);
//	props->setMaximumWidth(400);
//	_propLayout = new QFormLayout(props);
//	_propLayout->setMargin(0);
//	_propLayout->setContentsMargins(0,10,0,10);
//	layout->addRow("Properties:", props);
	printerDisconnected();
}

//QWidget* JetStatusView::buildCounters()
//{
//	QWidget*  counters = new QWidget(this);
//	counters->setMaximumWidth(500);
//	counters->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
//	_counters.insert("SYSTEM.TOTAL", new QLabel("0", counters));
//	_counters.insert("SYSTEM.USER", new QLabel("0", counters));
//	for (int i = 0; i < 16; i++) {
//		_counters.insert(QString("BCD.%1").arg(i), new QLabel("0", counters));
//	}

//	QGridLayout* countLayout = new QGridLayout(counters);
//	countLayout->setMargin(0);
//	countLayout->setContentsMargins(0,10,0,10);

//	int row = 0;
//	int numCols = 4;
//	int bcdCodes = (_counters.count() - 2);
//	int numRows = bcdCodes / numCols;
//	for (int i = 0; i < numRows ; i++, row++) {
//		for (int j = 0, col = 0; j < numCols; ++j) {
//			if((i * j) < bcdCodes) {
//				QString cntr = QString("BCD.%1").arg(j * numCols + i);
//				countLayout->addWidget(new QLabel(cntr), i, col++);
//				countLayout->addWidget(_counters[cntr], i, col++);
//			}
//		}
//	}

//	countLayout->addWidget(new QLabel("User"), row, 0);
//	countLayout->addWidget(_counters["SYSTEM.USER"], row, 1);
//	countLayout->addWidget(new QLabel("Total"), row, 2);
//	countLayout->addWidget(_counters["SYSTEM.TOTAL"], row, 3);

//	return counters;
//}

//QWidget *JetStatusView::buildInputs()
//{
//	QWidget* inputs = new QWidget(this);
//	inputs->setLayout(new QGridLayout());
//	return inputs;
//}

void JetStatusView::printerDisconnected()
{
	_type->setText("---");
	_sscc->setText("---");
	_inverted->setChecked(false);
	_paused->setChecked(false);
	_printStatus->setChecked(false);
	_isInError->setChecked(false);

//	_autostart->setChecked(false);
//	_currentMessage->setText("---");
//	_bcdMode->setText("---");
//	_bcdStatus->setText("---");
//	_errors->clear();
//	updateInputs(QVector<TIJViewerController::PrinterInput>());
//	updateOutputs(QVector<TIJViewerController::PrinterOutput>());
//	updateProperties(QMap<QString, QString>());
//	updateErrors(std::vector<Macsa::Printers::Error>());
}

void JetStatusView::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
//	int cols = _errors->columnCount();
//	if (cols == 4) {

//		int w = 0;
//		int c = 0;
//		_errors->setColumnWidth(c++, 100); w += 100;
//		_errors->setColumnWidth(c++, 100); w += 100;
//		_errors->setColumnWidth(c++, 60); w += 60;
//		w = _errors->width() - (w + 18);
//		_errors->setColumnWidth(c, w);
//	}

}

//void JetStatusView::updateInputs(const QVector<TIJViewerController::PrinterInput> &inputs)
//{
//	if (_inputs.size() == 0){
//		int in = 0;
//		int numCols = 3;
//		int numRows = inputs.count() / numCols;
//		for (int i = 0; i < numRows; i++) {
//			int col = 0;
//			for (int j = 0; j < numCols; j++) {
//				if (in < inputs.count()){
//					QLabel* lblName = new QLabel(inputs.at(in).descriptor);
//					QLabel* lblValue = new QLabel(inputs.at(in).value ? "ON" : "OFF");
//					_inputs.insert(inputs.at(in).descriptor, lblValue);
//					_gridInputs->addWidget(lblName, i, col++);
//					_gridInputs->addWidget(lblValue, i, col++);
//					in++;
//				}
//			}
//		}
//	}

//	if (_inputs.count()){
//		for (int i = 0; i < inputs.count(); i++) {
//			QLabel* lbl = _inputs[inputs.at(i).descriptor];
//			bool val = inputs.at(i).value;
//			if (lbl){
//				lbl->setText(val ? "ON" : "OFF");
//				if (val) {
//					lbl->setStyleSheet(GREEN_COLOR);
//				}
//				else {
//					lbl->setStyleSheet(RED_COLOR);
//				}
//				QFont f = lbl->font();
//				f.setBold(val);
//				lbl->setFont(f);
//			}
//		}
//	}
//}

//void JetStatusView::updateOutputs(const QVector<TIJViewerController::PrinterOutput> &outputs)
//{
//	if (_outputs.size() == 0){
//		int in = 0;
//		int numCols = 1;
//		int numRows = outputs.count() / numCols;
//		for (int i = 0; i < numRows; i++) {
//			int col = 0;
//			for (int j = 0; j < numCols; j++) {
//				if (in < outputs.count()){
//					QLabel* lblName = new QLabel(outputs.at(in).descriptor);
//					QLabel* lblValue = new QLabel(outputs.at(in).value ? "ON" : "OFF");
//					_outputs.insert(outputs.at(in).descriptor, lblValue);
//					_gridOutputs->addWidget(lblName, i, col++);
//					_gridOutputs->addWidget(lblValue, i, col++);
//					in++;
//				}
//			}
//		}
//	}

//	if (_outputs.count()){
//		for (int i = 0; i < outputs.count(); i++) {
//			QLabel* lbl = _outputs[outputs.at(i).descriptor];
//			bool val = outputs.at(i).value;
//			if (lbl){
//				lbl->setText(val ? "ON" : "OFF");
//				lbl->setText(val ? "ON" : "OFF");
//				if (val) {
//					lbl->setStyleSheet(GREEN_COLOR);
//				}
//				else {
//					lbl->setStyleSheet(RED_COLOR);
//				}
//				QFont f = lbl->font();
//				f.setBold(val);
//				lbl->setFont(f);
//			}
//		}
//	}
//}

//void JetStatusView::updateProperties(const QMap<QString, QString> &props)
//{
//	if (_props.size() == 0 && props.count()) {
//		for (QMap<QString, QString>::const_iterator it = props.begin(); it != props.end(); it++) {
//			QLabel* propValue = new QLabel(it.value());
//			_propLayout->addRow(it.key(), propValue);
//			_props.insert(it.key(), propValue);
//		}
//	}

//	if (_props.count()) {
//		for (QMap<QString, QString>::const_iterator it = props.begin(); it != props.end(); it++) {
//			QLabel* lbl = _props[it.key()];
//			if(lbl) {
//				lbl->setText(it.value());
//			}
//		}
//	}

//}

//void JetStatusView::updateErrors(const std::vector<Macsa::Printers::JetLogType> &errors)
//{
//	_errors->clear();
//	QStringList header;
//	header << "Timestamp" << "Type" << "Priority" << "code";
//	_errors->setColumnCount(header.count());
//	_errors->setRowCount(static_cast<int>(errors.size()));
//	_errors->setHorizontalHeaderLabels(header);

//	for (uint32_t i = 0; i < errors.size(); i++) {
//		QDateTime dt = QDateTime::fromTime_t(static_cast<uint>(errors.at(i).timestamp()));
//		QTableWidgetItem* itTStamp = new QTableWidgetItem(QString("%1").arg(dt.toString(Qt::SystemLocaleShortDate)));
//		QTableWidgetItem* itType = new QTableWidgetItem(errors.at(i).type().toString().c_str());
//		switch (errors.at(i).type()()) {
//			case Macsa::Printers::nErrorType::ERROR:
//				itType->setIcon(QIcon(ERROR_ICON));
//				break;
//			case Macsa::Printers::nErrorType::WARNING:
//				itType->setIcon(QIcon(WARN_ICON));
//				break;
//			case Macsa::Printers::nErrorType::INFORMATION:
//				itType->setIcon(QIcon(INFO_ICON));
//				break;
//			default:
//				break;
//		}
//		QTableWidgetItem* itPriority = new QTableWidgetItem(QString("%1").arg(errors.at(i).priority()));
//		itPriority->setTextAlignment(Qt::AlignCenter);
//		QTableWidgetItem* itCode = new QTableWidgetItem(errors.at(i).code().toString().c_str());

//		_errors->setItem(static_cast<int>(i), 0, itTStamp);
//		_errors->setItem(static_cast<int>(i), 1, itType);
//		_errors->setItem(static_cast<int>(i), 2, itPriority);
//		_errors->setItem(static_cast<int>(i), 3, itCode);
//	}

//}
