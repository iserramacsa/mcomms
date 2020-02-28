#include "tijnotifier.h"
#include "tijobserver.h"

using namespace Macsa;


TijNotifier::TijNotifier()
{}

void TijNotifier::notifyStatusChanged()
{
	std::function<void (TijObserver *)> func = &TijObserver::statusChanged;
	notifyObservers(func);
}

void TijNotifier::notifyIOStatusChanged()
{
	std::function<void (TijObserver *)> func = &TijObserver::ioStatusChanged;
	notifyObservers(func);
}

void TijNotifier::notifyConfigChanged()
{
	std::function<void (TijObserver *)> func = &TijObserver::configChanged;
	notifyObservers(func);
}
void TijNotifier::notifyFilesListChanged()
{
	std::function<void (TijObserver *)> func = &TijObserver::filesListChanged;
	notifyObservers(func);
}

void TijNotifier::notifyFontsChanged()
{
	std::function<void (TijObserver *)> func = &TijObserver::fontsChanged;
	notifyObservers(func);
}

void TijNotifier::notifyUserValuesChanged()
{
	std::function<void (TijObserver *)> func = &TijObserver::userValuesChanged;
	notifyObservers(func);
}

void TijNotifier::notifyErrorsLogsChanged()
{
	std::function<void (TijObserver *)> func = &TijObserver::errorsLogsChanged;
	notifyObservers(func);
}

void TijNotifier::notifyFileChanged(const std::string& unit, const std::string& filepath)
{
	std::function<void (TijObserver *, const std::string&, const std::string& )> func = &TijObserver::fileChanged;
	notifyObservers(func, unit, filepath);
}
