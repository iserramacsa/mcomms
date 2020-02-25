#ifndef PRINTER_COMMS_VIEW_H
#define PRINTER_COMMS_VIEW_H

#include <QWidget>
#include "viewers/tijviewercontroller.h"
#include "tijprintercontroller.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include "printer/datatypes.h"

class PrinterCommsView : public QWidget
{
		Q_OBJECT
	private:
		struct netWidget
		{
			QLabel*     iface;
			QLineEdit*  address;
			QLineEdit*  netmask;
			QLineEdit*  gateway;
			QCheckBox*	dhcp;
			QLabel*		macAddress;
			QLabel*		port;
		};
		struct bleWidget
		{
			QLabel*     name;
			QCheckBox*	visible;
			QLabel*		password;
		};

	public:
		explicit PrinterCommsView(QWidget* parent = 0);
		~PrinterCommsView();
		void setController(Macsa::TijController& controller);

	public slots:
		void refresh();

	private:
		TIJViewerController* _controller;

		QVector<netWidget>	_ifaces;
		bleWidget			_ble;
		QPushButton* _butChangeConfig;

		void build();
		void clear();
		void refreshNetIface(int idx);
		void refreshBle();

		QLabel* getTitle(const QString& text);
		QWidget* buildNetworkAdapter();
		QWidget* buildBluetoothDevice();
		QLineEdit* createIpFormatedLineEditor(QWidget *parent);

	private slots:
		void onChangeConfiguration();
};


#endif //PRINTER_VIEW_H
