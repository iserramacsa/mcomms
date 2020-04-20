#ifndef JET_VIEWER_CONTROLLER_H
#define JET_VIEWER_CONTROLLER_H

#include <QObject>
#include <QDateTime>
#include "jet/jetviewer.h"
#include "jet/datatypes.h"

#include <QThread>
#include <QDebug>

class JetViewerController : public QObject, public Macsa::MComms::JetViewer
{
		Q_OBJECT

	public:
		typedef Macsa::MComms::JetViewer::JetPrinterStatus JetStatus;

	signals:
		void printerStatusChanged();
		void printerConfigChanged();
		void printerFilesListChanged();
		void printerFontsChanged();
//		void printerUserValuesChanged();
		void printerErrorsLogsChanged();
		void printerFileGroupChanged(QString group);
//		void printerFileChanged(const QString& unit, const QString& filepath);

	public:
		JetViewerController(Macsa::MComms::JetController &controller, QObject* parent = nullptr);
		virtual ~JetViewerController() override {}

		//Jet controller
		virtual Macsa::MComms::JetController& controller(){ return _controller;}
		inline QString id() const {return _(_controller.id());}
		inline QString address() const {return _(_controller.address());}

		//JetObserver
		virtual void statusChanged()	 override { emit printerStatusChanged();	 }
		virtual void configChanged()	 override { emit printerConfigChanged();	 }
		virtual void filesListChanged()  override { emit printerFilesListChanged();  }
		virtual void fontsChanged()		 override { emit printerFontsChanged();      }
		virtual void errorsLogsChanged() override { emit printerErrorsLogsChanged(); }
		virtual void fileGroupChanged(const std::string& group) override{
			emit printerFileGroupChanged(_(group));
		}

	public slots:
		//Status commands
		bool getCounters();
		bool getSSCC();
		bool getStatus();
		bool getDateTime();
		bool getPrinterLogs(time_t from = 0, time_t to = time(nullptr), Macsa::Printers::JetLogType type = Macsa::Printers::nJetLogType::LOG_TYPE_ALL);
		bool getPause();
		bool setCounters(const QMap<unsigned int, unsigned int>& counters);
		bool resetCounters();

		//Files commands
		bool requestUSBMessages();
		bool requestFiles();
		bool requestVersions();
		bool requestFonts();

		//Messages commands
		bool setCurrentMessage(unsigned int messageNumber);
		bool sendMessage(const Macsa::Printers::Message& message, const std::vector<char> &content, bool raw);
		bool resetMessagesGroup();
		bool getMessagesGroup(const QString& group);
		bool createMessageGroup(const QString& group);
		bool sendMessageGroup(const QString& group, const Macsa::Printers::Message &message, const std::vector<char> &content, bool raw);
		bool deleteMessageGroup(const QString& group);
		bool setMessageVariable(unsigned int filenum, const QString& variable, const QString& value);
		bool setMessageVariables(unsigned int filenum, const QMap<QString, QString>& values);
		bool getUserInputs(unsigned int filenum, const QString &group = "");
		bool setUserInputs(unsigned int filenum, const QMap<QString, QString>& uiFields, const QString& group = "");

		//Config  commands
		bool setPause(bool pause);
		bool incrementSSCC();
		bool setDateTime(const time_t &datetime);
		bool setOutput(const Macsa::Printers::JetIO& output);
		bool setPrintDirection(Macsa::Printers::PrintDirection dir);
		bool setPrintBitmapInverted(bool inverted);
		bool setPrintSpeed(unsigned int speed);
		bool setPrintDelay(unsigned int delay);
		bool setHorizontalResolution(unsigned int resolution);
		bool setConfig(Macsa::Printers::JetPrinter &printer);

		bool getPrintSpeed();
		bool getPrintDelay();
		bool getHorizontalResolution();
		bool getConfig();
		bool resetInkAlarm();

		//Nisx Commands
		bool getNisXMessage(unsigned int msgNum);
		bool setNisXElement(const QString& filename,  const QString& content);

	protected:
		Macsa::MComms::JetController& _controller;
		Macsa::Printers::JetPrinter* jetPrinter() const;

		inline QString _(const std::string& text) const {return text.c_str();}
		inline std::string _(const QString& text) const {return text.toStdString();}
};

#endif //TIJ_VIEWER_CONTROLLER_H
