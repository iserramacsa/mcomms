#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include "printerconndialog.h"
#include "networkdialog.h"

#include <QDebug>

#define EMULATORS_PATH	"./emulators"
#define EMULATOR_TIJ	EMULATORS_PATH "/tij/TIJEmulator"

using namespace Macsa;
using namespace Macsa::MComms;

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
	layout->setMargin(0);
	layout->setSpacing(0);
	_tijView = new TijView(this);
	_jetView = new JetView(this);
	ui.printerHolder->setLayout(layout);
	layout->addWidget(_tijView);
	layout->addWidget(_jetView);
	onPrinterSelected(QModelIndex());
}

void MainWindow::onManageNetwork()
{
	NetworkDialog* dialog = new NetworkDialog(_manager, this);
	if(dialog->exec()) {
		refreshPrintersList();
	}
}

void MainWindow::onAddPrinter()
{
	PrinterConnectionDialog * dialog = new PrinterConnectionDialog("TIJPrinter", "192.168.1.64", 9991, this);

	if( dialog->exec()) {
		QString name = dialog->name();
		QString address = dialog->address();
		uint16_t port = dialog->port();
//		qDebug() << __func__  << " Type: " << dialog->strType() << " id: " << name << " - "  << address;
		const bool monitorize = true;
		bool refresh = false;
		if (dialog->serverType() == PrinterConnectionDialog::ServerType::JET_PRINTER){
			refresh = _manager.addJetPrinter(name.toStdString(), address.toStdString(), monitorize);
		}
		else {
			if(dialog->serverType() == PrinterConnectionDialog::ServerType::TIJ_EMULATOR)
			{
				QProcess* emulator = new QProcess();
				emulator->start(EMULATOR_TIJ, QStringList() << "-p" << QString("%1").arg(port));
				_emulators.push_back(emulator);
			}
			refresh = _manager.addTijPrinter(name.toStdString(), address.toStdString(), monitorize);
		}
		if(refresh){
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
		MComms::PrinterController * controller = _manager.getPrinter(static_cast<uint>(row));
		if (controller != nullptr) {
			controller->disconnect();
			QString name = QString("%1: %2").arg(controller->id().c_str()).arg(controller->address().c_str());
			_manager.removePrinter(controller->id().c_str());

			refreshPrintersList();
		}
	}
}

void MainWindow::onPrinterSelected(const QModelIndex &index)
{
	int row = index.row();

	MComms::PrinterController* controller = _manager.getPrinter(static_cast<uint>(row));

	if(controller != nullptr) {
		Printers::Printer* printer = controller->printer();
		if (printer) {
			if (printer->type() == "idjet" && dynamic_cast<MComms::JetController*>(controller)){
				_jetView->setController(*(dynamic_cast<MComms::JetController*>(controller)));
				_jetView->setEnabled(true);
				_jetView->setVisible(true);
				_tijView->setVisible(false);
			}
			else if (printer->type() == "SM200" && dynamic_cast<MComms::TijController*>(controller)) {
				_tijView->setController(*(dynamic_cast<MComms::TijController*>(controller)));
				_tijView->setEnabled(true);
				_tijView->setVisible(true);
				_jetView->setVisible(false);
			}
		}
	}
	else {
		_tijView->clear();
		_tijView->setVisible(false);
		_jetView->clear();
		_jetView->setVisible(false);
	}
}


void MainWindow::refreshPrintersList()
{
	_printersListModel->setStringList(QStringList());
	QStringList list;
	for (uint p = 0; p < _manager.size(); p++) {
		const Macsa::MComms::PrinterController* controller = _manager.getPrinter(p);
		if (controller != nullptr){
			list << QString("%1: %2").arg(controller->id().c_str()).arg(controller->address().c_str());
		}
	}
	_printersListModel->setStringList(list);
	if (!list.count()) {
		_tijView->clear();
		_tijView->setEnabled(false);
	}
}
