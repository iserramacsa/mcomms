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
		QWidget* buildCounters();
		QWidget* buildInputs();
		void printerDisconnected();

		QLabel*	   _printerType;
		QCheckBox* _printerAutostart;
		QLabel* _printerUserMessage;
		QLabel* _printerBcdMode;
		QLabel* _printerBcdStatus;

		QTableWidget* _errors;

		QMap<QString, QLabel*> _counters;

		QMap<QString, QLabel*> _inputs; // QTableWidget* _inputs;
		QGridLayout* _gridInputs;

		QMap<QString, QLabel*> _outputs;
		QGridLayout* _gridOutputs;

		QFormLayout* _propLayout;
		QMap<QString, QLabel*> _props;

		void updateErrors(const QVector<TIJViewerController::PrinterError> &errors);
		void updateInputs(const QVector<TIJViewerController::PrinterInput> &inputs);
		void updateOutputs(const QVector<TIJViewerController::PrinterOutput> &outputs);
		void updateProperties(const QMap<QString, QString> &prop);
};


#endif //PRINTER_VIEW_H
