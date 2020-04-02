#ifndef PRINTER_STATUS_VIEW_H
#define PRINTER_STATUS_VIEW_H

#include <QWidget>
#include <QtGui>
#include <QTimer>
#include "viewers/tijviewercontroller.h"
#include "tij/tijcontroller.h"
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
		void setController(Macsa::MComms::TijController& controller);

	public slots:
		void refresh();

	private:		
		QLabel*		_printerType;
		QCheckBox*	_printerAutostart;
		QLabel*		_printerCurrentMessage;
		QLabel*		_printerBcdMode;
		QLabel*		_printerBcdStatus;

		QTableWidget* _errors;

		QMap<QString, QLabel*> _counters;

		QMap<QString, QLabel*> _inputs; // QTableWidget* _inputs;
		QGridLayout* _gridInputs;

		QMap<QString, QLabel*> _outputs;
		QGridLayout* _gridOutputs;

		QFormLayout* _propLayout;
		QMap<QString, QLabel*> _props;

		TIJViewerController* _controller;

		virtual void resizeEvent(QResizeEvent *);

		void build();
		QWidget* buildCounters();
		QWidget* buildInputs();

		void printerDisconnected();

		void updateErrors(const std::vector<Macsa::Printers::Error> &errors);
		void updateInputs(const QVector<TIJViewerController::PrinterInput> &inputs);
		void updateOutputs(const QVector<TIJViewerController::PrinterOutput> &outputs);
		void updateProperties(const QMap<QString, QString> &prop);
};


#endif //PRINTER_VIEW_H
