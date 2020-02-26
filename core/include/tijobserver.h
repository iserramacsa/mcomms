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

			virtual void statusChanged()	  {}
			virtual void ioStatusChanged()	  {}
			virtual void configChanged()	  {}
			virtual void filesListChanged()   {}
			virtual void fontsChanged()		  {}
			virtual void userValuesChanged()  {}
			virtual void errorsLogsChanged()  {}
			virtual void fileChanged(const std::string& unit, const std::string& filepath) {}
			void controllerDeleted();

		private:
			const unsigned int _id;
			TijController* _controller;
	};
}

#endif //MACSA_MCOMMS_TIJ_OBSERVER_H
