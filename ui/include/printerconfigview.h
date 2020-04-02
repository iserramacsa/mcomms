#ifndef PRINTER_CONFIG_VIEW_H
#define PRINTER_CONFIG_VIEW_H

#include <QWidget>
#include "viewers/tijviewercontroller.h"
#include "tij/tijcontroller.h"
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QTableWidget>
#include <QSpinBox>
#include "tij/datatypes.h"

class PrinterConfigView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterConfigView(QWidget* parent = 0);
		~PrinterConfigView();
		void setController(Macsa::MComms::TijController& controller);

	signals:
		void configChangeRequested();

	public slots:
		void refresh();

	private:
		TIJViewerController* _controller;

		//Logs
		QCheckBox* _logsEnabled;
		QComboBox* _loggerLevel;
		QCheckBox* _traceComms;

		//General config
		QPushButton* _butEnable;
		QCheckBox*   _printAutostart;
		QCheckBox*   _lowLevelOutput;
		QCheckBox*   _blockCartridge;
		QLabel*		 _userMessage;
		QPushButton* _butMessage;

		//Print Setup
		QCheckBox* _printRotated;
		QComboBox* _printResolution;
		QComboBox* _nozzlesCols;
		QComboBox* _bcdMode;
		QComboBox* _printDirection;
		//Photocell
		QComboBox* _photocell;
		//Encoder
		QComboBox* _encoderMode;
		QDoubleSpinBox*  _fixedSpeed;
		QDoubleSpinBox*  _encoderWheelDiam;
		QDoubleSpinBox*  _encoderResolution;
		//ShotMode
		QCheckBox* _multiprint;
		QSpinBox*  _firstDelay;
		QSpinBox*  _nextDelay;
		QSpinBox*  _numPrints;
		QCheckBox* _repeatPrint;
		//BCD Table
		QTableWidget* _bcdTable;
		//Cartridge
		QCheckBox*		_autoConfig;
		QDoubleSpinBox* _voltage;
		QCheckBox*		_pulseWarm;
		QDoubleSpinBox* _pulseTemp;
		QDoubleSpinBox* _pulseWidth;
		QDoubleSpinBox* _adjCapacity;
		//IOS
		QTableWidget* _inputs;
		QTableWidget* _outputs;
		//Date & Shift codes
		QTableWidget* _shiftCodes;
		QTableWidget* _minuteCodes;
		QTableWidget* _hoursCodes;
		QTableWidget* _daysCodes;
		QTableWidget* _weekDayCodes;
		QTableWidget* _julianCodes;
		QTableWidget* _weeksCodes;
		QTableWidget* _monthCodes;
		QTableWidget* _yearsCodes;

		void build();
		QWidget* buildLoggerSettings();
		QWidget* buildGeneralSettings();
		QWidget* buildPrintSetup();
		QWidget* buildTriggerSetup();
		QWidget* buildDateCodesSetup();
		QWidget* buildBcdTable();
		QWidget* buildCartridgeSetup();
		QWidget* buildIOSetup();

		void updateLoggerSettings();
		void updateGeneralSettings();
		void updatePrintSetup();
		void updateTriggerSetup();
		void updateBcdTable();
		void updateDateCodes();
		void updateCartridgeSettings();
		void updateIOSettings();

		void printerDisconnected();

		// Helpers
		QStringList printResolutions() const;
		QWidget* buildPrintDelay(QWidget* parent, QSpinBox** editor) const;
		QWidget* buildCartridgeSpinBox(QWidget* parent, QDoubleSpinBox** editor, const QString& units, int min, int max, int decimals = 2) const;
		QWidget* buildDateCodeTable(QTableWidget** table, QStringList headers, QWidget* parent) const;
		QLabel* getTitle(const QString& text);

		void fillDateCodes(QTableWidget* table, const std::vector<Macsa::Printers::DateCode::DateCodeGeneric>& data);
		void addInputRow(QTableWidget* table, int row, int iniCol, const TIJViewerController::PrinterInput& input);
		void addOutputRow(QTableWidget* table, int row, const TIJViewerController::PrinterOutput& output);

		template <typename N>
		QStringList getPrinterEnumOptions(const Macsa::Utils::SmartEnum<N>& e) const;


		void resizeEvent(QResizeEvent*);
		void resizeDateCodeTableColumns(QTableWidget* table);

	private slots:
		void onStartStop();
		void onToggleAutoStart();
		void onToggleLowLevel();
		void onToggleBlockCartridge();
		void onToggleRotated();
		void onRequestChanges();
		void onChangeResolution(int idx);
		void onChangeNozzlesCols(int idx);
		void onSelectUserMessage();

		void validateTriggerSettings();
		void validateCartridgeSettings();
};


#endif //PRINTER_VIEW_H
