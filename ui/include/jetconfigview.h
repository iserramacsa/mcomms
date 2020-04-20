#ifndef JET_PRINTER_CONFIG_VIEW_H
#define JET_PRINTER_CONFIG_VIEW_H

#include <QWidget>
#include "viewers/jetviewercontroller.h"
#include "jet/jetcontroller.h"
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QTableWidget>
#include <QSpinBox>
#include "jet/datatypes.h"

class JetConfigView : public QWidget
{
		Q_OBJECT
	public:
		explicit JetConfigView(QWidget* parent = 0);
		~JetConfigView();
		void setController(Macsa::MComms::JetController& controller);

	public slots:
		void refresh();

	private:
		JetViewerController* _controller;

		//General config
		QPushButton* _butEnable;
		QCheckBox*   _printingList;
		QCheckBox*   _sendMessageAfterPrint;
		QCheckBox*   _useFifo;
		QCheckBox*   _delayinPoints;
		QCheckBox*   _stbIncSCC;
		QCheckBox*   _stbResetList;
		QCheckBox*   _OptimizeBarcode;
		QLabel*		 _userMessage;
		QPushButton* _butMessage;
		QComboBox*   _overlappingMode;
		QComboBox*   _printMode;
		QComboBox*   _defaultFont;

		//Print Setup
		QCheckBox* _printInverted;
		QComboBox* _printDirection;
		QSpinBox*  _horizontalResolution;
		//Encoder
		QComboBox* _encoderMode;
		QSpinBox*  _fixedSpeed;
		QSpinBox*  _encoderPulses;
		QSpinBox*  _encoderWheel;
		QSpinBox*  _encoderAbcPitch;
		//IOS
//		QTableWidget* _inputs;
//		QTableWidget* _outputs;

		void build();
		QWidget* buildGeneralSettings();
		QWidget* buildPrintSetup();
//		QWidget* buildIOSetup();

		void updateGeneralSettings();
		void updatePrintSetup();
//		void updateIOSettings();

		void printerDisconnected();

		// Helpers
//		QStringList printResolutions() const;
//		QWidget* buildPrintDelay(QWidget* parent, QSpinBox** editor) const;
//		QWidget* buildCartridgeSpinBox(QWidget* parent, QDoubleSpinBox** editor, const QString& units, int min, int max, int decimals = 2) const;
//		QWidget* buildDateCodeTable(QTableWidget** table, QStringList headers, QWidget* parent) const;
		QLabel* getTitle(const QString& text);

//		void fillDateCodes(QTableWidget* table, const std::vector<Macsa::Printers::DateCode::DateCodeGeneric>& data);
//		void addInputRow(QTableWidget* table, int row, int iniCol, const JetViewerController::PrinterInput& input);
//		void addOutputRow(QTableWidget* table, int row, const JetViewerController::PrinterOutput& output);

		template <typename N>
		QStringList getPrinterEnumOptions(const Macsa::Utils::SmartEnum<N>& e) const;


//		void resizeEvent(QResizeEvent*);

	private slots:
		void onStartStop();
		void onToggleInverted();
		void onChangeResolution(int hres);
};


#endif //TIJ_PRINTER_VIEW_H
