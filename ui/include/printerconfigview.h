#ifndef PRINTER_CONFIG_VIEW_H
#define PRINTER_CONFIG_VIEW_H

#include <QWidget>
#include "viewers/tijviewercontroller.h"
#include "tijprintercontroller.h"
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QTableWidget>
#include <QSpinBox>
#include "printer/datatypes.h"

class PrinterConfigView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterConfigView(QWidget* parent = 0);
		~PrinterConfigView();
		void setController(Macsa::TIJPrinterController& controller);

	signals:
		void configChangeRequested();

	public slots:
		void refresh();

	private:
		TIJViewerController* _controller;

		//General config
		QPushButton* _butEnable;
		QCheckBox* _printAutostart;
		QCheckBox* _lowLevelOutput;
		QCheckBox* _blockCartridge;

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

		QTableWidget* _inputs;
		QTableWidget* _outputs;
//		QTableWidget* _dateCodes;

		void build();
		QWidget* buildGeneralSettings();
		QWidget* buildPrintSetup();
		QWidget* buildTriggerSetup();
		QWidget* buildDateCodesSetup();
		QWidget* buildBcdTable();
		QWidget* buildCartridgeSetup();
		QWidget* buildIOSetup();

		void updateGeneralSettings();
		void updatePrintSetup();
		void updateTriggerSetup();
		void updateBcdTable();
		void updateDateCodes();
		void updateCartridgeSettings();
		void updateIOSettings();

		void printerDisconnected();

		QStringList printResolutions() const;
		QWidget* buildPrintDelay(QWidget* parent, QSpinBox** editor) const;
		QWidget* buildCartridgeSpinBox(QWidget* parent, QDoubleSpinBox** editor, const QString& units, int min, int max, int decimals = 2) const;
		QLabel* getTitle(const QString& text);

		void addInputRow(QTableWidget* table, int row, const TIJViewerController::PrinterInput& input);
		void addOutputRow(QTableWidget* table, int row, const TIJViewerController::PrinterOutput& output);

		template <typename N>
		QStringList getPrinterEnumOptions(const Macsa::Printers::SmartEnum<N>& e) const;


		void resizeEvent(QResizeEvent*);

	private slots:
		void onStartStop();
		void onToggleAutoStart();
		void onToggleLowLevel();
		void onToggleBlockCartridge();
		void onToggleRotated();
		void onRequestChanges();
		void onChangeResolution(int idx);
		void onChangeNozzlesCols(int idx);

		void validateTriggerSettings();
		void validateCartridgeSettings();
};


#endif //PRINTER_VIEW_H
