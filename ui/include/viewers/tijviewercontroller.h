#ifndef TIJ_VIEWER_CONTROLLER_H
#define TIJ_VIEWER_CONTROLLER_H

#include <QObject>
#include <QDateTime>
#include "tijviewer.h"

#include <QThread>
#include <QDebug>

class TIJViewerController : public QObject, public Macsa::MComms::TijViewer
{
		Q_OBJECT

	public:
		typedef Macsa::MComms::TijViewer::TijPrinterStatus TijStatus;
		enum class TIJConfigProperties
		{
			HEADER_TYPE = 0,
			SHUTTER_ENABLED,
			SHUTTER_TIME,
			HRES,
			PRINTMODE,
			PRINTMODE_INTENSITY,
			PRINTMODE_RESOLUTION_MODE,
			PRINTMODE_RESOLUTION_PH,
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
				uint boardId;
				QDateTime timestamp;
				QString type;
				uint priority;
				QString code;
		};

		struct NetworkIface {
				QString iface;
				QString address;
				QString netmask;
				QString gateway;
				QString hwAddress;
				bool dhcp;
				uint16_t port;
		};

		struct BluetoothDevice {
				QString name;
				QString pass;
				bool visible;
		};

	signals:
		void printerStatusChanged();
		void printerConfigChanged();
		void printerFilesListChanged();
		void printerFontsChanged();
		void printerUserValuesChanged();
		void printerErrorsLogsChanged();
		void printerFileChanged(const QString& unit, const QString& filepath);

	public:
		TIJViewerController(Macsa::MComms::TijController &controller, QObject* parent = nullptr);
		virtual ~TIJViewerController() override {}
		virtual Macsa::MComms::TijController& controller(){ return _controller;}
		//Status
		QString id() const {return _(_controller.id());}
		QString address() const {return _(_controller.address());}

		virtual void statusChanged()	 override { /*qDebug() << " Observer: " << Macsa::MComms::TijObserver::id() << "Th: " << QThread::currentThreadId() << " " << __func__;*/ emit printerStatusChanged();	  }
		virtual void configChanged()	 override { /*qDebug() << " Observer: " << Macsa::MComms::TijObserver::id() << "Th: " << QThread::currentThreadId() << " " << __func__;*/ emit printerConfigChanged();	  }
		virtual void filesListChanged()  override { /*qDebug() << " Observer: " << Macsa::MComms::TijObserver::id() << "Th: " << QThread::currentThreadId() << " " << __func__;*/ emit printerFilesListChanged();  }
		virtual void fontsChanged()		 override { /*qDebug() << " Observer: " << Macsa::MComms::TijObserver::id() << "Th: " << QThread::currentThreadId() << " " << __func__;*/ emit printerFontsChanged();      }
		virtual void userValuesChanged() override { /*qDebug() << " Observer: " << Macsa::MComms::TijObserver::id() << "Th: " << QThread::currentThreadId() << " " << __func__;*/ emit printerUserValuesChanged(); }
		virtual void errorsLogsChanged() override { /*qDebug() << " Observer: " << Macsa::MComms::TijObserver::id() << "Th: " << QThread::currentThreadId() << " " << __func__;*/ emit printerErrorsLogsChanged(); }
		virtual void fileChanged(const std::string& unit, const std::string& filepath) override {
			//qDebug() << "Observer: " << Macsa::MComms::TijObserver::id() << " " << __func__ << " Unit: " << _(unit) << " File: " << _(filepath);
			emit printerFileChanged(_(unit), _(filepath));
		}

		//Command request
		bool requestLive();
		bool requestStatus();
		bool requestConfig();
		bool requestErrorsList();
		bool requestAllFiles();
		bool requestFontFiles();
		bool requestMessagesFiles();
		bool requestImagesFiles();
		bool requestFileContent(const std::string& filepath, bool rawMode = false);


		// File related getters and setters
		std::vector<uint8_t> getFileContent(const std::string& filepath);

		//Status related getters and setters
		QString printerDateTime(const QString &format = "");
		QVector<PrinterError> errorsLog() const;
		bool printing() const;

		QString boardType() const;
		QString boardControllerVersion() const;
		QString boardFPGAVersion() const;
		QString boardAPIVersion() const;

