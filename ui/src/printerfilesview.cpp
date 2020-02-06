#include "printerfilesview.h"

PrinterFilesView::PrinterFilesView(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	_controller = nullptr;

	connect(ui.butRefresh, SIGNAL(clicked(bool)), SLOT(onRequestFiles()));

	_treeFiles = ui.treeFiles;
	_treeFiles->setColumnCount(2);
	_treeFiles->setHeaderLabels(QStringList()<< "Path"<<"Type");
	_treeFiles->setColumnWidth(0, 600);

	connect(_treeFiles, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(onRequestFile(QTreeWidgetItem*,int)));

	clear();
}

PrinterFilesView::~PrinterFilesView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void PrinterFilesView::setController(Macsa::TIJPrinterController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new TIJViewerController(controller);
	refresh();
}

void PrinterFilesView::clear()
{
	_treeFiles->clear();
}

void PrinterFilesView::refresh()
{
	_treeFiles->clear();
	if (_controller != nullptr)
	{
		std::vector<std::string> drives = _controller->controller().getDrives();
		QList<QTreeWidgetItem*> items;
		for (std::vector<std::string>::iterator d = drives.begin(); d != drives.end(); d++) {
			QTreeWidgetItem* item = new QTreeWidgetItem();
			item->setText(0, d->c_str());
			if (item->text(0) == "//") {
				item->setIcon(0, QIcon(":/icons/sd_card.svg"));
			}
			else if (item->text(0) == "USB//") {
				item->setIcon(0, QIcon(":/icons/usb.svg"));
			}
			AddFilesChild(item, "fonts",_controller->controller().getFonts(d->c_str()));
			AddFilesChild(item, "messages", _controller->controller().getMessages(d->c_str()));
			AddFilesChild(item, "images", _controller->controller().getImages(d->c_str()));
			item->setExpanded(true);
			items << item;
		}
		_treeFiles->insertTopLevelItems(0, items);
	}
}

void PrinterFilesView::AddFilesChild(QTreeWidgetItem *item, const QString &folder, std::vector<std::string> files)
{
	if (files.size()) {
		QTreeWidgetItem* fItem = new QTreeWidgetItem();
		fItem->setText(0, folder);
		fItem->setIcon(0, QIcon(":/icons/folder.svg"));

		for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++) {
			QStringList fileName = QString(it->c_str()).split(".");
			QTreeWidgetItem* file = new QTreeWidgetItem();
			for (int f = 0; f < fileName.count(); ++f) {
				file->setText(f, fileName.at(f));
			}
			fItem->insertChild(fItem->childCount(), file);
		}

		item->insertChild(item->childCount(), fItem);
	}
}

void PrinterFilesView::onRequestFiles()
{
	if (_controller->data(static_cast<int>(TIJViewerController::TIJDataDescriptors::ALL_FILES)).toBool()) {
		refresh();
	}
}

#include <QDebug>
void PrinterFilesView::onRequestFile(QTreeWidgetItem *item, int)
{
	if (!item->childCount()){
		QString path = QString("%1.%2").arg(item->text(0)).arg(item->text(1));
		while (item->parent() != nullptr) {
			path.prepend("/");
			item = item->parent();
			path.prepend(item->text(0));
		}

		if (_controller != nullptr) {
//			std::vector<uint8_t> bytes = _controller->controller().getFile(path);
		}
	}
}
