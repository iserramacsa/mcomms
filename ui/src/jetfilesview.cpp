#include "jetfilesview.h"

JetFilesView::JetFilesView(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	_controller = nullptr;

	connect(ui.butRefresh, SIGNAL(clicked(bool)), SLOT(onRequestFiles()));

	_treeFiles = ui.treeFiles;
	_treeFiles->setColumnCount(2);
	_treeFiles->setHeaderLabels(QStringList() << "Path" << "Type");
	_treeFiles->setColumnWidth(0, 600);

	/**** Not implemented in jet protocol ****/
//	connect(_treeFiles, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(onRequestFile(QTreeWidgetItem*,int)));

	clear();
}

JetFilesView::~JetFilesView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void JetFilesView::setController(Macsa::MComms::JetController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new JetViewerController(controller);
	connect(_controller, SIGNAL(printerFilesListChanged()), SLOT(refresh()));
	connect(_controller, SIGNAL(printerFontsChanged()), SLOT(refresh()));

	/**** Not implemented in jet protocol ****/
//	connect(_controller, SIGNAL(printerFileChanged(const QString &, const QString &)), SLOT(onFileChanged(const QString &, const QString &)));


	refresh();
}

void JetFilesView::clear()
{
	_treeFiles->clear();
}

void JetFilesView::refresh()
{
	_treeFiles->clear();
	if (_controller != nullptr)
	{
		std::vector<std::string> drives = _controller->printerDrives();
		QList<QTreeWidgetItem*> items;
		for (std::vector<std::string>::iterator d = drives.begin(); d != drives.end(); d++) {
			QTreeWidgetItem* item = new QTreeWidgetItem();
			item->setText(0, d->c_str());
			if (item->text(0) == "") {
				item->setIcon(0, QIcon(":/icons/sd_card.svg"));
			}
			else if (item->text(0) == "USB//") {
				item->setIcon(0, QIcon(":/icons/usb.svg"));
			}
			std::vector<std::string> directories = _controller->printerDirectories(*d);
			for (std::vector<std::string>::iterator dir = directories.begin(); dir != directories.end(); dir++) {
				addDirectoryChild(item, _controller->printerDirectory(*d, *dir));
			}
			item->setExpanded(true);
			items << item;
		}
		_treeFiles->insertTopLevelItems(0, items);

		///Expand all
		for (int i = 0; i < items.count(); i++) {
			const QTreeWidgetItem* item = items.at(i);
			for (int j = 0; j < item->childCount(); j++) {
				_treeFiles->setItemExpanded(item->child(j), true);
			}
			_treeFiles->setItemExpanded(item, true);
		}
	}
}

void JetFilesView::addDirectoryChild(QTreeWidgetItem *item, const Macsa::Printers::Directory *directory)
{
	if (directory) {
		QTreeWidgetItem* fItem = new QTreeWidgetItem();
		fItem->setText(0, directory->name().c_str());
		fItem->setIcon(0, QIcon(":/icons/folder.svg"));
		std::vector<std::string> subdirectories = directory->getSubdirectoriesList();
		for (std::vector<std::string>::iterator dir = subdirectories.begin(); dir != subdirectories.end(); dir++) {
			addDirectoryChild(fItem, directory->getSubdirectory(*dir));
		}
		addFilesChild(fItem, directory->getFilesList());
		item->insertChild(item->childCount(), fItem);
	}
}

void JetFilesView::addFilesChild(QTreeWidgetItem *item, std::vector<std::string> files)
{
	if (files.size()) {
		for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++) {

			size_t ext = (*it).find_last_of(".");
			QTreeWidgetItem* file = new QTreeWidgetItem();
			if (ext != (*it).npos) {
				std::string extension = (*it).substr(ext + 1);
				file->setText(0, (*it).c_str());
				file->setText(1, extension.c_str());
			}
			else {
				file->setText(0, (*it).c_str());
			}
			item->insertChild(item->childCount(), file);
		}
	}
}

/**** Not implemented in jet protocol ****/
//void JetFilesView::onFileChanged(const QString &unit, const QString &filePath)
//{
//	QString pwd = filePath;
//	pwd.replace("//", "/");
//	QStringList route = pwd.split("/");
//	QList<QTreeWidgetItem*> items =_treeFiles->findItems(route.last(), Qt::MatchFlag::MatchExactly);
//	if (items.count()){
//		qDebug() << items;
//	}
//	refresh();
//}

void JetFilesView::onRequestFiles()
{
	_controller->requestFiles();
	_controller->requestFonts();
	_controller->requestUSBMessages();
}

/**** Not implemented in jet protocol ****/
//void JetFilesView::onRequestFile(QTreeWidgetItem *item, int)
//{
//	if (!item->childCount()){
//		QString path = QString("/%1.%2").arg(item->text(0)).arg(item->text(1));
//		while (item->parent() != nullptr) {
//			item = item->parent();
//			path.prepend(item->text(0));
//		}
//		path.replace("///", "//");

//		if (_controller != nullptr) {
//			_controller->requestFileContent(path.toStdString());
//		}
//	}
//}
