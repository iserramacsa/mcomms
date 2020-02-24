#include "network/nodeobserver.h"
#include "network/networknode.h"

using namespace Macsa;
using namespace Macsa::Network;

static unsigned idSeed = 0;

NodeObserver::NodeObserver(NetworkNode* subject) :
	_id(idSeed++),
	_node(subject)
{
	if (_node != nullptr){
		_node->attach(this);
	}
}

NodeObserver::~NodeObserver()
{
	if (_node != nullptr){
		_node->detach(this);
	}
}

unsigned NodeObserver::id() const
{
	return _id;
}

bool NodeObserver::equal(const NodeObserver &other) const
{
	return (_id == other._id);
}
