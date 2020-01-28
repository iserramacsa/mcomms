#include "printer/printer.h"
#include <sstream>

using namespace Macsa;
using namespace Macsa::Printers;


Printer::Printer()
{
	_id = 0;
	_lastUpdate = time(nullptr);
	_dt = time(nullptr);
//	_statusChanged = false;
//	_configChanged = false;
//	_filesChanged = false;
//	_fontsChanged = false;
//	_errorsChanged = false;
}

Printer::~Printer()
{}

std::string Printer::type() const {return _type;}

int Printer::id() const {return _id;}
void Printer::setId(int id) { _id = id;}

std::time_t Printer::dateTime() const
{
	time_t now = time(nullptr);
	double update = difftime(now, _lastUpdate);

	time_t dateTime = static_cast<time_t>(_dt + update);

	return dateTime;
}

void Printer::setDateTime(const std::time_t& dateTime)
{
	_dt = dateTime;
	_lastUpdate = time(nullptr);
}


//bool Printer::statusChanged() const {return _statusChanged;}
//void Printer::setStatusChanged(bool changed){_statusChanged = changed;}

//bool Printer::configChanged() const {return _configChanged;}
//void Printer::setConfigChanged(bool changed){_configChanged = changed;}

//bool Printer::filesChanged() const {return _filesChanged;}
//void Printer::setFilesChanged(bool changed) {_filesChanged = changed;}

//bool Printer::fontsChanged() const {return _fontsChanged;}
//void Printer::setFontsChanged(bool changed) {_fontsChanged = changed;}

//bool Printer::errorsChanged() const {return _errorsChanged;}
//void Printer::setErrorsChanged(bool changed) {_errorsChanged = changed;}

//Configuration& Printer::configuration()
//{
//	return _configuration;
//}

//const Configuration& Printer::configuration() const
//{
//	return _configuration;
//}

//Status& Printer::status()
//{
//	return _status;
//}

//const Status& Printer::status() const
//{
//	return _status;
//}

//PrinterFiles& Printer::files()
//{
//	return *_files;
//}

//const PrinterFiles& Printer::files() const
//{
//	return *_files;
//}

//PrinterComms& Printer::comms()
//{
//	return *_comms;
//}

//const PrinterComms &Printer::comms() const
//{
//	return *_comms;
//}
