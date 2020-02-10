#include "tijemulator.h"

using namespace Macsa;
using namespace Macsa::Printers;

TIJEmulator::TIJEmulator()
{
	init();
}

TIJEmulator::~TIJEmulator()
{

}

void TIJEmulator::init()
{
	Board board(0, dynamic_cast<TIJPrinter*>(this));

	board.setType("emulator");
	_boards.insert(_boards.begin(), board);
}
