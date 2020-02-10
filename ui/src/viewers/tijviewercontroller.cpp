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
				return _controller.updateFiles() == ErrorCode_n::SUCCESS;
		case TIJDataDescriptors::MESSAGES_FILES:
			return _controller.updateMessages() == ErrorCode_n::SUCCESS;
		case TIJDataDescriptors::FONTS_FILES:
			return _controller.updateFonts() == ErrorCode_n::SUCCESS;
		case TIJDataDescriptors::IMAGES_FILES:
				return _controller.updateImages() == ErrorCode_n::SUCCESS;
		case TIJDataDescriptors::PRINTER_ID:
				return _controller.id().c_str();
		case TIJDataDescriptors::PRINTER_ADDRS:
				return _controller.address().c_str();
		case TIJDataDescriptors::PRINTER_STATUS:
				return static_cast<int>(_controller.printerStatus());
		case TIJDataDescriptors::PRINTER_DT:
			{
				TIJPrinter* tij = dynamic_cast<TIJPrinter*>(_controller.printer());
				if (tij){
					time_t time = tij->dateTime();
					QDateTime dt = QDateTime::fromTime_t(static_cast<uint32_t>(time));
					return dt.toString();
				}
				return "";
			}
		default:
			return QVariant();
	}
}

bool TIJViewerController::setData(int /*descriptor*/, const QVariant &/*value*/)
{
	return false;
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

bool TIJViewerController::requestFileContent(const std::string &filepath, bool rawMode)
{
	return (_controller.updateFile(filepath, rawMode) == ErrorCode_n::SUCCESS);
}

std::vector<uint8_t> TIJViewerController::getFileContent(const std::string &filepath)
{
	return _controller.getFile(filepath);
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

	return value.c_str();
}

QString TIJViewerController::boardControllerVersion() const
{
	std::string value = "---";
	const TIJPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->controllerVersion();
	}
	return value.c_str();
}

QString TIJViewerController::boardFPGAVersion() const
{
	std::string value = "---";
	const TIJPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->fpgaVersion();
	}
	return value.c_str();
}

QString TIJViewerController::boardAPIVersion() const
{
	std::string value = "---";
	const TIJPrinter* tij = tijPrinter();
	if (tij) {
		value = tij->apiVersion();
	}
	return value.c_str();
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

bool TIJViewerController::lowLevelOutput() const
{
	bool value = false;
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->lowLevelOutput();
	}
	return value;
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

void TIJViewerController::setEnabled(bool enabled)
{
	 _controller.setEnabled(enabled);
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

QString TIJViewerController::currentMessage() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->currentMessage();
	}
	return value.c_str();
}

QString TIJViewerController::userMessage() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->userMessage();
	}
	return value.c_str();
}

QMap<int, QString> TIJViewerController::bcdTable() const
{
	QMap<int, QString> bcdTable;
	const Board* board = tijPrinterBoard();
	if (board) {
		BCDTable table = board->bcdTable();
		for (unsigned int code = 0; code < table.size(); code++) {
			bcdTable.insert(static_cast<int>(code), table.at(code).c_str());
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
	return value.c_str();
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
	return value.c_str();
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

QString TIJViewerController::nozzlesCol() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->nozzlesCol().toString();
	}
	return value.c_str();
}

QString TIJViewerController::shotMode() const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->shotMode().mode().toString();
	}
	return value.c_str();
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
	return value.c_str();

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
	return value.c_str();
}

QMap<QString, int> TIJViewerController::counters() const
{
	QMap<QString, int> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		Board::countersMap counters = board->counters();
		for (Board::countersMap::const_iterator c = counters.begin(); c != counters.end(); c++) {
			values.insert(c->first.c_str(), c->second);
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

QMap<QString, QString> TIJViewerController::properties() const
{
	QMap<QString, QString> values;
	const Board* board = tijPrinterBoard();
	if (board) {
		Board::propertyMap propertirs = board->properties();
		for (Board::propertyMap::const_iterator p = propertirs.begin(); p != propertirs.end(); p++) {
			values.insert(p->first.c_str(), p->second.c_str());
		}
	}
	return values;
}

QString TIJViewerController::property(const QString &name) const
{
	std::string value = "---";
	const Board* board = tijPrinterBoard();
	if (board) {
		value = board->property(name.toStdString());
	}
	return value.c_str();
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
			err.code = (*it).code().toString().c_str();
			err.type = (*it).type().toString().c_str();
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
		value.code = perror.code().toString().c_str();
		value.type = perror.type().toString().c_str();
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
	pIn.descriptor = in.descriptor().c_str();
	pIn.mode = in.mode().toString().c_str();
	pIn.inverted = in.inverted();
	pIn.filter = in.filter();
	pIn.value = in.value();

	return pIn;
}

TIJViewerController::PrinterOutput TIJViewerController::printerOutputToView(Output out) const
{
	PrinterOutput pOut;
	pOut.id = static_cast<int>(out.id());
	pOut.descriptor = out.descriptor().c_str();
	pOut.initialValue = out.initialValue();
	pOut.type = out.type().toString().c_str();
	pOut.time = out.time();
	pOut.value = out.value();

	return pOut;
}

