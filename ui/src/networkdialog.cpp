#include "networkdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>


using namespace Macsa::Network;
// #####################   PrinterItem   ######################## //
PrinterItem::PrinterItem(Macsa::PrinterController *printer, Macsa::PrintersManager &manager, QWidget *parent) :
	QFrame(parent),
	Macsa::Network::NodeObserver(printer),
	_printer(printer),
	_manager(manager)
{
	setFrameShape(QFrame::Box);
	QHBoxLayout * layout = new QHBoxLayout(this);

	QLabel* name = new QLabel(this);
	name->setText(_printer->id().c_str());

	_status = new QLabel(this);
	layout->addWidget(name);
	layout->addStretch();
	layout->addWidget(_status);

	_connect = new QPushButton(this);
	_connect->setFlat(true);
	_connect->setIconSize(QSize(32, 32));
	_connect->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	connect(_connect, SIGNAL(clicked(bool)), SLOT(connectPrinter()));
	layout->addWidget(_connect);

	PrinterItem::nodeStatusChanged(printer->status());
}

void PrinterItem::nodeStatusChanged(const NodeStatus &status)
{
	QIcon icon;

	switch (status) {
		case NodeStatus::CONNECTED:
			_status->setText("CONNECTED");
			icon = QIcon(":/icons/toggle_on.svg");
			break;
		case NodeStatus::CONNECTING:
			_status->setText("CONNECTING");
			icon = QIcon(":/icons/toggle_off.svg");
			break;
		case NodeStatus::DISCONNECTED:
			_status->setText("DISCONNECTED");
			icon = QIcon(":/icons/toggle_off.svg");
			break;
	}
	_connect->setIcon(QIcon(icon));
}

void PrinterItem::nodeTimeout()
{
	qDebug() << __PRETTY_FUNCTION__;
}

void PrinterItem::connectPrinter()
{
	if (_printer->status() == NodeStatus::CONNECTED) {
		_printer->disconnect();
	}
	else {
		_printer->connect();
	}
}

// #####################   NetworkDialog   ######################## //
NetworkDialog::NetworkDialog(Macsa::PrintersManager& manager, QWidget *parent) :
	QDialog(parent),
	Macsa::Network::NetworkObserver(&manager),
	_manager(manager)
{
	configure();
	connect(this, SIGNAL(refresh()), this, SLOT(refreshPrintersList()), Qt::QueuedConnection);
}

void NetworkDialog::onValidate()
{

}

void NetworkDialog::onDiscoverPrinters()
{
	_manager.clear();
	_manager.sendDiscover();
}

void NetworkDialog::nodeDiscovered(const std::string &name, const std::string &addr)
{
	qDebug() << __func__ << " Name: " << name.c_str() << " Addr: " << addr.c_str();
	if(_manager.addTijPrinter(name, addr, true)) {
		emit refresh();
	}
}

void NetworkDialog::configure()
{
	ui.setupUi(this);
	_items.clear();

	_printersList = new QVBoxLayout(ui.networkWidget);

	QPushButton * okButt = ui.buttonBox->button(QDialogButtonBox::Ok);
	connect(okButt, SIGNAL(clicked()), SLOT(onValidate()));

	QPushButton * cancelButt = ui.buttonBox->button(QDialogButtonBox::Cancel);
	connect(cancelButt, SIGNAL(clicked()), SLOT(reject()));

	connect(ui.butDiscover, SIGNAL(clicked()), SLOT(onDiscoverPrinters()));
	refreshPrintersList();
}

void NetworkDialog::refreshPrintersList()
{
	clearItems();
	for (unsigned i = 0; i < _manager.size(); i++) {
		Macsa::PrinterController* controller = _manager.getPrinter(i);
		if (controller != nullptr) {
			PrinterItem* item = new PrinterItem(controller, _manager, this);
			_printersList->addWidget(item);
		}
	}
	_printersList->addStretch();
}

void NetworkDialog::clearItems()
{
	QLayoutItem* item;
	while ( ( item = _printersList->takeAt( 0 ) ) != nullptr )
	{
		delete item->widget();
		delete item;
	}

	_items.clear();

	update();
}
