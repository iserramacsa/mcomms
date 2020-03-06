#include "tijviewer.h"

using namespace Macsa::MComms;
using namespace Macsa::Network;

TijViewer::TijViewer(TijController &controller) :
	TijObserver(&controller),
	Network::NodeObserver(&controller),
	_controller(controller)
{}

TijViewer::~TijViewer()
{}

//Node Observer callbacks
void TijViewer::statusChanged(){}

void TijViewer::ioStatusChanged(){}

void TijViewer::configChanged(){}

void TijViewer::filesListChanged(){}

void TijViewer::fontsChanged(){}

void TijViewer::userValuesChanged(){}

void TijViewer::errorsLogsChanged(){}

void TijViewer::fileChanged(const std::string& /*unit*/, const std::string& /*filepath*/){}

//Node Observer callbacks
void TijViewer::nodeStatusChanged(const NetworkNode::nNodeStatus& status)
{
	if (status == NetworkNode::DISCONNECTED) {
		_controller.disconnect();
	}
}
void TijViewer::nodeTimeout()
{}
