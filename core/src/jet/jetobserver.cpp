#include "jet/jetobserver.h"
#include "jet/jetnotifier.h"

using namespace Macsa::MComms;

JetObserver::JetObserver(JetNotifier *controller) :
	Utils::Observer<JetObserver>(controller)
{

}

void JetObserver::statusChanged() {}

void JetObserver::datetimeChanged(const time_t&){}

void JetObserver::configChanged() {}

void JetObserver::filesListChanged() {}

void JetObserver::fontsChanged() {}

void JetObserver::errorsLogsChanged() {}

void JetObserver::fileGroupChanged(const std::string &/*group*/){}
