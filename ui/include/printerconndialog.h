#ifndef PRINTER_CONNECTION_DIALOG
#define PRINTER_CONNECTION_DIALOG

#include <QtGui>
#include "ui_addprinterdialog.h"
#include <QDialog>
#include <QLineEdit>


class PrinterConnectionDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit PrinterConnectionDialog(QWidget * parent = nullptr);
		PrinterConnectionDialog(const QString& name, const QString& address, QWidget * parent = nullptr);

		QString address() const;
		QString name() const;

	private slots:
		void onValidate();

	private:
		QString _address;
		QString _name;
		Ui::AddPrinterDialog ui;

		void configure();

};

#endif
