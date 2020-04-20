/*********************************************************/
/*	Project: MComms ui test application                  */
/*  Macsa 2020                                           */
/*********************************************************/
#include <iostream>
#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"

#define WIN_MIN_WIDTH	1200
#define WIN_MIN_HEIGHT	600

int main (int argc, char* argv[])
{
#if defined (DEBUG)
	#if defined (ARMSTONE_A9) || defined (LOCO)
	const char* qws_mouse = "tslib:/dev/input/event0" ;
	QByteArray d( qws_mouse, static_cast<int>(strlen(qws_mouse))) ;
	qputenv("QWS_MOUSE_PROTO", d) ;
	qputenv("TSLIB_TSDEVICE", d) ;
	#endif
#endif

	QApplication app(argc, argv);
	MainWindow win;

#if defined (ARMSTONE_A9) || defined (LOCO)
	win.setWindowFlags(Qt::FramelessWindowHint);
	win.showFullScreen();
#else
	QRect rWin = app.desktop()->geometry();

	rWin.setX(((rWin.width()/2 - WIN_MIN_WIDTH) / 2) + rWin.width()/2);
	rWin.setY((rWin.height() - WIN_MIN_HEIGHT) / 2);
	rWin.setWidth(WIN_MIN_WIDTH);
	rWin.setHeight(WIN_MIN_HEIGHT);

	win.setGeometry(rWin);
	win.show();
#endif

	return app.exec();
}
