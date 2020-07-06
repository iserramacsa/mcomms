#include "jet/jetviewer.h"

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Network;
using namespace Macsa::Printers;

JetViewer::JetViewer(JetController &controller) :
	JetObserver(&controller),
	Network::NodeObserver(&controller),
	_controller(controller)
{}

JetViewer::~JetViewer()
{}

/**************** Printer Files getters ****************/
std::vector<std::string> JetViewer::printerDrives() const
{
	std::vector<std::string> drives;
	if (jetPrinter().files()) {
		drives = jetPrinter().files()->getDrives();
	}
	return drives;
}

const Printers::Drive *JetViewer::printerDrive(const std::string &drive) const
{
	const Printers::Drive * d = nullptr;
	if (jetPrinter().files()) {
		d = jetPrinter().files()->getDrive(drive);
	}
	return d;
}


std::vector<std::string> JetViewer::printerDirectories(const std::string &drive) const
{
	std::vector<std::string> directories;
	if (jetPrinter().files()) {
		directories = jetPrinter().files()->getDirectories(drive);
	}
	return directories;
}

std::vector<std::string> JetViewer::printerSubdirectories(const std::string &drive, const std::string &directory) const
{
	std::vector<std::string> subdirectories;
	if (jetPrinter().files()) {
		const Printers::Directory* dir = jetPrinter().files()->getDirectory(drive, directory);
		if (dir){
			subdirectories = dir->getSubdirectoriesList();
		}
	}
	return subdirectories;
}

const Printers::Directory *JetViewer::printerDirectory(const std::string &drive, const std::string &directory) const
{
	const Printers::Directory *	dir = nullptr;
	if (jetPrinter().files()) {
		dir = jetPrinter().files()->getDirectory(drive, directory);
	}
	return dir;
}

std::vector<std::string> JetViewer::printerFiles(const std::string &drive, const std::string &directory) const
{
	std::vector<std::string> files;
	if (jetPrinter().files()) {
		files = jetPrinter().files()->getFiles(drive, directory);
	}
	return files;
}

const Printers::File *JetViewer::printerFile(const std::string path) const
{
	const Printers::File* file = nullptr;
	if (jetPrinter().files()) {
		file = jetPrinter().files()->getFile(path);
	}
	return file;
}

const JetEthernet *JetViewer::printerEthernetIface(const std::string &iface) const
{
	return static_cast<const Printers::JetComms*>(jetPrinter().comms())->ethernetIface(iface);
}

std::vector<std::string> JetViewer::printerEthernetIfaces() const
{
	return static_cast<const Printers::JetComms*>(jetPrinter().comms())->ifaces();
}

/**************** Printer base getters ****************/
time_t JetViewer::dateTime() const
{
	return jetPrinter().dateTime();
}

std::string JetViewer::printerType() const
{
	return jetPrinter().type();
}

JetViewer::JetPrinterStatus JetViewer::printerStatus() const
{
	JetPrinterStatus status = JetPrinterStatus::DISCONNECTED;

	if (_controller.status() == NetworkNode::nNodeStatus::CONNECTED) {
		const JetPrinter& printer = jetPrinter();
		if (printer.isInError()) {
			status = JetPrinterStatus::ERROR;
		}
		else if (printer.paused()) {
			status = JetPrinterStatus::STOPPED;
		}
		else {
			if (printer.printStatus()) {
				status = JetPrinterStatus::PRINTING;
			}
			else {
				status = JetPrinterStatus::RUNNING;
			}
		}
	}
	else if (_controller.status() == NetworkNode::nNodeStatus::CONNECTING) {
		status = JetPrinterStatus::CONNECTING;
	}

	return status;
}

/**************** Printer versions ****************/
std::string JetViewer::printheadVersion(unsigned int numBoard) const
{
	return jetPrinter().board(nJetBoardType::PRINTHEAD_BOARD, numBoard).version();
}

std::string JetViewer::signalsBoardVersion(unsigned int numBoard) const
{
	return jetPrinter().board(nJetBoardType::SIGNALS_BOARD, numBoard).version();
}

std::map<std::string, std::string> JetViewer::installedLibrariesVersions() const
{
	return jetPrinter().getLibrariesVersions();
}

/**************** Printer status ****************/
int JetViewer::id() const
{
	return jetPrinter().id();
}

Printers::PrintDirection JetViewer::printDirection() const
{
	return jetPrinter().printDir();
}
uint64_t JetViewer::sscc() const
{
	return jetPrinter().sscc();
}
bool JetViewer::bitmapInverted() const
{
	return jetPrinter().bitmapInverted();
}
bool JetViewer::isInError() const
{
	return jetPrinter().isInError();
}

