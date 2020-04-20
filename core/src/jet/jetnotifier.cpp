#include "jet/jetnotifier.h"
#include "jet/jetobserver.h"

using namespace Macsa;
using namespace Utils;
using namespace Macsa::MComms;

JetNotifier::JetNotifier()
{

}

void JetNotifier::notifyStatusChanged()
{
	std::function<void (JetObserver *)> func = &JetObserver::statusChanged;
	notifyObservers(func);
}

void JetNotifier::notifyDatetimeChanged(const time_t& dt)
{
	std::function<void (JetObserver *, const time_t&)> func = &JetObserver::datetimeChanged;
	notifyObservers(func, dt);
}

void JetNotifier::notifyConfigChanged()
{
	std::function<void (JetObserver *)> func = &JetObserver::configChanged;
	notifyObservers(func);
}

void JetNotifier::notifyFilesListChanged()
{
	std::function<void (JetObserver *)> func = &JetObserver::filesListChanged;
	notifyObservers(func);
}

void JetNotifier::notifyFontsChanged()
{
	std::function<void (JetObserver *)> func = &JetObserver::fontsChanged;
	notifyObservers(func);
}

void JetNotifier::notifyErrorsLogsChanged()
{
	std::function<void (JetObserver *)> func = &JetObserver::errorsLogsChanged;
	notifyObservers(func);
}

void JetNotifier::notifyFileGroupChanged(const std::string &group)
{
	std::function<void (JetObserver *, const std::string&)> func = &JetObserver::fileGroupChanged;
	notifyObservers(func, group);
}

