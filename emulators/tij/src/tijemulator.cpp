#include "tijemulator.h"

using namespace Macsa;
using namespace Macsa::Printers;

TIJEmulator::TIJEmulator()
{
	_controllerVersion = "Emulator v";
	_controllerVersion += EMULATOR_VERSION_STR;

	_apiVersion = "MComms v1.0.0";

	init();
}

TIJEmulator::~TIJEmulator()
{}

void TIJEmulator::init()
{
	Board board(0, dynamic_cast<TijPrinter*>(this));
	initBoard(board);
	_boards.clear();
	_boards.push_back(board);
}

void TIJEmulator::initBoard(Board &board)
{
	board.setType("emulator");
	board.setAutoStart(false);
	board.setBlocked(true);
	board.setEnabled(false);
	board.setPrinting(false);
	board.setBcdMode(Printers::nBCDMode::USER_MODE);
}
