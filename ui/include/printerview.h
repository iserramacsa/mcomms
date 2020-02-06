#ifndef PRINTER_VIEW_H
#define PRINTER_VIEW_H

#include <QWidget>
#include <QtGui>
#include "ui_printerview.h"
#include "viewers/tijviewercontroller.h"
#include "tijprintercontroller.h"
#include "printerstatusview.h"
#include "printerfilesview.h"
#include "printerconfigview.h"

class PrinterView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterView(QWidget* parent = 0);
		~PrinterView();
		void setController(Macsa::TIJPrinterController& controller);
		void clear();

	private:
		TIJViewerController* _controller;
		PrinterStatusView* _printerStatusView;
		PrinterConfigView* _printerConfigView;
		PrinterFilesView* _printerFilesView;
		Ui::printerView ui;

		void refresh();
		void setPrinterStatus(TIJViewerController::TIJStatus status);

		void buildStatus();
		void buildConfig();
		void buildFiles();

	private slots:
		void onRequestLive();
		void onRequestConfig();
		void onRequestStatus();
		void onRequestFiles();
		void onConnectClicked();
};


#endif //PRINTER_VIEW_H