JetPrinter::logsList JetViewer::printerLogs(time_t from, time_t to) const
{
	return jetPrinter().logs(from, to);
}

JetPrinter::logsList JetViewer::printerLogs() const
{
	return jetPrinter().logs();
}

bool JetViewer::printStatus() const
{
	return jetPrinter().printStatus();
}

JetPrinter::tanksMap JetViewer::inkTanks() const
{
	return jetPrinter().inkTanks();
}

unsigned int JetViewer::tankLevel(unsigned int id) const
{
	return jetPrinter().tankLevel(id);
}

/**************** Printer Messages ****************/
std::string JetViewer::currentMessage() const
{
	return jetPrinter().messageManager().currentMessage();
}

int JetViewer::currentMessageNum() const
{
	return jetPrinter().messageManager().currentMessageNumber();
}

std::string JetViewer::currentMessageGroup() const
{
	return jetPrinter().messageManager().currentGroup();
}

std::vector<std::string> JetViewer::messageGroups() const
{
	return jetPrinter().messageManager().groups();
}

std::vector<Message> JetViewer::messages(const std::string &group) const
{
	return jetPrinter().messageManager().messages(group);
}

JetViewer::countersMap JetViewer::messagesCounters() const
{
	countersMap counters;
	const Printers::JetMessagesManager& manager = jetPrinter().messageManager();
	std::string group = manager.currentGroup();

	std::vector<Message> messages =  manager.messages(group);
	for  (auto& message : messages) {
		counters.insert(std::pair<unsigned int, unsigned int>(message.number(), message.counter()));
	}
	return counters;
}

/**************** Printer Configuration getters ****************/
bool JetViewer::paused() const
{
	return jetPrinter().paused();
}

JetPrinthead JetViewer::printerPrinthead(unsigned int id)
{
	return jetPrinter().printhead(id);
}

std::vector<JetIO> JetViewer::printheadInputs(unsigned int id) const
{
	std::vector<JetIO> inputs;
	JetBoard ph = jetPrinter().board(nJetBoardType::PRINTHEAD_BOARD, id);
	for (auto& in : ph.inputsList()) {
		JetIO input(in);
		input.setValue(ph.input(in));
		inputs.push_back(input);
	}
	return inputs;
}

std::vector<JetIO> JetViewer::signalsBoardInputs(unsigned int id) const
{
	std::vector<JetIO> inputs;
	JetBoard signal = jetPrinter().board(nJetBoardType::SIGNALS_BOARD, id);
	for (auto& in : signal.inputsList()) {
		JetIO input(in);
		input.setValue(signal.input(in));
		inputs.push_back(input);
	}
	return inputs;
}

std::vector<JetIO> JetViewer::printerInputs() const
{
	std::vector<JetIO> inputs;
	JetBoard ph = jetPrinter().board(nJetBoardType::PRINTHEAD_BOARD, 0);
	for (auto& in : ph.inputsList()) {
		JetIO input(in);
		input.setValue(ph.input(in));
		inputs.push_back(input);
	}

	JetBoard signal = jetPrinter().board(nJetBoardType::SIGNALS_BOARD, 0);
	for (auto& in : signal.inputsList()) {
		JetIO input(in);
		input.setValue(signal.input(in));
		inputs.push_back(input);
	}

	return inputs;
}

JetIO JetViewer::printerInput(const std::string& id) const
{
	std::vector<JetIO> inputs = printerInputs();
	std::vector<JetIO>::const_iterator it = std::find_if(inputs.begin(), inputs.end(),
														 [id](const JetIO& input){return (input.id() == id);});
	if (it != inputs.end()){
		return (*it);
	}
	return JetIO(id);
}

std::vector<JetIO> JetViewer::printerOutputs() const
{
	return jetPrinter().outputs();
}

JetIO JetViewer::printerOutput(const std::string &id) const
{
	std::vector<JetIO> outputs = jetPrinter().outputs();
	std::vector<JetIO>::const_iterator it = std::find_if(outputs.begin(), outputs.end(),
														 [id](const JetIO& output){return (output.id() == id);});
	if (it != outputs.end()){
		return (*it);
	}
	return JetIO(id);
}


// Notifier callbacks
void JetViewer::statusChanged(){}
void JetViewer::configChanged(){}
void JetViewer::filesListChanged(){}
void JetViewer::fontsChanged(){}
void JetViewer::errorsLogsChanged(){}

void JetViewer::nodeStatusChanged(const NetworkNode::nNodeStatus &status)
{
	if (status == NetworkNode::DISCONNECTED) {
		_controller.disconnect();
	}
}

void JetViewer::nodeTimeout()
{}

