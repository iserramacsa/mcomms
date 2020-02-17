#include "printerconndialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>

PrinterConnectionDialog::PrinterConnectionDialog(QWidget *parent) :
	QDialog(parent)
{
	configure();
}

PrinterConnectionDialog::PrinterConnectionDialog(const QString &name, const QString &address, uint16_t port, QWidget *parent) :
	QDialog(parent)
{
	configure();
	_name = name;
	_address = address;

	ui.printerId->setText(_name);
	ui.printerAddress->setText(_address);
	ui.printerPort->setValue(port);
}

QString PrinterConnectionDialog::address() const
{
	return _address;
}

QString PrinterConnectionDialog::name() const
{
	return _name;
}

uint16_t PrinterConnectionDialog::port() const
{
	return _port;
}

PrinterConnectionDialog::ServerType PrinterConnectionDialog::serverType() const
{
	return _type;
}

QString PrinterConnectionDialog::strType() const
{
	switch (_type)
	{
		case ServerType::TIJ_EMULATOR: return "TIJ_EMULATOR";
		case ServerType::TIJ_PRINTER: return "TIJ_PRINTER";
	}
	return "";
}

void PrinterConnectionDialog::onValidate()
{
	if (_type == ServerType::TIJ_PRINTER){
		_name = ui.printerId->text();
		_address = ui.printerAddress->text();
		_port = static_cast<uint16_t>(ui.printerPort->value());
	}
	else if (_type == ServerType::TIJ_EMULATOR){
		_name = "TijEmulator";
		_address = "127.0.0.2";
		_port = static_cast<uint16_t>(ui.emulatorPort->value());
	}
	accept();
}

void PrinterConnectionDialog::onChangeServerType(const QString &name)
{
	_type = _availableServers.value(name);
	if (_type == ServerType::TIJ_PRINTER) {
		ui.printerForm->setVisible(true);
		ui.emulatorForm->setVisible(false);
	}
	else if (_type == ServerType::TIJ_EMULATOR){
		ui.printerForm->setVisible(false);
		ui.emulatorForm->setVisible(true);
	}
}


void PrinterConnectionDialog::configure()
{
	_type = ServerType::TIJ_PRINTER;
	ui.setupUi(this);
	setWindowTitle("Printer connection");

	ui.printerCB->addItems(getAvailablePrinters());
	connect(ui.printerCB, SIGNAL(currentIndexChanged(const QString &)), SLOT(onChangeServerType(const QString &)));

	ui.printerForm->setVisible(false);
	ui.emulatorForm->setVisible(false);

	QPushButton * okButt = ui.buttonBox->button(QDialogButtonBox::Ok);
	connect(okButt, SIGNAL(clicked()), SLOT(onValidate()));

	QPushButton * cancelButt = ui.buttonBox->button(QDialogButtonBox::Cancel);
	connect(cancelButt, SIGNAL(clicked()), SLOT(reject()));
}

QStringList PrinterConnectionDialog::getAvailablePrinters()
{
	QDir dir("./");
	if (dir.cd("emulators")){
		if (dir.cd("tij")){
			_availableServers.insert("TIJEmulator", ServerType::TIJ_EMULATOR);
			dir.cdUp();
		}
		dir.cdUp();
	}
	if (dir.cd("printers")){
		if (dir.cd("tij")){
			_availableServers.insert("TIJPrinter", ServerType::TIJ_PRINTER);
			dir.cdUp();
		}
		dir.cdUp();
	}
	return _availableServers.keys();
}

