#ifndef JET_VIEWER_CONTROLLER_H
#define JET_VIEWER_CONTROLLER_H

#include <QObject>
#include <QDateTime>
#include "jet/jetviewer.h"

#include <QThread>
#include <QDebug>

class JetViewerController : public QObject, public Macsa::MComms::JetViewer
{
		Q_OBJECT

	public:
		typedef Macsa::MComms::JetViewer::JetPrinterStatus JetStatus;

	signals:
//		void printerStatusChanged();
//		void printerConfigChanged();
//		void printerFilesListChanged();
//		void printerFontsChanged();
//		void printerUserValuesChanged();
//		void printerErrorsLogsChanged();
//		void printerFileChanged(const QString& unit, const QString& filepath);

	public:
		JetViewerController(Macsa::MComms::JetController &controller, QObject* parent = nullptr);
		virtual ~JetViewerController() override {}
		virtual Macsa::MComms::JetController& controller(){ return _controller;}
		//Status
		inline QString id() const {return _(_controller.id());}
		inline QString address() const {return _(_controller.address());}

//		virtual void statusChanged()	 override { emit printerStatusChanged();	 }
//		virtual void configChanged()	 override { emit printerConfigChanged();	 }
//		virtual void filesListChanged()  override { emit printerFilesListChanged();  }
//		virtual void fontsChanged()		 override { emit printerFontsChanged();      }
//		virtual void userValuesChanged() override { emit printerUserValuesChanged(); }
//		virtual void errorsLogsChanged() override { emit printerErrorsLogsChanged(); }
//		virtual void fileChanged(const std::string& unit, const std::string& filepath) override {
//			emit printerFileChanged(_(unit), _(filepath));
//		}

		//Command request
//		bool requestLive();
//		bool requestStatus();
//		bool requestConfig();
//		bool requestErrorsList();
//		bool requestAllFiles();
//		bool requestFontFiles();
//		bool requestMessagesFiles();
//		bool requestImagesFiles();
//		bool requestFileContent(const std::string& filepath, bool rawMode = false);


	protected:
		Macsa::MComms::JetController& _controller;
		Macsa::Printers::JetPrinter* jetPrinter() const;

		inline QString _(const std::string& text) const {return text.c_str();}
};

#endif //TIJ_VIEWER_CONTROLLER_H
