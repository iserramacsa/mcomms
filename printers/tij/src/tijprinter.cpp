#include "tij/tijprinter.h"

using namespace Macsa;
using namespace Macsa::Printers;


TIJPrinter::TIJPrinter()
{
	_id = 0;
	_statusChanged = false;
	_configChanged = false;
	_filesChanged = false;
	_fontsChanged = false;
	_errorsChanged = false;
	_type = "SM200";
}

TIJPrinter::~TIJPrinter()
{

}
