#ifndef TIJ_VIEWER_CONTROLLER_H
#define TIJ_VIEWER_CONTROLLER_H

#include <QVariant>
#include <QDateTime>
#include "viewers/printerviewercontroller.h"
#include "tijprintercontroller.h"

class TIJViewerController : public PrinterViewerController
{
	public:
		typedef Macsa::TIJPrinterController::TIJPrinterStatus TIJStatus;
		enum class TIJDataDescriptors
		{
			LIVE = 0,
			STATUS,
			CONFIG,
			ALL_FILES,

			PRINTER_ID,
			PRINTER_ADDRS,
			PRINTER_STATUS,
			PRINTER_DT,
		};

		struct PrinterInput {
				int id;
				QString descriptor;
				bool value;
				QString mode;
				bool inverted;
				uint filter;
		};

		struct PrinterOutput {
				int id;
				QString descriptor;
				bool value;
				bool initialValue;
				QString type;
				uint32_t time;
		};

		struct PrinterError {
				QDateTime timestamp;
				QString type;
				uint priority;
				QString code;
		};

	public:
		TIJViewerController(Macsa::TIJPrinterController& controller);
		virtual ~TIJViewerController(){}
		virtual Macsa::TIJPrinterController& controller(){ return _controller;}
		virtual QVariant data(int descriptor);
		virtual bool setData(int descriptor, const QVariant& value);

		TIJStatus printerStatus() const;

		QString boardType() const;
		QString boardControllerVersion() const;
		QString boardFPGAVersion() const;
		QString boardAPIVersion() const;

		bool autoStart() const;
		//		void setAutoStart(bool autoStart);

		bool lowLevelOutput() const;
		//		void setLowLevelOutput(bool lowLevelOutput);

		bool printing() const;
		//		void setPrinting(bool printing);

		bool enabled() const;
		void setEnabled(bool enabled);

		bool blocked() const;
		//		void setBlocked(bool blocked);

		QString currentMessage() const;
		QString userMessage() const;
		//		void setUserMessage(const std::string &currentMessage);

		QMap<int, QString> bcdTable() const;
		QString bcdMode() const;
		uint8_t currentBcdCode() const;
		// void setBcdTable(const BCDTable& bcdTable);
		// void setBcdMode(const BCDMode &mode);
		// void setBcdMode(const BCDMode_n &mode);
		// void setBcdMode(const std::string &mode);
		// void setBcdCurrent(uint8_t current);

		QString printDirection() const;
		// void setPrinterDirection(const PrinterDir &printDirection);
		// void setPrinterDirection(const PrinterDir_n &printDirection);
		// void setPrinterDirection(const std::string &printDirection);

		bool printRotated() const;
		//void setPrintRotated(bool printRotated);

		QString nozzlesCol() const;
		// void setNozzlesCol(const NozzlesCol &nozzlesCol);
		// void setNozzlesCol(const NozzlesCol_n &nozzlesCol);
		// void setNozzlesCol(const std::string &nozzlesCol);

		QString shotMode() const;
		uint16_t shotModeNumPrints() const;
		QVector<uint> shotModeDelays() const;
		bool shotModeRepeat() const;
		//void setShotMode(const ShotMode& shotMode);

		QString encoderMode() const;
		double encoderFixedSpeed() const;
		double encoderResolution() const;
		double encoderDiameter() const;
		// void setEncoderMode(const EncoderMode &value);
		// void setEncoderMode(const std::string &value);
		//void setEncoderFixedSpeed(double value);
		//void setEncoderResolution(double value);
		//void setEncoderDiameter(double value);

		QString photocell() const;
		//void setPhotocell(const Photocell& photocell);
		//void setPhotocell(const Photocell_n& photocell);
		//void setPhotocell(const std::string & photocell);

		QMap<QString, int> counters() const;
		int counter(const QString& name) const;
		//void setCounters(const countersMap& counters);
		//void setCounter(const std::string& name, int value);

		QMap<QString, QString> properties() const;
		QString property(const QString& name) const;
		//void setProperties(const propertyMap& properties);
		//void setProperty(const std::string& name, const std::string& value);

		bool cartridgeAutoSetup() const;
		double cartridgeFiringVoltage() const;
		double cartridgePulseWidth() const;
		bool cartridgePulseWarming() const;
		double cartridgePulseWarmTemp() const;
		double cartridgeAdjustedCapacity() const;
		//		void setCartridge(const Cartridge &cartridge);

		QVector<PrinterInput> inputs() const;
		PrinterInput input(unsigned int idx) const;
		//		void setInputs(const std::vector<Input>& inputs);
		//		void setInput(unsigned int idx, const Input& input);

		QVector<PrinterOutput> outputs() const;
		PrinterOutput output(unsigned int idx) const;
		//		void setOutputs(const std::vector<Output>& outputs);
		//		void setOutput(unsigned int idx, const Output& output);

		QVector<PrinterError> errors() const;
		PrinterError error(unsigned int idx) const;
		//		void setErrors(const std::vector<Error>& errors);
		//		void setError(unsigned int idx, const Error& error);

	protected:
		Macsa::TIJPrinterController& _controller;
		Macsa::Printers::TIJPrinter* tijPrinter() const;
		const Macsa::Printers::Board* tijPrinterBoard() const;
		PrinterInput printerInputToView(Macsa::Printers::Input in) const;
		PrinterOutput printerOutputToView(Macsa::Printers::Output out) const;
};

#endif //TIJ_VIEWER_CONTROLLER_H
