#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QMainWindow>
#include "printersmanager.h"

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget* parent = nullptr);
		virtual ~MainWindow();

	protected:
		void loadMenus();

	private slots:
		void onAddPrinter();

	private:
		Macsa::PrintersManager _manager;

};

#endif //UI_MAIN_WINDOW_H
