#ifndef PRINTERS_NETWORK_DIALOG_H
#define PRINTERS_NETWORK_DIALOG_H

#include <QtGui>
#include "ui_networkdialog.h"
#include <QDialog>
#include <QLineEdit>
#include "printersmanager.h"


class NetworkDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit NetworkDialog(QWidget * parent = nullptr);

	private slots:
		void onValidate();
		void onDiscoverPrinters();
		void onPrinterDetected(const QString& name, const QString address);

	private:
		Macsa::PrintersManager manager;
		Ui::networkDialog ui;
		QVBoxLayout* _printersList;


		void configure();
};

#endif //PRINTERS_NETWORK_DIALOG_H
