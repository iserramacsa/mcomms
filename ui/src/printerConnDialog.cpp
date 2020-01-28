#include "printerConnDialog.h"

PrinterConnectionDialog::PrinterConnectionDialog(QWidget *parent) :
	QDialog(parent)
{
	setWindowTitle("Printer connection");

}

PrinterConnectionDialog::PrinterConnectionDialog(const QString &name, const QString &address, QWidget *parent)
{
	_name = name;
	_address = address;
}

QString PrinterConnectionDialog::address() const
{
	return _address;
}

QString PrinterConnectionDialog::name() const
{
	return _name;
}

void PrinterConnectionDialog::onNameChanged(const QString &name)
{
	_name = name;

}

void PrinterConnectionDialog::onAddressChanged(const QString &address)
{
	_address = address;
}

void PrinterConnectionDialog::buildDialog()
{

}

