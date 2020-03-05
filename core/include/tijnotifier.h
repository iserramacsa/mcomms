#ifndef MACSA_MCOMMS_TIJ_NOTIFIER_H
#define MACSA_MCOMMS_TIJ_NOTIFIER_H

#include "utils/observer.h"

namespace Macsa {
	namespace MComms {
		class TijObserver;
		class TijNotifier : public Utils::Notifier<TijObserver>
		{
			public:
				TijNotifier();
				void notifyStatusChanged();
				void notifyIOStatusChanged();
				void notifyConfigChanged();
				void notifyFilesListChanged();
				void notifyFontsChanged();
				void notifyUserValuesChanged();
				void notifyErrorsLogsChanged();
				void notifyFileChanged(const std::string &unit, const std::string &filepath);

		};
	}
}

#endif //MACSA_MCOMMS_TIJ_NOTIFIER_H
