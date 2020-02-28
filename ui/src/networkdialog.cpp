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
	nodeStatusChanged(printer->status());
}

void PrinterItem::nodeStatusChanged(const NodeStatus &status)
{
	switch (status) {
		case NodeStatus::CONNECTED:
			_status->setText("CONNECTED");
			break;
		case NodeStatus::CONNECTING:
			_status->setText("DISCONNECTED");
			break;
		case NodeStatus::DISCONNECTED:
			_status->setText("DISCONNECTED");
			break;
	}
}

void PrinterItem::nodeTimeout()
{
	qDebug() << __PRETTY_FUNCTION__;
}

// #####################   NetworkDialog   ######################## //
NetworkDialog::NetworkDialog(Macsa::PrintersManager& manager, QWidget *parent) :
	QDialog(parent),
	_manager(manager)
{
	configure();
}

void NetworkDialog::onValidate()
{

}

void NetworkDialog::onDiscoverPrinters()
{

}

void NetworkDialog::onPrinterDetected(const QString &name, const QString address)
{
	qDebug() << __func__ << " Name: " << name << " Addr: " << address;

	refreshPrintersList();
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
