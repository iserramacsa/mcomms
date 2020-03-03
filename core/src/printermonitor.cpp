#include "printermonitor.h"

using namespace Macsa;
using namespace Macsa::Network;

PrinterMonitor::PrinterMonitor(const std::string &id, const std::string &address) :
	PrinterController(id, address, 0)
{}

PrinterMonitor::~PrinterMonitor()
{}
