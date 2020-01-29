#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QMainWindow>
#include "network/network.h"
#include <QtGui>
#include "ui_mainwindow.h"
#include "printersmanager.h"
#include "printerslistmodel.h"

#include <QStandardItemModel>

class MainWindow : public QMainWindow
{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget* parent = nullptr);
		virtual ~MainWindow();

	protected:
		void loadMenus();
		void loadPrintersList();

	private slots:
		void onAddPrinter();
		void onPrinterSelected(const QModelIndex& index);

	private:
		QStringListModel* _printersListModel;
		Macsa::PrintersManager _manager;
		Ui::MainWindow ui;

};

#endif //UI_MAIN_WINDOW_H
