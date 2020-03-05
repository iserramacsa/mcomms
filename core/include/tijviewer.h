#ifndef MACSA_MCOMMS_TIJ_VIEWER_H
#define MACSA_MCOMMS_TIJ_VIEWER_H

#include "tijcontroller.h"
#include "tijobserver.h"

namespace Macsa {
	namespace MComms {
		class TijViewer : public TijObserver
		{
			public:
				TijViewer(TijController& controller);
				virtual ~TijViewer();

			private:
				TijController& _controller;
		};
	}
}

#endif //MACSA_MCOMMS_TIJ_VIEWER_H
