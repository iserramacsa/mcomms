#include "tijviewer.h"

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Network;
using namespace Macsa::Printers;

TijViewer::TijViewer(TijController &controller) :
	TijObserver(&controller),
	Network::NodeObserver(&controller),
	_controller(controller)
{}

TijViewer::~TijViewer()
{}

std::vector<std::string> TijViewer::printerDrives() const
{
	std::vector<std::string> drives;
	if (tijprinter().files()) {
		drives = tijprinter().files()->getDrives();
	}
	return drives;
}

std::vector<std::string> TijViewer::printerDirectory(const std::string& drive) const
{
	std::vector<std::string> directories;
	if (tijprinter().files()) {
		directories = tijprinter().files()->getDirectories(drive);
	}
	return directories;
}

std::vector<std::string> TijViewer::printerFiles(const std::string& drive, const std::string& folder) const
{
	std::vector<std::string> files;
	if (tijprinter().files()) {
		files = tijprinter().files()->getFiles(drive, folder);
	}
	return files;
}

std::vector<std::string> TijViewer::printerFiles(const std::string& filter) const
{
	std::vector<std::string> files;
	if (tijprinter().files()) {
		files = tijprinter().files()->getAllFiles(filter);
	}
	return files;
}

const Drive* TijViewer::getPrinterDrive(const std::string& drive) const
{
	if (tijprinter().files()) {
		return tijprinter().files()->getDrive(drive);
	}
	return nullptr;
}

const Directory* TijViewer::getPrinterFolder(const std::string& drive, const std::string& folder) const
{
	if (tijprinter().files()) {
		return tijprinter().files()->getDirectory(drive, folder);
	}
	return nullptr;
}

const File* TijViewer::getPrinterFile(const std::string& drive, const std::string& folder, const std::string& filename) const
{
	if (tijprinter().files()) {
		return tijprinter().files()->getFile(drive, folder, filename);
	}
	return nullptr;
}

const File* TijViewer::getPrinterFile(const std::string& filepath) const
{
	if (tijprinter().files()) {
		return tijprinter().files()->getFile(filepath);
	}
	return nullptr;
}


time_t TijViewer::printerDateTime() const
{
	return tijprinter().dateTime();
}

std::string TijViewer::printerType() const
{
	return tijprinter().type();
}

TijViewer::TijPrinterStatus TijViewer::printerStatus() const
{
	TijPrinterStatus status = TijPrinterStatus::DISCONNECTED;

	if (_controller.status() == NetworkNode::nNodeStatus::CONNECTED) {
		const TijPrinter& printer = tijprinter();
		const Macsa::Printers::Board * board = printer.board(0);
		if (board != nullptr) {
			if (board->enabled()) {
				if (board->errors().size()) {
					status = TijPrinterStatus::WARNING; // TODO: review
				}
				else {
					status = TijPrinterStatus::RUNNING;
					if (board->printing()) {
						status = TijPrinterStatus::PRINTING;
					}
				}
			}
			else {
				status = TijPrinterStatus::STOPPED;
			}
		}
	}
	else if (_controller.status() == NetworkNode::nNodeStatus::CONNECTING) {
		status = TijPrinterStatus::CONNECTING;
	}

	return status;
}

std::string TijViewer::printerControllerVersion() const
{
	return tijprinter().controllerVersion();
}

std::string TijViewer::printerApiVersion() const
{
	return tijprinter().apiVersion();
}

std::string TijViewer::printerFpgaVersion() const
{
	return tijprinter().fpgaVersion();
}

int TijViewer::printerId() const
{
	return tijprinter().id();
}

std::string TijViewer::printerCurrentMessage() const
{
	if (validBoard()) {
		return tijBoard().currentMessage();
	}
	return "";
}

uint8_t TijViewer::printerCurrentBCDCode() const
{
	if (validBoard()) {
		return tijBoard().currentBcdCode();
	}
	return 1;
}

BCDMode TijViewer::printerBCDMode() const
{
	if (validBoard()) {
		return tijBoard().bcdMode();
	}
	return BCDMode();
}

bool TijViewer::printerIsPrinting() const
{
	if (validBoard()) {
		return tijBoard().printing();
	}
	return false;
}

TijViewer::countersMap TijViewer::printerCounters() const
{
	if (validBoard()) {
		return tijBoard().counters();
	}
	return countersMap();
}

int TijViewer::printerCounter(const std::string &name) const
{
	if (validBoard()) {
		return tijBoard().counter(name);
	}
	return -1;
}

TijViewer::propertyMap TijViewer::printerStatusProperties() const
{
	if (validBoard()) {
		return tijBoard().statusProperties();
	}
	return 	propertyMap();
}

std::string TijViewer::printerStatusProperty(const std::string& name) const
{
	if (validBoard()) {
		return tijBoard().statusProperty(name);
	}
	return "";
}

bool TijViewer::printerAutoStart() const
{
	if (validBoard()) {
		return tijBoard().autoStart();
	}
	return false;
}

