#ifndef MACSA_MCOMMS_JET_OBSERVER_H
#define MACSA_MCOMMS_JET_OBSERVER_H

#include "utils/observer.h"

namespace Macsa {
	namespace MComms {
		class JetNotifier;
		class JetObserver : public Utils::Observer<JetObserver>
		{
			public:
				JetObserver(JetNotifier* controller);

				virtual void statusChanged();
				virtual void datetimeChanged(const time_t &);
				virtual void configChanged();
				virtual void filesListChanged();
				virtual void fontsChanged();
//				virtual void userValuesChanged();
				virtual void errorsLogsChanged();
				virtual void fileGroupChanged(const std::string& group);
		};
	}
}

#endif //MACSA_MCOMMS_JET_OBSERVER_H
