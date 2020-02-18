#include "networkdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>

NetworkDialog::NetworkDialog(QWidget *parent) :
	QDialog(parent)
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


