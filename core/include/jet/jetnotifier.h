#ifndef MACSA_MCOMMS_JET_NOTIFIER_H
#define MACSA_MCOMMS_JET_NOTIFIER_H

#include "utils/observer.h"

namespace Macsa {
	namespace MComms {
		class JetObserver;
		class JetNotifier : public Utils::Notifier<JetObserver>
		{
			public:
				JetNotifier();
				void notifyStatusChanged();
				void notifyDatetimeChanged(const time_t &);
				void notifyConfigChanged();
				void notifyFilesListChanged();
				void notifyFontsChanged();
//				void notifyUserValuesChanged();
				void notifyErrorsLogsChanged();
				void notifyFileGroupChanged(const std::string& group);

		};
	}
}

#endif //MACSA_MCOMMS_JET_NOTIFIER_H
