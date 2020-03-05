#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QMainWindow>
#include "network/network.h"
#include <QtGui>
#include "ui_mainwindow.h"
#include "printersmanager.h"
#include "printerslistmodel.h"
#include "printerview.h"

#include <QStandardItemModel>
#include <QProcess>

class MainWindow : public QMainWindow
{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget* parent = nullptr);
		virtual ~MainWindow();

	protected:
		void loadMenus();
		void loadPrintersList();
		void loadView();

	private slots:
		void onManageNetwork();
		void onAddPrinter();
		void onDelPrinter();
		void onPrinterSelected(const QModelIndex& index);

	private:
		QVector<QProcess*> _emulators;
		PrinterView *_printerView;
		QStringListModel *_printersListModel;
		Macsa::MComms::PrintersManager _manager;
		Ui::MainWindow ui;

		void refreshPrintersList();

};

#endif //UI_MAIN_WINDOW_H
