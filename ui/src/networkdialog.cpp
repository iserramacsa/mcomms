#include "networkdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <QDebug>

using namespace Macsa::Network;

PrinterItem::PrinterItem(Macsa::PrinterController *printer, Macsa::PrintersManager &manager, QWidget *parent) :
	QWidget(parent),
	Macsa::Network::NodeObserver(printer),
	_printer(printer),
	_manager(manager)
{
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
	Q_UNUSED(name)
	Q_UNUSED(address)

}

void NetworkDialog::configure()
{
	ui.setupUi(this);

	_printersList = new QVBoxLayout(ui.networkWidget);

	QPushButton * okButt = ui.buttonBox->button(QDialogButtonBox::Ok);
	connect(okButt, SIGNAL(clicked()), SLOT(onValidate()));

	QPushButton * cancelButt = ui.buttonBox->button(QDialogButtonBox::Cancel);
	connect(cancelButt, SIGNAL(clicked()), SLOT(reject()));

	connect(ui.butDiscover, SIGNAL(clicked()), SLOT(onDiscoverPrinters()));
}
