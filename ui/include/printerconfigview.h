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
		QTableWidget* _bcdTable;
		QComboBox* _printDirection;
		//Photocell
		QComboBox* _photocell;
		//Encoder
		QComboBox* _encoderMode;
		QSpinBox*  _fixedSpeed;
		QSpinBox*  _encoderWheelDiam;
		QSpinBox*  _encoderResolution;
		//ShotMode
		QCheckBox* _multiprint;
		QSpinBox*  _firstDelay;
		QSpinBox*  _nextDelay;
		QSpinBox*  _numPrints;
		QCheckBox* _repeatPrint;
		//Cartridge
		QCheckBox* _autoConfig;
		QSpinBox*  _voltage;
		QCheckBox* _pulseWarm;
		QSpinBox*  _pulseTemp;
		QSpinBox*  _pulseWidth;
		QSpinBox*  _adjCapacity;

		QTableWidget* _inputs;
		QTableWidget* _outputs;
//		QTableWidget* _dateCodes;

		void build();
		QWidget* buildGeneralSettings();
		QWidget* buildPrintSetup();
		QWidget* buildTriggerSetup();
		QWidget* buildBcdTable();
		void updateGeneralSettings();
		void updatePrintSetup();
		void updateTriggerSetup();
		void updateBcdTable();
		void printerDisconnected();

		QStringList printResolutions() const;
		QLabel* getTitle(const QString& text);


	private slots:
		void onStartStop();
		void onToggleAutoStart();
		void onToggleLowLevel();
		void onToggleBlockCartridge();
		void onToggleRotated();
		void onRequestChanges();
};


#endif //PRINTER_VIEW_H
