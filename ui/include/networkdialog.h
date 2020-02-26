#ifndef PRINTERS_NETWORK_DIALOG_H
#define PRINTERS_NETWORK_DIALOG_H

#include <QtGui>
#include "ui_networkdialog.h"
#include <QDialog>
#include <QLineEdit>
#include "printersmanager.h"
#include "network/nodeobserver.h"

typedef Macsa::Network::NetworkNode::NodeStatus_n NodeStatus;

class PrinterItem : public QWidget, public Macsa::Network::NodeObserver
{
		Q_OBJECT
	public:
		explicit PrinterItem(Macsa::PrinterController* printer, Macsa::PrintersManager& manager, QWidget * parent = nullptr);

	private:
		Macsa::PrinterController* _printer;
		Macsa::PrintersManager& _manager;
		QLabel* _status;

		virtual void nodeStatusChanged(const NodeStatus& status);
		virtual void nodeTimeout();
};

class NetworkDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit NetworkDialog(Macsa::PrintersManager& manager, QWidget * parent = nullptr);

	private slots:
		void onValidate();
		void onDiscoverPrinters();
		void onPrinterDetected(const QString& name, const QString address);

	private:
		Macsa::PrintersManager& _manager;
		Ui::networkDialog ui;
		QVBoxLayout* _printersList;

		void configure();
		void refreshPrintersList();
};

#endif //PRINTERS_NETWORK_DIALOG_H
