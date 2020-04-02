#include "viewers/tijviewercontroller.h"
#include "tij/tijmonitor.h"
#include <QDateTime>
#include <QVector>
#include "printer/board.h"

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Printers;

TIJViewerController::TIJViewerController(TijController &controller, QObject *parent) :
	QObject(parent),
	TijViewer(controller),
	_controller(controller)
{}

#include <iostream>

bool TIJViewerController::requestLive() {
	_controller.getLive();
	return true;
}

bool TIJViewerController::requestStatus()
{
	return _controller.updateStatus();
}

bool TIJViewerController::requestConfig()
{
	return _controller.updateConfig();
}

bool TIJViewerController::requestErrorsList()
{
	return _controller.updateErrorsList();
}

bool TIJViewerController::requestAllFiles()
{
	return _controller.updateFilesList();
}

bool TIJViewerController::requestFontFiles()
{
	return _controller.updateFontsList();
}

bool TIJViewerController::requestMessagesFiles()
{
	return _controller.updateMessagesList();
}

bool TIJViewerController::requestImagesFiles()
{
	return _controller.updateImagesList();
}

bool TIJViewerController::requestFileContent(const std::string &filepath, bool rawMode)
{
	return (_controller.updateFile(filepath, rawMode));
}

std::vector<uint8_t> TIJViewerController::getFileContent(const std::string &filepath)
{
	return _controller.getFile(filepath);
}

QString TIJViewerController::printerDateTime(const QString& format)
{
	TijPrinter* tij = dynamic_cast<TijPrinter*>(_controller.printer());
	if (tij){
		time_t time = tij->dateTime();
		QDateTime dt = QDateTime::fromTime_t(static_cast<uint32_t>(time));
		if (format.length()){
			return dt.toString(format);
		}
		else{
			return dt.toString(Qt::SystemLocaleShortDate);
		}
	}
	return "";
}

QVector<TIJViewerController::PrinterError> TIJViewerController::errorsLog() const
{
	QVector<PrinterError> values;
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		std::vector<Error> errors = tij->errorsLog();
		for (std::vector<Error>::const_iterator it = errors.begin(); it != errors.end(); it++) {
			PrinterError err;
			err.boardId = (*it).boardId();
			err.timestamp = QDateTime::fromTime_t(static_cast<uint>((*it).timestamp()));
			err.code = _((*it).code().toString());
			err.type = _((*it).type().toString());
			err.priority = (*it).priority();
			values.push_back(err);
		}
	}
	return values;
}

TIJViewerController::NetworkIface TIJViewerController::networkIface(int index) const
{
	NetworkIface iface;
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		const TijComms * comms = dynamic_cast<const TijComms*>(tij->comms());
		if (comms) {
			const Ethernet * eth = comms->ethernetIface(index);
			if (eth) {
				iface.dhcp = eth->dhcp();
				iface.address = _(eth->address());
				iface.netmask = _(eth->netmask());
				iface.gateway = _(eth->gateway());
				iface.hwAddress = _(eth->macAddress());
				iface.iface = _(eth->hostname());
				iface.port = eth->tcpPort();
			}
		}
	}
	return iface;
}

TIJViewerController::BluetoothDevice TIJViewerController::bluetooth() const
{
	BluetoothDevice bDev;
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		const TijComms * comms = dynamic_cast<const TijComms*>(tij->comms());
		if (comms) {
			const BlueTooth * ble = comms->bluetooth();
			if (ble) {
				bDev.name = _(ble->name());
				bDev.pass = _(ble->pass());
				bDev.visible = ble->visible();
			}
		}
	}
	return bDev;

}

QString TIJViewerController::loggerLevelStr() const
{
	std::string value = "---";
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->loggerLevel().toString();
	}

	return _(value);
}

LoggerLevel TIJViewerController::loggerLevel() const
{
	LoggerLevel value;
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->loggerLevel();
	}

	return value;
}

bool TIJViewerController::traceComms() const
{
	bool value = false;
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->logComsEnabled();
	}

	return value;
}

bool TIJViewerController::loggerEnabled() const
{
	bool value = false;
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->logsEnabled();
	}

	return value;
}

QString TIJViewerController::boardType() const
{
	std::string value = (printerType().length() ? printerType() : "---");
	return _(value);
}

QString TIJViewerController::boardControllerVersion() const
{
	std::string value = "---";
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->controllerVersion();
	}
	return _(value);
}

QString TIJViewerController::boardFPGAVersion() const
{
	std::string value = "---";
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->fpgaVersion();
	}
	return _(value);
}

QString TIJViewerController::boardAPIVersion() const
{
	std::string value = "---";
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->apiVersion();
	}
	return _(value);
}

bool TIJViewerController::autoStart() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->autoStart();
	}
	return value;
}

bool TIJViewerController::setAutoStart(bool autoStart)
{
	return (_controller.setAutoStart(autoStart) == Printers::SUCCESS);
}

bool TIJViewerController::lowLevelOutput() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->lowLevelOutput();
	}
	return value;
}

