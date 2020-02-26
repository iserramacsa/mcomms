#include "tijobserver.h"

#include <iostream>

using namespace Macsa;

static unsigned int seed = 0;

TijObserver::TijObserver(TijController *controller) :
	_id(seed++),
	_controller(controller)
{
	std::cout <<  __PRETTY_FUNCTION__ << " Observer: " <<  _id << std::endl;
	if (_controller != nullptr) {
		_controller->attach(this);
	}
}

TijObserver::~TijObserver()
{
	std::cout <<  __PRETTY_FUNCTION__ << " Observer: " <<  _id << std::endl;
	if (_controller != nullptr) {
		_controller->detach(this);
	}
}

unsigned int TijObserver::id() const
{
	return _id;
}

void TijObserver::controllerDeleted()
{
	_controller = nullptr;
}
