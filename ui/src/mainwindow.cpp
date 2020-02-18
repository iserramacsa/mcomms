#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include "printerconndialog.h"
#include "networkdialog.h"

#include <QDebug>

#define EMULATORS_PATH	"./emulators"
#define EMULATOR_TIJ	EMULATORS_PATH "/tij/TIJEmulator"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	this->setWindowTitle(QString("%1 v%2").arg(UI_PROJECT_NAME).arg(UI_VERSION_STR));
	ui.setupUi(this);
	loadMenus();
	loadPrintersList();
	loadView();
	_emulators.clear();
}

MainWindow::~MainWindow()
{
	while (_emulators.count()) {
		QProcess* p = _emulators.last();
		delete p;
		_emulators.pop_back();
	}
}

void MainWindow::loadMenus()
{
	connect(ui.butAddPrinter, SIGNAL(clicked(bool)), SLOT(onAddPrinter()));
	connect(ui.butRemPrinter, SIGNAL(clicked(bool)), SLOT(onDelPrinter()));
	connect(ui.butNetwork, SIGNAL(clicked(bool)), SLOT(onManageNetwork()));
}

void MainWindow::loadPrintersList()
{
	_printersListModel = new QStringListModel(this);
	ui.listPrinters->setModel(_printersListModel);

	connect(ui.listPrinters, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(onPrinterSelected(const QModelIndex&)));
}

void MainWindow::loadView()
{
	QVBoxLayout* layout = new QVBoxLayout();
	_printerView = new PrinterView(this);
	ui.printerHolder->setLayout(layout);
	layout->addWidget(_printerView);
	_printerView->setEnabled(false);
}

void MainWindow::onManageNetwork()
{
	NetworkDialog* dialog = new NetworkDialog(this);
	if(dialog->exec()) {

	}
}

void MainWindow::onAddPrinter()
{
	PrinterConnectionDialog * dialog = new PrinterConnectionDialog(this);

	if( dialog->exec()) {
		QString name = dialog->name();
		QString address = dialog->address();
		uint16_t port = dialog->port();
		qDebug() << __func__  << " Type: " << dialog->strType() << " id: " << name << " - "  << address;
		switch (dialog->serverType())
		{
			case PrinterConnectionDialog::ServerType::TIJ_EMULATOR:
				{
					QProcess* emulator = new QProcess();
					emulator->start(EMULATOR_TIJ, QStringList() << "-p" << QString("%1").arg(port));
					_emulators.push_back(emulator);
				}
				break;
			default:
			//case PrinterConnectionDialog::ServerType::TIJ_PRINTER:
				break;
		}
		bool monitorize = false;
		if (_manager.addTijPrinter(name.toStdString(), address.toStdString(), monitorize)) {
			refreshPrintersList();
			if (_printersListModel->stringList().count() == 1) {
				onPrinterSelected(_printersListModel->index(0));
			}
		}
	}
}

void MainWindow::onDelPrinter()
{
	int row = ui.listPrinters->currentIndex().row();
	if (row >= 0) {
		Macsa::TIJPrinterController * controller = dynamic_cast<Macsa::TIJPrinterController*>(_manager.getPrinter(row));
		if (controller != nullptr) {
			controller->disconnect();
			QString name = QString("%1: %2").arg(controller->id().c_str()).arg(controller->address().c_str());
			_manager.removeTijPrinter(controller->id().c_str());

			refreshPrintersList();
		}
	}
}

void MainWindow::onPrinterSelected(const QModelIndex &index)
{
	int row = index.row();
	Macsa::TIJPrinterController * controller = dynamic_cast<Macsa::TIJPrinterController*>(_manager.getPrinter(row));
	if (controller){
		qDebug() << __func__  << " Selected printer: " << controller->id().c_str();
		_printerView->setController(*controller);
		_printerView->setEnabled(true);
	}
	else {
		_printerView->clear();
		_printerView->setEnabled(false);
	}
}

void MainWindow::refreshPrintersList()
{
	_printersListModel->setStringList(QStringList());
	QStringList list;
	for (int p = 0; p < static_cast<int>(_manager.size()); p++) {
		const Macsa::PrinterController* controller = _manager.getPrinter(p);
		if (controller != nullptr){
			list << QString("%1: %2").arg(controller->id().c_str()).arg(controller->address().c_str());
		}
	}
	_printersListModel->setStringList(list);
	if (!list.count()) {
		_printerView->clear();
		_printerView->setEnabled(false);
	}
}
