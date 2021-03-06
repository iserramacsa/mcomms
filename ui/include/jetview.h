#ifndef JET_PRINTER_VIEW_H
#define JET_PRINTER_VIEW_H

#include <QWidget>
#include <QtGui>
#include "ui_jetview.h"
#include "viewers/jetviewercontroller.h"
#include "jet/jetcontroller.h"
#include "jetstatusview.h"
#include "jetconfigview.h"
#include "jetfilesview.h"
#include "jetmsgmanager.h"
//#include "printercommsview.h"

class JetView : public QWidget
{
		Q_OBJECT
	public:
		explicit JetView(QWidget* parent = 0);
		~JetView();
		void setController(Macsa::MComms::JetController& controller);
		void clear();

	private:
		JetViewerController* _controller;
		JetStatusView*		_statusView;
		JetConfigView*		_configView;
		JetMessageManager*  _messageManager;
//		JetCommsView*		_commsView;
		JetFilesView*		_filesView;
		QTableWidget*		_printerErrorsLog;
		QTimer				_dtTimer;
		Ui::jetView ui;

		virtual void resizeEvent(QResizeEvent *);

		void updateLogs();
		void setPrinterStatus(JetViewerController::JetStatus status);

		void buildStatus();
		void buildConfig();
		void buildMessageManager();
//		void buildComms();
		void buildFiles();
		void buildErrorsLog();
		void resizeErrorsLog();

	private slots:		
		void refresh();
		void onRequestConfig();
		void onRequestStatus();
//		void onRequestFiles();
//		void onRequestFonts();
//		void onRequestImages();
//		void onRequestMessages();
//		void onRequestErrorsLog();
		void onConnectClicked();
		void onUpdateDateTime();
};


#endif //JET_PRINTER_VIEW_H
