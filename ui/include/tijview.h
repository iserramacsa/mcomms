#ifndef TIJ_PRINTER_VIEW_H
#define TIJ_PRINTER_VIEW_H

#include <QWidget>
#include <QtGui>
#include "ui_tijview.h"
#include "viewers/tijviewercontroller.h"
#include "tij/tijcontroller.h"
#include "tijstatusview.h"
#include "tijconfigview.h"
#include "tijcommsview.h"
#include "printerfilesview.h"

class TijView : public QWidget
{
		Q_OBJECT
	public:
		explicit TijView(QWidget* parent = 0);
		~TijView();
		void setController(Macsa::MComms::TijController& controller);
		void clear();

	private:
		TIJViewerController* _controller;
		TijStatusView*		_statusView;
		TijConfigView*	_configView;
		TijCommsView*	_commsView;
		PrinterFilesView*	_filesView;
		QTableWidget*		_errorsLogTable;
		QTimer				_dtTimer;
		Ui::tijView ui;

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


#endif //TIJ_PRINTER_VIEW_H
