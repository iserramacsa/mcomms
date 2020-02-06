#ifndef PRINTER_FILES_VIEW_H
#define PRINTER_FILES_VIEW_H

#include <QWidget>
#include <QtGui>
#include "ui_printerfiles.h"
#include "viewers/tijviewercontroller.h"
#include "tijprintercontroller.h"

class PrinterFilesView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterFilesView(QWidget* parent = 0);
		~PrinterFilesView();
		void setController(Macsa::TIJPrinterController& controller);
		void clear();
		void refresh();

	private:
		TIJViewerController* _controller;
		Ui::PrinterFiles ui;
		QTreeWidget* _treeFiles;

		void AddFilesChild(QTreeWidgetItem* item, const QString& folder, std::vector<std::string> files);

	private slots:
		void onRequestFiles();
		void onRequestFile(QTreeWidgetItem *item, int column);
};


#endif //PRINTER_VIEW_H
