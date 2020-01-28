#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include "printerconndialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);
	loadMenus();
	loadPrintersList();
}

MainWindow::~MainWindow()
{}

void MainWindow::loadMenus()
{
	connect(ui._buttAddPrinter, SIGNAL(clicked(bool)), SLOT(onAddPrinter()));
}

void MainWindow::loadPrintersList()
{
	_printersListModel = new PrintersListModel(this);
	_printersListModel->setColumnCount(1);
	QStandardItem* item = new QStandardItem("Printers list");
	_printersListModel->setVerticalHeaderItem(0, item);
	_printersListModel->setHorizontalHeaderItem(0, item);

	//_printersListModel->setVerticalHeaderItem(0, item);
	//_printersListModel->setHeaderData(0, Qt::Orientation::Vertical, "Printers", Qt::DisplayRole);
	ui._listPrinters->setModel(_printersListModel);
}

void MainWindow::onAddPrinter()
{
	PrinterConnectionDialog * dialog = new PrinterConnectionDialog(this);

	if( dialog->exec()) {
		qDebug() << __func__  << " id: " << dialog->name() << " - "  << dialog->address();
		if (_manager.addTijPrinter(dialog->name().toStdString(), dialog->address().toStdString())) {
			QStandardItem* item = new QStandardItem(QString("%1: %2").arg(dialog->name()).arg(dialog->address()));
			_printersListModel->appendRow(item);
		}
	}

}
