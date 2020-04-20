#include "tijfilesview.h"

TijFilesView::TijFilesView(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	_controller = nullptr;

	connect(ui.butRefresh, SIGNAL(clicked(bool)), SLOT(onRequestFiles()));

	_treeFiles = ui.treeFiles;
	_treeFiles->setColumnCount(3);
	_treeFiles->setHeaderLabels(QStringList()<< "Path"<<"Type"<<"Size");
	_treeFiles->setColumnWidth(0, 600);

	connect(_treeFiles, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(onRequestFile(QTreeWidgetItem*,int)));

	clear();
}

TijFilesView::~TijFilesView()
{
	if (_controller != nullptr) {
		delete _controller;
	}
}

void TijFilesView::setController(Macsa::MComms::TijController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new TIJViewerController(controller);
	connect(_controller, SIGNAL(printerFilesListChanged()), SLOT(refresh()));
	connect(_controller, SIGNAL(printerFontsChanged()), SLOT(refresh()));
	connect(_controller, SIGNAL(printerFileChanged(const QString &, const QString &)), SLOT(onFileChanged(const QString &, const QString &)));
	refresh();
}

void TijFilesView::clear()
{
	_treeFiles->clear();
}

void TijFilesView::refresh()
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

void TijFilesView::AddFilesChild(QTreeWidgetItem *item, const QString &folder, std::vector<std::string> files)
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
			QString filepath = QString("%1%2/%3").arg(item->text(0)).arg(folder).arg((*it).c_str());
			std::vector<uint8_t>content = _controller->controller().getFile(filepath.toStdString());
			file->setText(2, QString("%1 kb").arg(QString::number((static_cast<double>(content.size())/1024),'f',2)));
			fItem->insertChild(fItem->childCount(), file);
		}
		item->insertChild(item->childCount(), fItem);
	}
}

void TijFilesView::onFileChanged(const QString &unit, const QString &filePath)
{
	QString pwd = filePath;
	pwd.replace("//", "/");
	QStringList route = pwd.split("/");
	QList<QTreeWidgetItem*> items =_treeFiles->findItems(route.last(), Qt::MatchFlag::MatchExactly);
	if (items.count()){
		qDebug() << items;
	}
	refresh();
}

void TijFilesView::onRequestFiles()
{
	_controller->requestAllFiles();
}

void TijFilesView::onRequestFile(QTreeWidgetItem *item, int)
{
	if (!item->childCount()){
		QString path = QString("/%1.%2").arg(item->text(0)).arg(item->text(1));
		while (item->parent() != nullptr) {
			item = item->parent();
			path.prepend(item->text(0));
		}
		path.replace("///", "//");

		if (_controller != nullptr) {
			_controller->requestFileContent(path.toStdString());
		}
	}
}
