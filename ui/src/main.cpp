/*********************************************************/
/*	Project: MComms ui test application                  */
/*  Macsa 2020                                           */
/*********************************************************/
#include <iostream>
#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"

#define WIN_MIN_WIDTH	600
#define WIN_MIN_HEIGHT	400

int main (int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow win;

	QRect rWin = app.desktop()->geometry();

	rWin.setX((rWin.width() - WIN_MIN_WIDTH * 2));
	rWin.setY((rWin.height() - WIN_MIN_HEIGHT) / 2);
	rWin.setWidth(WIN_MIN_WIDTH);
	rWin.setHeight(WIN_MIN_HEIGHT);

	win.setGeometry(rWin);

	win.show();

	return app.exec();
}
