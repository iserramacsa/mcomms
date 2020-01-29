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
	_printersListModel = new QStringListModel(this);
	ui._listPrinters->setModel(_printersListModel);

	connect(ui._listPrinters, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(onPrinterSelected(const QModelIndex&)));
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
//			QStandardItem* item = new QStandardItem(QString("%1: %2").arg(dialog->name()).arg(dialog->address()));
//			_printersListModel->appendRow(item);
		}
	}

}

void MainWindow::onPrinterSelected(const QModelIndex &index)
{
	int row = index.row();
	qDebug() << __func__  << " Selected printer: " << _manager.getPrinter(row)->id().c_str();

}