bool TijViewer::printerLowLevelOutput() const
{
	if (validBoard()) {
		return tijBoard().lowLevelOutput();
	}
	return false;
}

bool TijViewer::printerEnabled() const
{
	if (validBoard()) {
		return tijBoard().enabled();
	}
	return false;
}

bool TijViewer::printerBlocked() const
{
	if (validBoard()) {
		return tijBoard().blocked();
	}
	return false;
}

std::string TijViewer::userMessage() const
{
	if (validBoard()) {
		return tijBoard().userMessage();
	}
	return "";
}

bool TijViewer::printerPrintRotated() const
{
	if (validBoard()) {
		return tijBoard().printRotated();
	}
	return false;
}

PrinterDir TijViewer::printerPrintDirection() const
{
	if (validBoard()) {
		return tijBoard().printDirection();
	}
	return PrinterDir();
}

NozzlesCol TijViewer::printerNozzlesCol() const
{
	if (validBoard()) {
		return tijBoard().nozzlesCol();
	}
	return NozzlesCol();
}

Photocell TijViewer::printerPhotocell() const
{
	if (validBoard()) {
		return tijBoard().photocell();
	}
	return Photocell();
}

EncoderMode TijViewer::printerEncoderMode() const
{
	if (validBoard()) {
		return tijBoard().encoder().mode();
	}
	return EncoderMode();
}

double TijViewer::printerEncoderFixedSpeed() const
{
	if (validBoard()) {
		return tijBoard().encoder().fixedSpeed();
	}
	return 0;
}

double TijViewer::printerEncoderResolution() const
{
	if (validBoard()) {
		return tijBoard().encoder().resolution();
	}
	return 0;
}

double TijViewer::printerEncoderDiameter() const
{
	if (validBoard()) {
		return tijBoard().encoder().diameter();
	}
	return 0;
}

ShotMode TijViewer::printerShotMode() const
{
	if (validBoard()) {
		return tijBoard().shotMode();
	}
	return ShotMode();
}

BCDTable TijViewer::printerBCDTable() const
{
	if (validBoard()) {
		return tijBoard().bcdTable();
	}
	return BCDTable();
}

Cartridge TijViewer::printerCartridgeSettings() const
{
	if (validBoard()) {
		return tijBoard().cartridge();
	}
	return Cartridge();
}

TijViewer::propertyMap TijViewer::printerConfigurationProperties() const
{
	if (validBoard()) {
		return tijBoard().configurationProperties();
	}
	return propertyMap();
}

std::string TijViewer::printerConfigurationProperty(const std::string &name) const
{
	if (validBoard()) {
		return tijBoard().configurationProperty(name);
	}
	return "";
}

DateCodes TijViewer::printerDateCodes() const
{
	return tijprinter().dateCodes();
}

std::vector<Input> TijViewer::printerInputs() const
{
	if (validBoard()) {
		return tijBoard().inputs();
	}
	return std::vector<Input>();
}

Input TijViewer::printerInput(unsigned int idx) const
{
	if (validBoard()) {
		return tijBoard().input(idx);
	}
	return Input(0);
}

std::vector<Output> TijViewer::printerOutputs() const
{
	if (validBoard()) {
		return tijBoard().outputs();
	}
	return std::vector<Output>();
}

Output TijViewer::printerOutput(unsigned int idx) const
{
	if (validBoard()) {
		return tijBoard().output(idx);
	}
	return Output(0);
}

std::vector<Error> TijViewer::printerErrors() const
{
	if (validBoard()) {
		return tijBoard().errors();
	}
	return std::vector<Error>();
}

Error TijViewer::printerError(unsigned int idx) const
{
	if (validBoard()) {
		return tijBoard().error(idx);
	}
	return Error();
}
std::vector<Error> TijViewer::printerErrorsLog() const
{
	return tijprinter().errorsLog();
}

bool TijViewer::printerLogsEnabled() const
{
	return tijprinter().logsEnabled();
}

bool TijViewer::printerLogComsEnabled() const
{
	return tijprinter().logComsEnabled();
}

LoggerLevel TijViewer::printerLoggerLevel() const
{
	return tijprinter().loggerLevel();
}

//Node Observer callbacks
void TijViewer::statusChanged(){}
void TijViewer::ioStatusChanged(){}
void TijViewer::configChanged(){}
void TijViewer::filesListChanged(){}
void TijViewer::fontsChanged(){}
void TijViewer::userValuesChanged(){}
void TijViewer::errorsLogsChanged(){}
void TijViewer::fileChanged(const std::string& /*unit*/, const std::string& /*filepath*/) {}

//Node Observer callbacks
void TijViewer::nodeStatusChanged(const NetworkNode::nNodeStatus& status)
{
	if (status == NetworkNode::DISCONNECTED) {
		_controller.disconnect();
	}
}
void TijViewer::nodeTimeout()
{}

