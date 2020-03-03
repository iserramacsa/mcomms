#ifndef UI_MAIN_EMULATOR_WINDOW_H
#define UI_MAIN_EMULATOR_WINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "tijemulator.h"


class EmulatorWindow : public QMainWindow
{
		Q_OBJECT
	public:
		explicit EmulatorWindow(Macsa::Printers::TIJEmulator & emulator, QWidget* parent = nullptr);
		virtual ~EmulatorWindow();

	protected:

	public slots:
		void onUpdateData();

	private:
		Macsa::Printers::TIJEmulator & _emulator;

		QCheckBox* _autostart;

		void build();
};

#endif //UI_MAIN_WINDOW_H
