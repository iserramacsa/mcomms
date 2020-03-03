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
#include "printercommsview.h"

class PrinterView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterView(QWidget* parent = 0);
		~PrinterView();
		void setController(Macsa::TijController& controller);
		void clear();

	private:
		TIJViewerController* _controller;
		PrinterStatusView*	_printerStatusView;
		PrinterConfigView*	_printerConfigView;
		PrinterCommsView*	_printerCommsView;
		PrinterFilesView*	_printerFilesView;
		QTableWidget*		_printerErrorsLog;
		QTimer				_dtTimer;
		Ui::printerView ui;

		virtual void resizeEvent(QResizeEvent *);

		void updateLogs();
		void setPrinterStatus(TIJViewerController::TijStatus status);

		void buildStatus();
		void buildConfig();
		void buildComms();
		void buildFiles();
		void buildErrorsLog();
		void resizeErrorsLog();

	private slots:		
		void refresh();
		void onRequestLive();
		void onRequestConfig();
		void onRequestStatus();
		void onRequestFiles();
		void onRequestFonts();
		void onRequestImages();
		void onRequestMessages();
		void onRequestErrorsLog();
		void onConnectClicked();
		void onRequestedChanges();
		void onUpdateDateTime();
};


#endif //PRINTER_VIEW_H
