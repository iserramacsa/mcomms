#include "network/networkobserver.h"
#include "network/networknotifier.h"
#include <iostream>

using namespace Macsa;
using namespace Macsa::Network;

NetworkObserver::NetworkObserver(NetworkNotifier *subject) :
	Utils::Observer<NetworkObserver>(subject)
{}

