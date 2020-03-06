#ifndef MACSA_MCOMMS_TIJ_VIEWER_H
#define MACSA_MCOMMS_TIJ_VIEWER_H

#include "tijcontroller.h"
#include "tijobserver.h"
#include "network/nodeobserver.h"

namespace Macsa {
	namespace MComms {
		class TijViewer : public TijObserver, protected Network::NodeObserver
		{
			public:
				TijViewer(TijController& controller);
				virtual ~TijViewer()override;

				//Tij Observer callbacks
				virtual void statusChanged() override;
				virtual void ioStatusChanged() override;
				virtual void configChanged() override;
				virtual void filesListChanged() override;
				virtual void fontsChanged() override;
				virtual void userValuesChanged() override;
				virtual void errorsLogsChanged() override;
				virtual void fileChanged(const std::string& unit, const std::string& filepath) override;

			protected:
				//Node Observer callbacks
				virtual void nodeStatusChanged(const Network::NetworkNode::nNodeStatus& status) override;
				virtual void nodeTimeout() override;

			private:
				TijController& _controller;
		};
	}
}

#endif //MACSA_MCOMMS_TIJ_VIEWER_H
