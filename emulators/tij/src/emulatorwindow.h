#ifndef UI_MAIN_EMULATOR_WINDOW_H
#define UI_MAIN_EMULATOR_WINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "clientmanager.h"
//#include "ui_emulatorwindow.h"


class EmulatorWindow : public QMainWindow
{
		Q_OBJECT
	public:
		explicit EmulatorWindow(ClientManager& manager, QWidget* parent = nullptr);
		virtual ~EmulatorWindow();

	protected:

	private slots:

	private:
//		Ui::EmulatorWindow ui;
		ClientManager& _manager;

};

#endif //UI_MAIN_WINDOW_H
