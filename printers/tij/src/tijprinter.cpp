#include "printer/tijprinter.h"

using namespace Macsa;
using namespace Macsa::Printer;


TIJPrinter::TIJPrinter()
{
	_id = 0;
	_statusChanged = false;
	_configChanged = false;
	_filesChanged = false;
	_fontsChanged = false;
	_errorsChanged = false;
	_type = "SM200";
	_currentMessage = "";
}

TIJPrinter::~TIJPrinter()
{

}
