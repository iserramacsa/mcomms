#include "emulatorwindow.h"

EmulatorWindow::EmulatorWindow(Macsa::Printers::TIJEmulator &emulator, QWidget *parent) :
	QMainWindow(parent),
	_emulator(emulator)
{
	build();

	onUpdateData();
}

EmulatorWindow::~EmulatorWindow()
{
}

void EmulatorWindow::onUpdateData()
{
	_autostart->setChecked(_emulator.board(0)->autoStart());
}

void EmulatorWindow::build()
{
	QWidget* root = new QWidget(this);
	root->setMinimumSize(300, 600);
	QFormLayout* layout = new QFormLayout(root);

	_autostart = new QCheckBox(root);
	layout->addRow("Autostart:", _autostart);

	setCentralWidget(root);
}
