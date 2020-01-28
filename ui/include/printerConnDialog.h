#ifndef PRINTER_CONNECTION_DIALOG
#define PRINTER_CONNECTION_DIALOG

#include <QDialog>

class PrinterConnectionDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit PrinterConnectionDialog(QWidget * parent = nullptr);
		PrinterConnectionDialog(const QString& name, const QString& address, QWidget * parent = nullptr);

		QString address() const;
		QString name() const;

	private slots:
		void onNameChanged(const QString& name);
		void onAddressChanged(const QString& address);

	private:
		QString _address;
		QString _name;
		//		uint16_t _port;

		void buildDialog();
};

#endif
