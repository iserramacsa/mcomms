#include <iostream>
#include "printersmanager.h"

#define PRINTER_TEST_NAME	"TIJPrinter"

int main(int argc, char* argv[])
{
	Macsa::PrintersManager _manager;
	if (_manager.addTijPrinter(PRINTER_TEST_NAME, "192.168.1.64") ) {
		std::cout << PRINTER_TEST_NAME << " added" << std::endl;
	}
	else {
		std::cout << PRINTER_TEST_NAME << "NOT added" << std::endl;
	}

	_manager.disconnectTijPrinter(PRINTER_TEST_NAME);

	return 0;
}
