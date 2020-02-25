#ifndef MACSA_MCOMMS_TIJ_OBSERVER_H
#define MACSA_MCOMMS_TIJ_OBSERVER_H

#include "tijprintercontroller.h"

namespace Macsa {
	class TijObserver
	{
		public:
			TijObserver(TijController* controller);
			virtual ~TijObserver();

			unsigned int id() const;

			virtual void statusChanged()	 const{}
			virtual void configChanged()	 const{}
			virtual void filesListChanged()  const{}
			virtual void fontsChanged()		 const{}
			virtual void userValuesChanged() const{}
			virtual void errorsLogsChanged() const{}

		private:
			const unsigned int _id;
			TijController* _controller;
	};
}

#endif //MACSA_MCOMMS_TIJ_OBSERVER_H
