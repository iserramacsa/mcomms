#include "printer/printer.h"

using namespace Macsa;
using namespace Macsa::Printers;


Printer::Printer() :
	_status(_configuration)
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

Printer::~Printer()
{}

std::string Printer::type() const {	return _type;}

int Printer::id() const {return _id;}
void Printer::setId(int id) { _id = id;}

bool Printer::statusChanged() const {return _statusChanged;}
void Printer::setStatusChanged(bool changed){_statusChanged = changed;}

bool Printer::configChanged() const {return _configChanged;}
void Printer::setConfigChanged(bool changed){_configChanged = changed;}

bool Printer::filesChanged() const {return _filesChanged;}
void Printer::setFilesChanged(bool changed) {_filesChanged = changed;}

bool Printer::fontsChanged() const {return _fontsChanged;}
void Printer::setFontsChanged(bool changed) {_fontsChanged = changed;}

bool Printer::errorsChanged() const {return _errorsChanged;}
void Printer::setErrorsChanged(bool changed) {_errorsChanged = changed;}

std::string Printer::currentMessage() const {return _currentMessage;}
void Printer::setCurrentMessage(std::string currentMessage){_currentMessage = currentMessage;}

std::string Printer::dateTime() const { return _dateTime; }
void Printer::setDateTime(const std::string &dateTime) { _dateTime = dateTime; }

Configuration *Printer::configuration()
{
	return &_configuration;
}

const Configuration *Printer::configuration() const
{
	return &_configuration;
}

Status *Printer::status()
{
	return &_status;
}

const Status *Printer::status() const
{
	return &_status;
}

PrinterFiles *Printer::files()
{
	return &_files;
}

const PrinterFiles *Printer::files() const
{
	return &_files;
}
