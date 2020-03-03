#ifndef MACSA_MPROTOCOL_COMMANDS_LIVE_H
#define MACSA_MPROTOCOL_COMMANDS_LIVE_H

#include "mcommands.h"

namespace Macsa
{
	namespace MProtocol {
		///
		/// \brief The PrinterLiveStatus is a convenience struct
		/// to check if some part of printer configuration has changed
		/// since last communication.
		///
		struct LiveFlags
		{
			bool statusChanged;
			bool configChanged;
			bool filesChanged;
			bool fontsChanged;
			bool errorsLogChanged;
			bool userValueChanged;
			bool isInError;

			LiveFlags() {
				statusChanged = false;
				configChanged = false;
				filesChanged  = false;
				fontsChanged  = false;
				isInError     = false;
				errorsLogChanged = false;
				userValueChanged = false;
			}
		};

		class MLive : public MCommand
		{
			public:
				MLive(Printers::TijPrinter &printer, LiveFlags& liveStatus);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				LiveFlags& _liveFlags;
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MLIVE_COMMANDS_H
