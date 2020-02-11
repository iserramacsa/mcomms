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
		QTableWidget*	  _printerErrorsLog;
		Ui::printerView ui;

		virtual void resizeEvent(QResizeEvent *);

		void refresh();
		void updateLogs();
		void setPrinterStatus(TIJViewerController::TIJStatus status);

		void buildStatus();
		void buildConfig();
		void buildFiles();
		void buildErrorsLog();
		void resizeErrorsLog();

	private slots:
		void onRequestLive();
		void onRequestConfig();
		void onRequestStatus();
		void onRequestFiles();
		void onRequestFonts();
		void onRequestImages();
		void onRequestMessages();
		void onRequestErrorsLog();
		void onConnectClicked();
};


#endif //PRINTER_VIEW_H
