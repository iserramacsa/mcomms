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


/**********************************************************************/
JetPrinter *JetViewerController::jetPrinter() const
{
	JetPrinter* jet = nullptr;
	if (_controller.status() == Network::NetworkNode::CONNECTED) {
		jet = dynamic_cast<JetPrinter*>(_controller.printer());
	}
	return jet;
}
