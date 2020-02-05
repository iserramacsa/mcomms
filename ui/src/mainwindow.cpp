#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include "printerconndialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	this->setWindowTitle(QString("%1 v%2").arg(UI_PROJECT_NAME).arg(UI_VERSION_STR));
	ui.setupUi(this);
	loadMenus();
	loadPrintersList();
	loadView();
}

MainWindow::~MainWindow()
{}

void MainWindow::loadMenus()
{
	connect(ui.butAddPrinter, SIGNAL(clicked(bool)), SLOT(onAddPrinter()));
	connect(ui.butRemPrinter, SIGNAL(clicked(bool)), SLOT(onDelPrinter()));
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

void MainWindow::onAddPrinter()
{
	PrinterConnectionDialog * dialog = new PrinterConnectionDialog(this);

	if( dialog->exec()) {
		qDebug() << __func__  << " id: " << dialog->name() << " - "  << dialog->address();
		if (_manager.addTijPrinter(dialog->name().toStdString(), dialog->address().toStdString())) {
			QStringList list = _printersListModel->stringList();
			list << QString("%1: %2").arg(dialog->name()).arg(dialog->address());
			_printersListModel->setStringList(list);
			if (list.count() == 1) {
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
			QString name = controller->id().c_str();
			_manager.removeTijPrinter(name.toStdString());

			QStringList list = _printersListModel->stringList();
			list.removeOne(name);
			_printersListModel->setStringList(list);
			if (list.count() == 1) {
				onPrinterSelected(_printersListModel->index(0));
			}
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
	}
	else {
		_printerView->clear();
		ui.printerHolder->setEnabled(false);
	}
}
