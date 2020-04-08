#include "viewers/jetviewercontroller.h"
#include "jet/jetmonitor.h"
#include <QDateTime>
#include <QVector>
#include "printer/board.h"

#include <iostream> //Debug

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Printers;

JetViewerController::JetViewerController(JetController &controller, QObject *parent) :
	QObject(parent),
	JetViewer(controller),
	_controller(controller)
{}

/******************   Status commands   ******************/
bool JetViewerController::getCounters()
{
	return _controller.getCounters();
}

bool JetViewerController::getSSCC()
{
	return _controller.getSSCC();
}

bool JetViewerController::getStatus()
{
	return _controller.getStatus();
}

bool JetViewerController::getDateTime()
{
	return _controller.getDateTime();
}

bool JetViewerController::getPrinterLogs(time_t from, time_t to, JetLogType type)
{
	return _controller.getPrinterLogs(from, to, type);
}

bool JetViewerController::getPause()
{
	return _controller.getPause();
}

bool JetViewerController::setCounters(const QMap<unsigned int, unsigned int> &counters)
{
	std::map<unsigned int, unsigned int> map;

	for (QMap<unsigned int, unsigned int>::const_iterator val = counters.begin(); val != counters.end(); val++) {
		map.insert(std::pair<unsigned int, unsigned int>(val.key(), val.value()));
	}

	return _controller.setCounters(map);
}

bool JetViewerController::resetCounters()
{
	return _controller.resetCounters();
}

/******************   Files commands   ******************/
bool JetViewerController::requestUSBMessages()
{
	return _controller.getUSBMessages();
}

bool JetViewerController::requestFiles()
{
	return _controller.getFiles();
}

bool JetViewerController::requestVersions()
{
	return _controller.getVersions();
}

bool JetViewerController::requestFonts()
{
	return _controller.getFonts();
}
/******************   Messages commands   ******************/
bool JetViewerController::setCurrentMessage(unsigned int messageNumber)
{
	return _controller.setCurrentMessage(messageNumber);
}

bool JetViewerController::sendMessage(const Message &message, const std::vector<char> &content, bool raw)
{
	return _controller.sendMessage(message, content, raw);
}

bool JetViewerController::resetMessagesGroup()
{
	return _controller.resetMessagesGroup();
}

bool JetViewerController::getMessagesGroup(const QString &group)
{
	return _controller.getMessagesGroup(_(group));
}

bool JetViewerController::createMessageGroup(const QString &group)
{
	return _controller.createMessageGroup(_(group));
}

bool JetViewerController::sendMessageGroup(const QString &group, const Message &message, const std::vector<char> &content, bool raw)
{
	return _controller.sendMessageGroup(_(group), message, content, raw);
}

bool JetViewerController::deleteMessageGroup(const QString &group)
{
	return _controller.deleteMessageGroup(_(group));
}

bool JetViewerController::setMessageVariable(unsigned int filenum, const QString &variable, const QString &value)
{
	return _controller.setMessageVariable(filenum, _(variable), _(value));
}

bool JetViewerController::setMessageVariables(unsigned int filenum, const QMap<QString, QString> &values)
{
	std::map<std::string, std::string> map;

	for (QMap<QString, QString>::const_iterator val = values.begin(); val != values.end(); val++) {
		map.insert(std::pair<std::string, std::string>(_(val.key()), _(val.value())));
	}

	return _controller.setMessageVariables(filenum, map);
}

bool JetViewerController::getUserInputs(unsigned int filenum, const QString &group)
{
	return _controller.getUserInputs(filenum, _(group));
}

bool JetViewerController::setUserInputs(unsigned int filenum, const QMap<QString, QString> &uiFields, const QString &group)
{
	std::map<std::string, std::string> map;

	for (QMap<QString, QString>::const_iterator val = uiFields.begin(); val != uiFields.end(); val++) {
		map.insert(std::pair<std::string, std::string>(_(val.key()), _(val.value())));
	}

	return _controller.setUserInputs(filenum, map, _(group));
}

/******************   Config commands   ******************/
bool JetViewerController::setPause(bool pause)
{
	return _controller.setPause(pause);
}

bool JetViewerController::incrementSSCC()
{
	return _controller.incrementSSCC();
}

bool JetViewerController::setDateTime(const time_t &datetime)
{
	return _controller.setDateTime(datetime);
}

bool JetViewerController::setOutput(const JetIO &output)
{
	return _controller.setOutput(output);
}

bool JetViewerController::setPrintDirection(PrintDirection dir)
{
	return _controller.setPrintDirection(dir);
}

bool JetViewerController::setPrintBitmapInverted(bool inverted)
{
	return _controller.setPrintBitmapInverted(inverted);
}

bool JetViewerController::setPrintheadMode(PHEnableMode mode)
{
	return _controller.setPrintheadEnabled(mode);
}

bool JetViewerController::setPrintSpeed(unsigned int speed)
{
	return _controller.setPrintSpeed(speed);
}

bool JetViewerController::setPrintDelay(unsigned int delay)
{
	return _controller.setPrintDelay(delay);
}

bool JetViewerController::setHorizontalResolution(unsigned int resolution)
{
	return _controller.setHorizontalResolution(resolution);
}

bool JetViewerController::setConfig(JetPrinter &printer)
{
	return _controller.setConfig(printer);
}

bool JetViewerController::getPrintSpeed()
{
	return _controller.getPrintSpeed();
}

bool JetViewerController::getPrintDelay()
{
	return _controller.getPrintDelay();
}

bool JetViewerController::getHorizontalResolution()
{
	return _controller.getHorizontalResolution();
}

bool JetViewerController::getConfig()
{
	return _controller.getConfig();
}

bool JetViewerController::resetInkAlarm()
{
	return _controller.resetInkAlarm();
}

bool JetViewerController::getNisXMessage(unsigned int msgNum)
{
	return _controller.getNisXMessage(msgNum);
}

bool JetViewerController::setNisXElement(const QString &filename, const QString &content)
{
	return _controller.setNisXElement(_(filename), _(content));
}


/**********************************************************************/
JetPrinter *JetViewerController::jetPrinter() const
{
	JetPrinter* jet = nullptr;
	if (_controller.status() == Network::NetworkNode::CONNECTED) {
		jet = dynamic_cast<JetPrinter*>(_controller.printer());
	}
	return jet;
}
