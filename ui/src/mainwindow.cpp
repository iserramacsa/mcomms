#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include "printerConnDialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	loadMenus();
}

MainWindow::~MainWindow()
{}

void MainWindow::loadMenus()
{
	QToolBar* toolBar = new QToolBar("Printer", this);
	this->addToolBar(toolBar);

	QMenuBar* menu = new QMenuBar(this);
	this->setMenuBar(menu);


	QMenu* printer = menu->addMenu("Printer");
	QAction* action = printer->addAction("&Add printer");
	toolBar->addAction(action);

	connect(action, SIGNAL(changed()), SLOT(onAddPrinter()));
}

void MainWindow::onAddPrinter()
{
	PrinterConnectionDialog * dialog = new PrinterConnectionDialog(this);

	if( dialog->exec()) {
		qDebug() << __func__  << " id: " << dialog->name() << " - "  << dialog->address();
	}

}
