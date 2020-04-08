#ifndef JET_PRINTER_STATUS_VIEW_H
#define JET_PRINTER_STATUS_VIEW_H

#include <QWidget>
#include <QtGui>
#include <QTimer>
#include "viewers/jetviewercontroller.h"
#include "jet/jetcontroller.h"
#include <QCheckBox>
#include <QLabel>
#include <QMap>
#include <QTableWidget>

class JetStatusView : public QWidget
{
		Q_OBJECT
	public:
		explicit JetStatusView(QWidget* parent = 0);
		~JetStatusView();
		void setController(Macsa::MComms::JetController& controller);

	public slots:
		void refresh();

	private:
		QLabel*		_type;
		QLabel*		_sscc;
		QCheckBox*	_inverted;
		QCheckBox*	_paused;
		QCheckBox*	_printStatus;
		QCheckBox*	_isInError;

		QTableWidget* _errors;

//		QMap<QString, QLabel*> _counters;

//		QMap<QLabel*, QLabel*> _inkTanks; // QTableWidget* _inkTanks;
//		QGridLayout* _gridInkTanks;

//		QMap<QString, QLabel*> _inputs; // QTableWidget* _inputs;
//		QGridLayout* _gridInputs;

//		QMap<QString, QLabel*> _outputs;
//		QGridLayout* _gridOutputs;

//		QFormLayout* _propLayout;
//		QMap<QString, QLabel*> _props;

		JetViewerController* _controller;

		virtual void resizeEvent(QResizeEvent *);

		void build();
//		QWidget* buildCounters();
//		QWidget* buildInputs();

		void printerDisconnected();

//		void updateErrors(const std::vector<Macsa::Printers::JetLogType> &errors);
//		void updateInputs(const QVector<Macsa::Printers::JetIO> &inputs);
//		void updateOutputs(const QVector<Macsa::Printers::JetIO> &outputs);
//		void updateProperties(const QMap<QString, QString> &prop);
};


#endif //PRINTER_VIEW_H
