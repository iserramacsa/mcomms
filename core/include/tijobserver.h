#ifndef MACSA_MCOMMS_TIJ_OBSERVER_H
#define MACSA_MCOMMS_TIJ_OBSERVER_H

#include "utils/observer.h"

namespace Macsa {
	class TijNotifier;
	class TijObserver : public Utils::Observer<TijObserver>
	{
		public:
			TijObserver(TijNotifier* controller);

			virtual void statusChanged();
			virtual void ioStatusChanged();
			virtual void configChanged();
			virtual void filesListChanged();
			virtual void fontsChanged();
			virtual void userValuesChanged();
			virtual void errorsLogsChanged();
			virtual void fileChanged(const std::string& unit, const std::string& filepath);
	};
}

#endif //MACSA_MCOMMS_TIJ_OBSERVER_H
