#include "tijobserver.h"

using namespace Macsa;

static unsigned int seed = 0;

TijObserver::TijObserver(TijController *controller) :
	_id(seed++),
	_controller(controller)
{
	if (_controller != nullptr) {
		_controller->attach(this);
	}
}

TijObserver::~TijObserver()
{
	if (_controller != nullptr) {
		_controller->detach(this);
	}
}

unsigned int TijObserver::id() const
{
	return _id;
}
