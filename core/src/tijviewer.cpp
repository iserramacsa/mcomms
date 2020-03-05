#include "tijviewer.h"

using namespace Macsa::MComms;

TijViewer::TijViewer(TijController &controller) :
	TijObserver(&controller),
	_controller(controller)
{

}

TijViewer::~TijViewer()
{

}
