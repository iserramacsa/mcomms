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
		enum class ServerType
		{
			TIJ_EMULATOR = 0,
			TIJ_PRINTER
		};
	public:
		explicit PrinterConnectionDialog(QWidget * parent = nullptr);
		PrinterConnectionDialog(const QString& name, const QString& address, uint16_t port, QWidget * parent = nullptr);

		QString address() const;
		QString name() const;
		uint16_t port() const;
		ServerType serverType() const;
		QString strType() const;


	private slots:
		void onValidate();
		void onChangeServerType(const QString &);

	private:
		QString _address;
		QString _name;
		ServerType _type;
		uint16_t _port;
		Ui::AddPrinterDialog ui;
		QMap<QString, ServerType>_availableServers;

		void configure();
		QStringList getAvailablePrinters();
};

#endif
