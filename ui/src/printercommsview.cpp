#include "printercommsview.h"
#include <QVBoxLayout>
#include <QFormLayout>

#define TITLE_CSS "QLabel {Background-color:#333; color:#DDD; margin: 3px 3px 3px 3px;} "

PrinterCommsView::PrinterCommsView(QWidget *parent):
	QWidget(parent)
{
	_controller = nullptr;
	build();
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	refresh();
}


PrinterCommsView::~PrinterCommsView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void PrinterCommsView::setController(Macsa::MComms::TijController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new TIJViewerController(controller);
	connect(_controller, SIGNAL(printerConfigChanged()), SLOT(refresh()));
	refresh();
}

void PrinterCommsView::refresh()
{
	if ((_controller != nullptr) && (_controller->printerStatus() != TIJViewerController::TijStatus::DISCONNECTED)) {
		for (int i = 0; i < _ifaces.count(); ++i) {
			refreshNetIface(i);
		}
		refreshBle();
	}
	else {
		clear();
	}
}

void PrinterCommsView::build()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(10);
	layout->addWidget(getTitle("Ethernet interfaces:"));
	for (int i = 0; i < 2; i++) {
		layout->addWidget(buildNetworkAdapter());
	}
	_butChangeConfig = new QPushButton("Apply Changes", this);
	_butChangeConfig->setMaximumWidth(250);
	connect(_butChangeConfig, SIGNAL(clicked(bool)), SLOT(onChangeConfiguration()));
	layout->addWidget(_butChangeConfig);


	layout->addWidget(getTitle("Bluetooth:"));
	layout->addWidget(buildBluetoothDevice());

	layout->addStretch();
}

void PrinterCommsView::clear()
{
	for (int i = 0; i < _ifaces.count(); ++i) {
		netWidget& iface = _ifaces[i];
		iface.dhcp->setChecked(false);
		iface.port->setText("---");
		iface.iface->setText("---");
		iface.address->setText("");
		iface.netmask->setText("");
		iface.gateway->setText("");
		iface.macAddress->setText("");
	}
}

void PrinterCommsView::refreshNetIface(int idx)
{
	if (_ifaces.count() > idx){
		TIJViewerController::NetworkIface eth = _controller->networkIface(idx);
		netWidget& iface = _ifaces[idx];
		iface.dhcp->setChecked(eth.dhcp);
		iface.port->setText(QString("%1").arg(eth.port));
		iface.iface->setText(eth.iface);
		iface.address->setText(eth.address);
		iface.netmask->setText(eth.netmask);
		iface.gateway->setText(eth.gateway);
		iface.macAddress->setText(eth.hwAddress);
	}
}

void PrinterCommsView::refreshBle()
{
	TIJViewerController::BluetoothDevice ble = _controller->bluetooth();
	_ble.name->setText(ble.name);
	_ble.password->setText(ble.pass);
	_ble.visible->setChecked(ble.visible);

}

QLabel *PrinterCommsView::getTitle(const QString &text)
{
	QLabel * title = new QLabel(text, this);
	title->setMargin(6);
	title->setStyleSheet(TITLE_CSS);
	return title;
}

QWidget *PrinterCommsView::buildNetworkAdapter()
{
	QWidget* rootEth = new QWidget(this);
	QFormLayout* layout  = new QFormLayout(rootEth);

	netWidget eth;
	eth.iface = new QLabel("", rootEth);
	eth.dhcp = new QCheckBox(rootEth);
	eth.dhcp->setEnabled(false);
	eth.address = createIpFormatedLineEditor(rootEth);
	eth.netmask = createIpFormatedLineEditor(rootEth);
	eth.gateway = createIpFormatedLineEditor(rootEth);
	eth.macAddress = new QLabel("", rootEth);
	eth.port = new QLabel("", rootEth);
	_ifaces.push_back(eth);

	layout->addRow("Iface:", eth.iface);
	layout->addRow("DHCP:", eth.dhcp);
	layout->addRow("Address:", eth.address);
	layout->addRow("Netmask:", eth.netmask);
	layout->addRow("GateWay:", eth.gateway);
	layout->addRow("HW Address:", eth.macAddress);
	layout->addRow("TCP port:", eth.port);

	return rootEth;
}

QWidget *PrinterCommsView::buildBluetoothDevice()
{
	QWidget* rootBle = new QWidget(this);
	QFormLayout* layout  = new QFormLayout(rootBle);

	_ble.name = new QLabel(rootBle);
	_ble.password = new QLabel(rootBle);
	_ble.visible = new QCheckBox(rootBle);
	_ble.visible->setEnabled(false);

	layout->addRow("Device name:", _ble.name);
	layout->addRow("Password:", _ble.password);
	layout->addRow("Visible:", _ble.visible);

	return rootBle;
}

QLineEdit *PrinterCommsView::createIpFormatedLineEditor(QWidget* parent)
{
	QLineEdit * editor = new QLineEdit(parent);
	editor->setInputMask("009.009.009.009");
	editor->setFixedWidth(200);
	editor->setAlignment(Qt::AlignHCenter);
	return  editor;
}

void PrinterCommsView::onChangeConfiguration()
{

}


