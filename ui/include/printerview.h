#ifndef PRINTER_VIEW_H
#define PRINTER_VIEW_H

#include <QWidget>
#include <QtGui>
#include "ui_printerview.h"
#include "viewers/tijviewercontroller.h"
#include "tijprintercontroller.h"

class PrinterView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterView(QWidget* parent = 0);
		~PrinterView();
		void setController(Macsa::TIJPrinterController& controller);

	private:
		TIJViewerController* _controller;
		Ui::PrinterView ui;

		void refresh();


	private slots:
		void onRequestLive();
		void onRequestConfig();
		void onRequestStatus();
};


#endif //PRINTER_VIEW_H
