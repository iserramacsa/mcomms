#ifndef PRINTER_FILES_VIEW_H
#define PRINTER_FILES_VIEW_H

#include <QWidget>
#include <QtGui>
#include "ui_printerfiles.h"
#include "viewers/jetviewercontroller.h"
#include "jet/jetcontroller.h"

class JetFilesView : public QWidget
{
		Q_OBJECT
	public:
		explicit JetFilesView(QWidget* parent = 0);
		~JetFilesView();
		void setController(Macsa::MComms::JetController& controller);
		void clear();

	public slots:
		void refresh();

	private:
		JetViewerController* _controller;
		Ui::PrinterFiles ui;
		QTreeWidget* _treeFiles;

		void addDirectoryChild(QTreeWidgetItem* item, const Macsa::Printers::Directory* directory);
		void addFilesChild(QTreeWidgetItem* item, std::vector<std::string> files);

	private slots:
//		void onFileChanged(const QString & unit, const QString & filePath); //Not implemented in jet protocol
		void onRequestFiles();
//		void onRequestFile(QTreeWidgetItem *item, int column);				//Not implemented in jet protocol
};


#endif //PRINTER_VIEW_H
