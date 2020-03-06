#ifndef MACSA_MCOMMS_TIJ_VIEWER_H
#define MACSA_MCOMMS_TIJ_VIEWER_H

#include "tijcontroller.h"
#include "tijobserver.h"
#include "network/nodeobserver.h"
#include "tij/tijprinter.h"

namespace Macsa {
	using namespace Printers;
	namespace MComms {
		class TijViewer : public TijObserver, protected Network::NodeObserver
		{
			public:
				enum class TijPrinterStatus ///Todo: change to smart enum
				{
					DISCONNECTED = -1,
					CONNECTING,
					STOPPED,
					WARNING,
					RUNNING,
					PRINTING,
				};

				using propertyMap = Board::propertyMap;
				using countersMap = Board::countersMap;

			public:
				TijViewer(TijController& controller);
				virtual ~TijViewer()override;

				//Printer base getters
				std::time_t printerDateTime() const;
				std::string printerType() const;
				TijPrinterStatus printerStatus() const;

				//Tij Printer data getters
				std::string printerControllerVersion() const;
				std::string printerApiVersion() const;
				std::string printerFpgaVersion() const;

				//Tij Status parameters
				int printerId() const;
				std::string printerCurrentMessage() const;
				uint8_t printerCurrentBCDCode() const;
				BCDMode printerBCDMode() const;
				bool printerIsPrinting() const;

				// Counters
				countersMap printerCounters() const;
				int printerCounter(const std::string& name) const;

				propertyMap printerStatusProperties() const;
				std::string printerStatusProperty(const std::string& name) const;

				//Tij Configuration parameters
				//  General Configuration
				bool printerAutoStart() const;
				bool printerLowLevelOutput() const;
				bool printerEnabled() const;
				bool printerBlocked() const;
				std::string userMessage() const;

				//  Print setup
				bool printerPrintRotated() const;
				PrinterDir printerPrintDirection() const;
				NozzlesCol printerNozzlesCol() const;
				Photocell printerPhotocell() const;
				EncoderMode printerEncoderMode() const;
				double printerEncoderFixedSpeed() const;
				double printerEncoderResolution() const;
				double printerEncoderDiameter() const;

				//  Trigger Setup
				ShotMode printerShotMode() const; //TODO

				//  BCD Table
				BCDTable printerBCDTable() const;

				// Cartridge settings
				Cartridge printerCartridgeSettings() const;

				// Configuration properties
				propertyMap printerConfigurationProperties() const;
				std::string printerConfigurationProperty(const std::string& name) const;

				// Datecodes
				DateCodes printerDateCodes() const;

				//Inputs
				std::vector<Input> printerInputs() const;
				Input printerInput(unsigned int idx) const;

				//outputs
				std::vector<Output> printerOutputs() const;
				Output printerOutput(unsigned int idx) const;

				//Errors
				std::vector<Error> printerErrors() const;
				Error printerError(unsigned int idx) const;

				//Tij Logger
				std::vector<Error> printerErrorsLog() const;
				bool printerLogsEnabled() const;
				bool printerLogComsEnabled() const;
				LoggerLevel printerLoggerLevel() const;

				//Tij Observer callbacks
				virtual void statusChanged() override;
				virtual void ioStatusChanged() override;
				virtual void configChanged() override;
				virtual void filesListChanged() override;
				virtual void fontsChanged() override;
				virtual void userValuesChanged() override;
				virtual void errorsLogsChanged() override;
				virtual void fileChanged(const std::string& unit, const std::string& filepath) override;

			private:
				//Node Observer callbacks
				virtual void nodeStatusChanged(const Network::NetworkNode::nNodeStatus& status) override;
				virtual void nodeTimeout() override;

			private:
				TijController& _controller;
				inline const Printers::TijPrinter& tijprinter() const {return dynamic_cast<const Printers::TijPrinter&>(*(_controller.printer()));}
				inline const Printers::Board& tijBoard() const {return (*tijprinter().board(0));}
				inline bool validBoard() const { return (tijprinter().board(0) != nullptr);}
		};
	}
}

#endif //MACSA_MCOMMS_TIJ_VIEWER_H