bool TIJViewerController::setLowLevelOutput(bool lowLevelOutput)
{
	return(_controller.setLowLevelOutput(lowLevelOutput) == Printers::SUCCESS);
}

bool TIJViewerController::printing() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->printing();
	}
	return value;
}

bool TIJViewerController::enabled() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->enabled();
	}
	return value;
}

bool TIJViewerController::setEnabled(bool enabled)
{
	return (_controller.setEnabled(enabled) == Printers::SUCCESS);
}

bool TIJViewerController::blocked() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->blocked();
	}
	return value;
}

bool TIJViewerController::setBlocked(bool blocked)
{
	return (_controller.setCartridgeBlocked(blocked) == Printers::SUCCESS);
}

QString TIJViewerController::currentMessage() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->currentMessage();
	}
	return _(value);
}

QString TIJViewerController::userMessage() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->userMessage();
	}
	return _(value);
}

QMap<int, QString> TIJViewerController::bcdTable() const
{
	QMap<int, QString> bcdTable;
	const Board* board = tijPrinterBoard();
	if (board) {
		BCDTable table = board->bcdTable();
		for (unsigned int code = 0; code < table.size(); code++) {
			bcdTable.insert(static_cast<int>(code), _(table.at(code)));
		}
	}
	return bcdTable;
}

BCDMode TIJViewerController::bcdMode() const
{
	BCDMode value;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->bcdMode();
	}
	return value;
}

QString TIJViewerController::bcdModeStr() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->bcdMode().toString();
	}
	return _(value);
}

uint8_t TIJViewerController::currentBcdCode() const
{
	uint8_t value = 0;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->currentBcdCode();
	}
	return value;
}

QString TIJViewerController::printDirectionStr() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->printDirection().toString();
	}
	return _(value);
}

PrinterDir TIJViewerController::printDirection() const
{
	PrinterDir value;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->printDirection();
	}
	return value;
}

bool TIJViewerController::printRotated() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->printRotated();
	}
	return value;
}

bool TIJViewerController::setPrintRotated(bool printRotated)
{
	return (_controller.setPrintRotated(printRotated) == Printers::SUCCESS);
}

QString TIJViewerController::nozzlesColStr() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->nozzlesCol().toString();
	}
	return _(value);
}

NozzlesCol TIJViewerController::nozzlesCol() const
{
	NozzlesCol value;
	value = nNozzlesCol::COL_A;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->nozzlesCol();
	}
	return value;
}

ShootingMode TIJViewerController::shotMode() const
{
	ShootingMode value;
	value = nShootingMode::SINGLE_SHOT;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->shotMode().mode();
	}
	return value;
}

QString TIJViewerController::shotModeStr() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->shotMode().mode().toString();
	}
	return _(value);
}

uint16_t TIJViewerController::shotModeNumPrints() const
{
	uint16_t value = 0;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->shotMode().numPrints();
	}
	return value;
}

QVector<uint> TIJViewerController::shotModeDelays() const
{
	QVector<uint> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		std::vector<Delay> delays = board->shotMode().delays();
		for (uint32_t i = 0; i < delays.size(); i++) {
			values.push_back(delays.at(i).delay());
		}
	}
	return values;
}

bool TIJViewerController::shotModeRepeat() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->shotMode().repeat();
	}
	return value;
}

QString TIJViewerController::encoderModeStr() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->encoder().mode().toString();
	}
	return _(value);

}

EncoderMode TIJViewerController::encoderMode() const
{
	EncoderMode value;
	value = nEncoderMode::FIXED_SPEED;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->encoder().mode();
	}
	return value;
}

double TIJViewerController::encoderFixedSpeed() const
{
	double value = 0.0;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->encoder().fixedSpeed();
	}
	return value;
}

double TIJViewerController::encoderResolution() const
{
	double value = 0.0;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->encoder().resolution();
	}
	return value;

}

double TIJViewerController::encoderDiameter() const
{
	double value = 0.0;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->encoder().diameter();
	}
	return value;
}

QString TIJViewerController::photocellStr() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->photocell().toString();
	}
	return _(value);
}

Photocell TIJViewerController::photocell() const
{
	Macsa::Printers::Photocell value;
	value = Macsa::Printers::nPhotocell::PHCELL_A;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->photocell();
	}
	return value;

}

QMap<QString, int> TIJViewerController::counters() const
{
	QMap<QString, int> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		Board::countersMap counters = board->counters();
		for (Board::countersMap::const_iterator c = counters.begin(); c != counters.end(); c++) {
			values.insert(_(c->first), c->second);
		}
	}
	return values;
}

int TIJViewerController::counter(const QString &name) const
{
	int value = 0;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->counter(name.toStdString());
	}
	return value;

}

QMap<QString, QString> TIJViewerController::statusProperties() const
{
	QMap<QString, QString> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		Board::propertyMap properties = board->statusProperties();
		for (Board::propertyMap::const_iterator p = properties.begin(); p != properties.end(); p++) {
			values.insert(_(p->first), _(p->second));
		}
	}
	return values;
}

