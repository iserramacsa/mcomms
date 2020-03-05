#include "tijobserver.h"
#include "tijnotifier.h"
#include <iostream>

using namespace Macsa::MComms;

TijObserver::TijObserver(TijNotifier *controller) :
	Utils::Observer<TijObserver>(controller)
{}

void TijObserver::statusChanged()
{}

void TijObserver::ioStatusChanged()
{}

void TijObserver::configChanged()
{}

void TijObserver::filesListChanged()
{}

void TijObserver::fontsChanged()
{}

void TijObserver::userValuesChanged()
{}

void TijObserver::errorsLogsChanged()
{}

void TijObserver::fileChanged(const std::string &/*unit*/, const std::string &/*filepath*/)
{}
