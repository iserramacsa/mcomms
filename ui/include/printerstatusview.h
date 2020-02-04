#ifndef PRINTER_STATUS_VIEW_H
#define PRINTER_STATUS_VIEW_H

#include <QWidget>
#include <QtGui>
#include "viewers/tijviewercontroller.h"
#include "tijprintercontroller.h"
#include <QCheckBox>
#include <QLabel>
#include <QMap>
#include <QTableWidget>

class PrinterStatusView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterStatusView(QWidget* parent = 0);
		~PrinterStatusView();
		void setController(Macsa::TIJPrinterController& controller);

	public slots:
		void refresh();

	private:
		TIJViewerController* _controller;
		void build();
		void printerDisconnected();

		QLabel*	   _printerType;
		QCheckBox* _printerAutostart;
		QLabel* _printerUserMessage;
		QLabel* _printerBcdMode;
		QLabel* _printerBcdStatus;
		QMap<QString, QLabel*> _counters;
		QTableWidget* _inputs;
		// QLabel* _printerVersionCtrl;
		// QLabel* _printerVersionFPGA;
		// QLabel* _printerVersionAPI;
		//Counters


		void updateInputs(const QVector<TIJViewerController::PrinterInput> &inputs);

};


#endif //PRINTER_VIEW_H