		//Config related getters or setters
			//Network
		NetworkIface networkIface(int index) const;
		BluetoothDevice bluetooth() const;

			//Logger
		QString loggerLevelStr() const;
		Macsa::Printers::LoggerLevel loggerLevel() const;
		bool traceComms() const;
		bool loggerEnabled() const;
			//General config
		bool autoStart() const;
		bool setAutoStart(bool autoStart);
		bool lowLevelOutput() const;
		bool setLowLevelOutput(bool lowLevelOutput);
		bool enabled() const;
		bool setEnabled(bool enabled);
		bool blocked() const;
		bool setBlocked(bool blocked);


		QString currentMessage() const;
		QString userMessage() const;
		//void setUserMessage(const std::string &currentMessage);

		QMap<int, QString> bcdTable() const;
		QString bcdModeStr() const;
		Macsa::Printers::BCDMode bcdMode() const;
		uint8_t currentBcdCode() const;
		// void setBcdTable(const BCDTable& bcdTable);
		// void setBcdMode(const BCDMode &mode);
		// void setBcdMode(const BCDMode_n &mode);
		// void setBcdMode(const std::string &mode);
		// void setBcdCurrent(uint8_t current);

		QString printDirectionStr() const;
		Macsa::Printers::PrinterDir printDirection() const;
		// void setPrinterDirection(const PrinterDir &printDirection);
		// void setPrinterDirection(const PrinterDir_n &printDirection);
		// void setPrinterDirection(const std::string &printDirection);

		bool printRotated() const;
		bool setPrintRotated(bool printRotated);

		QString nozzlesColStr() const;
		Macsa::Printers::NozzlesCol nozzlesCol() const;
		// void setNozzlesCol(const NozzlesCol &nozzlesCol);
		// void setNozzlesCol(const NozzlesCol_n &nozzlesCol);
		// void setNozzlesCol(const std::string &nozzlesCol);

		QString shotModeStr() const;
		Macsa::Printers::ShootingMode shotMode() const;
		uint16_t shotModeNumPrints() const;
		QVector<uint> shotModeDelays() const;
		bool shotModeRepeat() const;
		//void setShotMode(const ShotMode& shotMode);

		QString encoderModeStr() const;
		Macsa::Printers::EncoderMode encoderMode() const;
		double encoderFixedSpeed() const;
		double encoderResolution() const;
		double encoderDiameter() const;
		// void setEncoderMode(const EncoderMode &value);
		// void setEncoderMode(const std::string &value);
		//void setEncoderFixedSpeed(double value);
		//void setEncoderResolution(double value);
		//void setEncoderDiameter(double value);

		QString photocellStr() const;
		Macsa::Printers::Photocell photocell() const;
		//void setPhotocell(const Photocell& photocell);
		//void setPhotocell(const Photocell_n& photocell);
		//void setPhotocell(const std::string & photocell);

		QMap<QString, int> counters() const;
		int counter(const QString& name) const;
		//void setCounters(const countersMap& counters);
		//void setCounter(const std::string& name, int value);

		QMap<QString, QString> statusProperties() const;
		QString statusProperty(const QString& name) const;
		QMap<QString, QString> configProperties() const;
		QString configProperty(const QString& name) const;
		QString configProperty(const TIJConfigProperties& param) const;
		//void setConfigProperties(const propertyMap& properties);
		//void setConfigProperty(const std::string& name, const std::string& value);

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

// Deprecated // std::vector<Macsa::Printers::Error> errors() const;
// Deprecated // Macsa::Printers::Error error(unsigned int idx) const;
		//		void setErrors(const std::vector<Error>& errors);
		//		void setError(unsigned int idx, const Error& error);

		Macsa::Printers::DateCodes dateCodes() const;
//		void setDateCodes(const Macsa::Printers::DateCodes &dateCodes);

	protected:
		Macsa::MComms::TijController& _controller;
		Macsa::Printers::TijPrinter* tijPrinter() const;
		const Macsa::Printers::Board* tijPrinterBoard() const;
		PrinterInput printerInputToView(Macsa::Printers::Input in) const;
		PrinterOutput printerOutputToView(Macsa::Printers::Output out) const;

		inline QString _(const std::string& text) const {return text.c_str();}
};

#endif //TIJ_VIEWER_CONTROLLER_H
