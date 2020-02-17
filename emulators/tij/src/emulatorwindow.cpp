#include "emulatorwindow.h"

EmulatorWindow::EmulatorWindow(ClientManager& manager, QWidget *parent) :
	QMainWindow(parent),
	_manager(manager)
{
//	ui.setupUi(this);
	manager.run();
}

EmulatorWindow::~EmulatorWindow()
{
	_manager.stop();
}
