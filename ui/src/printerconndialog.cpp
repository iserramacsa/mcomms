#include "printerconndialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

PrinterConnectionDialog::PrinterConnectionDialog(QWidget *parent) :
	QDialog(parent)
{
	configure();
}

PrinterConnectionDialog::PrinterConnectionDialog(const QString &name, const QString &address, QWidget *parent) :
	QDialog(parent)
{
	configure();
	_name = name;
	_address = address;
	ui._edName->setText(_name);
	ui._edAddress->setText(_address);
}

QString PrinterConnectionDialog::address() const
{
	return _address;
}

QString PrinterConnectionDialog::name() const
{
	return _name;
}

void PrinterConnectionDialog::onValidate()
{
	_name = ui._edName->text();
	_address = ui._edAddress->text();
	accept();
}

void PrinterConnectionDialog::configure()
{
	ui.setupUi(this);
	setWindowTitle("Printer connection");

	QPushButton * okButt = ui.buttonBox->button(QDialogButtonBox::Ok);
	connect(okButt, SIGNAL(clicked()), SLOT(onValidate()));

	QPushButton * cancelButt = ui.buttonBox->button(QDialogButtonBox::Cancel);
	connect(cancelButt, SIGNAL(clicked()), SLOT(reject()));
}