QString TIJViewerController::statusProperty(const QString &name) const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->statusProperty(name.toStdString());
	}
	return _(value);
}

QMap<QString, QString> TIJViewerController::configProperties() const
{
	QMap<QString, QString> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		Board::propertyMap properties = board->configurationProperties();
		for (Board::propertyMap::const_iterator p = properties.begin(); p != properties.end(); p++) {
			values.insert(_(p->first), _(p->second));
		}
	}
	return values;
}

QString TIJViewerController::configProperty(const QString &name) const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->configurationProperty(name.toStdString());
	}
	return _(value);

}

QString TIJViewerController::configProperty(const TIJConfigProperties &param) const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		std::string key = "";
		switch (param) {
			case TIJConfigProperties::HEADER_TYPE:					key = "HeaderType";					break;
			case TIJConfigProperties::SHUTTER_ENABLED:				key = "SHUTTER.ENABLED";			break;
			case TIJConfigProperties::SHUTTER_TIME:					key = "SHUTTER.TIME";				break;
			case TIJConfigProperties::HRES:							key = "HRES";						break;
			case TIJConfigProperties::PRINTMODE:					key = "PRINTMODE";					break;
			case TIJConfigProperties::PRINTMODE_INTENSITY:			key = "PRINTMODE.INTENSITY";		break;
			case TIJConfigProperties::PRINTMODE_RESOLUTION_MODE:	key = "PRINTMODE.RESOLUTION.MODE";	break;
			case TIJConfigProperties::PRINTMODE_RESOLUTION_PH:		key = "PRINTMODE.RESOLUTION.PH";	break;
		}

		value = board->configurationProperty(key);
	}
	return _(value);
}

bool TIJViewerController::cartridgeAutoSetup() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->cartridge().autoconfig();
	}
	return value;
}

double TIJViewerController::cartridgeFiringVoltage() const
{
	double value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->cartridge().voltage();
	}
	return value;
}

double TIJViewerController::cartridgePulseWidth() const
{
	double value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->cartridge().pulseWidth();
	}
	return value;
}

bool TIJViewerController::cartridgePulseWarming() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->cartridge().pulseWarming();
	}
	return value;
}

double TIJViewerController::cartridgePulseWarmTemp() const
{
	double value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->cartridge().pulseWarmingTemp();
	}
	return value;
}

double TIJViewerController::cartridgeAdjustedCapacity() const
{
	double value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->cartridge().adjustedCapacity();
	}
	return value;
}

QVector<TIJViewerController::PrinterInput> TIJViewerController::inputs() const
{
	QVector<PrinterInput> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		std::vector<Input> inputs = board->inputs();
		for (std::vector<Input>::const_iterator it = inputs.begin(); it != inputs.end(); it++) {
			values.push_back(printerInputToView((*it)));
		}
	}
	return values;
}

TIJViewerController::PrinterInput TIJViewerController::input(unsigned int idx) const
{
	PrinterInput value;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = printerInputToView(board->input(idx));
	}
	return value;
}

QVector<TIJViewerController::PrinterOutput> TIJViewerController::outputs() const
{
	QVector<PrinterOutput> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		std::vector<Output> outputs = board->outputs();
		for (std::vector<Output>::const_iterator it = outputs.begin(); it != outputs.end(); it++) {
			values.push_back(printerOutputToView((*it)));
		}
	}
	return values;

}

TIJViewerController::PrinterOutput TIJViewerController::output(unsigned int idx) const
{
	PrinterOutput value;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = printerOutputToView(board->output(idx));
	}
	return value;
}

DateCodes TIJViewerController::dateCodes() const
{
	const TijPrinter* tij = tijPrinter();
	if (tij) {
		return tij->dateCodes();
	}
	return DateCodes();
}


/**********************************************************************/
TijPrinter *TIJViewerController::tijPrinter() const
{
	TijPrinter* tij = nullptr;
	if (_controller.status() == Network::NetworkNode::CONNECTED) {
		tij = dynamic_cast<TijPrinter*>(_controller.printer());
	}
	return tij;
}

const Board *TIJViewerController::tijPrinterBoard() const
{
	const Board * board = nullptr;
	TijPrinter* tij = tijPrinter();
	if (tij) {
		board = tij->board(0);
	}
	return board;
}

TIJViewerController::PrinterInput TIJViewerController::printerInputToView(Input in) const
{
	PrinterInput pIn;
	pIn.id = static_cast<int>(in.id());
	pIn.descriptor = _(in.descriptor());
	pIn.mode = _(in.mode().toString());
	pIn.inverted = in.inverted();
	pIn.filter = in.filter();
	pIn.value = in.value();

	return pIn;
}

TIJViewerController::PrinterOutput TIJViewerController::printerOutputToView(Output out) const
{
	PrinterOutput pOut;
	pOut.id = static_cast<int>(out.id());
	pOut.descriptor = _(out.descriptor());
	pOut.initialValue = out.initialValue();
	pOut.type = _(out.type().toString());
	pOut.time = out.time();
	pOut.value = out.value();

	return pOut;
}

