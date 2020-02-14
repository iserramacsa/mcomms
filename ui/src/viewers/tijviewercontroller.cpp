#include "viewers/tijviewercontroller.h"
#include <QDateTime>
#include <QVector>
#include "printer/board.h"

using namespace Macsa;
using namespace Macsa::Printers;

TIJViewerController::TIJViewerController(TIJPrinterController &controller) :
	_controller(controller)
{

}

QVariant TIJViewerController::data(int descriptor)
{
	switch (static_cast<TIJDataDescriptors>(descriptor))
	{
		case TIJDataDescriptors::LIVE:
			return requestLive();
		case TIJDataDescriptors::STATUS:
			return requestStatus();
		case TIJDataDescriptors::CONFIG:
			return requestConfig();
		case TIJDataDescriptors::ALL_FILES:
			return  requestAllFiles();
		case TIJDataDescriptors::MESSAGES_FILES:
			return requestMessagesFiles();
		case TIJDataDescriptors::FONTS_FILES:
			return requestFontFiles();
		case TIJDataDescriptors::IMAGES_FILES:
			return requestImagesFiles();
		case TIJDataDescriptors::PRINTER_ID:
			return _(_controller.id());
		case TIJDataDescriptors::PRINTER_ADDRS:
			return _(_controller.address());
		case TIJDataDescriptors::PRINTER_STATUS:
			return static_cast<int>(_controller.printerStatus());
		case TIJDataDescriptors::PRINTER_DT:
			return printerDateTime();
	}
	return QVariant();
}

bool TIJViewerController::setData(int /*descriptor*/, const QVariant &/*value*/)
{
	return false;
}

#include <iostream>
void TIJViewerController::updatePrinterData()
{
	if (_controller.getLive() == ErrorCode_n::SUCCESS) {
		if (_controller.statusChanged())
			_controller.updateStatus();

		if (_controller.configChanged())
			_controller.updateConfig();

		if (_controller.filesChanged())
			_controller.updateFilesList();

		if (_controller.fontsChanged())
			_controller.updateFontsList();

		if (_controller.userValuesChanged())
			std::cout << "Printer user values changed!" << std::endl;
//			_controller.updateUserValues();

		if (_controller.errorsLogsChanged())
			_controller.updateErrorsList();

		if (_controller.isInError())
			std::cout << "Printer is in error!" << std::endl;
	}
}

bool TIJViewerController::requestLive()
{
	return _controller.getLive() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestStatus()
{
	return _controller.updateStatus() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestConfig()
{
	return _controller.updateConfig() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestErrorsList()
{
	return _controller.updateErrorsList() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestAllFiles()
{
	return _controller.updateFilesList() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestFontFiles()
{
	return _controller.updateFontsList() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestMessagesFiles()
{
	return _controller.updateMessagesList() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestImagesFiles()
{
	return _controller.updateImagesList() == ErrorCode_n::SUCCESS;
}

bool TIJViewerController::requestFileContent(const std::string &filepath, bool rawMode)
{
	return (_controller.updateFile(filepath, rawMode) == ErrorCode_n::SUCCESS);
}

std::vector<uint8_t> TIJViewerController::getFileContent(const std::string &filepath)
{
	return _controller.getFile(filepath);
}

QString TIJViewerController::printerDateTime(const QString& format)
{
	TIJPrinter* tij = dynamic_cast<TIJPrinter*>(_controller.printer());
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
	const TIJPrinter* tij = tijPrinter();
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
	const TIJPrinter* tij = tijPrinter();
	if (tij) {
		const TIJComms * comms = dynamic_cast<const TIJComms*>(tij->comms());
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
	const TIJPrinter* tij = tijPrinter();
	if (tij) {
		const TIJComms * comms = dynamic_cast<const TIJComms*>(tij->comms());
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

TIJViewerController::TIJStatus TIJViewerController::printerStatus() const
{
	return _controller.printerStatus();
}

QString TIJViewerController::boardType() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->type();
	}

	return _(value);
}

QString TIJViewerController::boardControllerVersion() const
{
	std::string value = "---";
	const TIJPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->controllerVersion();
	}
	return _(value);
}

QString TIJViewerController::boardFPGAVersion() const
{
	std::string value = "---";
	const TIJPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->fpgaVersion();
	}
	return _(value);
}

QString TIJViewerController::boardAPIVersion() const
{
	std::string value = "---";
	const TIJPrinter* tij = tijPrinter();
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

QString TIJViewerController::bcdMode() const
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

QString TIJViewerController::printDirection() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->printDirection().toString();
	}
	return _(value);
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

QString TIJViewerController::nozzlesCol() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->nozzlesCol().toString();
	}
	return _(value);
}

QString TIJViewerController::shotMode() const
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

QString TIJViewerController::encoderMode() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->encoder().mode().toString();
	}
	return _(value);

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

QString TIJViewerController::photocell() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->photocell().toString();
	}
	return _(value);
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
		value = board->configurationProperty(name.toStdString());
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
		value = board->statusProperty(name.toStdString());
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

QVector<TIJViewerController::PrinterError> TIJViewerController::errors() const
{
	QVector<PrinterError> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		std::vector<Error> errors = board->errors();
		for (std::vector<Error>::const_iterator it = errors.begin(); it != errors.end(); it++) {
			PrinterError err;
			err.timestamp = QDateTime::fromTime_t(static_cast<uint>((*it).timestamp()));
			err.code = _((*it).code().toString());
			err.type = _((*it).type().toString());
			err.priority = (*it).priority();
			values.push_back(err);
		}
	}
	return values;
}

TIJViewerController::PrinterError TIJViewerController::error(unsigned int idx) const
{
	PrinterError value;
	const Board* board = tijPrinterBoard();
	if (board) {
		Error perror = board->error(idx);
		value.timestamp = QDateTime::fromTime_t(static_cast<uint>(perror.timestamp()));
		value.code = _(perror.code().toString());
		value.type = _(perror.type().toString());
		value.priority = perror.priority();
	}
	return value;
}


/**********************************************************************/
TIJPrinter *TIJViewerController::tijPrinter() const
{
	TIJPrinter* tij = nullptr;
	if (_controller.status() == Network::NetworkNode::CONNECTED) {
		tij = dynamic_cast<TIJPrinter*>(_controller.printer());
	}
	return tij;
}

const Board *TIJViewerController::tijPrinterBoard() const
{
	const Board * board = nullptr;
	TIJPrinter* tij = tijPrinter();
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

