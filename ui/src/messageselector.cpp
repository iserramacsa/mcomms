#include "messageselector.h"

using namespace Macsa;
using namespace Macsa::MComms;
using namespace Macsa::Printers;

MessageSelectorDialog::MessageSelectorDialog(TijController& controller, QWidget *parent) :
	QDialog(parent),
	TijViewer(controller)
{
	ui.setupUi(this);
	_selectedMessage = "";
	_filesTree = ui.messagesView;
	fillTreeView();
	connect(_filesTree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), SLOT(onMessageSelected(QTreeWidgetItem *, int)));
	setWindowTitle("Tij User Message Selector");
}

MessageSelectorDialog::~MessageSelectorDialog()
{}

QString MessageSelectorDialog::selectedMessage() const
{
	return _selectedMessage;
}

void MessageSelectorDialog::filesListChanged()
{
	fillTreeView();
}

#include<QDebug>
void MessageSelectorDialog::onMessageSelected(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column)
	Q_UNUSED(item)
	QString filepath = item->data(0, Qt::DisplayRole).toString();

//	while(item->parent()){
//		item = item->parent();
//		if (item->parent()){
//			filepath.prepend("/");
//		}
//		filepath.prepend(item->data(0, Qt::DisplayRole).toString());
//	}

	qDebug() << "Selected message: "  << filepath;
	_selectedMessage = filepath;
}

void MessageSelectorDialog::fillTreeView()
{
	_filesTree->setHeaderLabels(QStringList());
	_filesTree->clear();
	_filesTree->setColumnCount(1);
	std::vector<std::string> drives = printerDrives();
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
		std::vector<std::string> files = printerFiles(d->c_str(), "messages");
		if (files.size()) {
			QTreeWidgetItem* fItem = new QTreeWidgetItem();
			fItem->setText(0, "messages");
			fItem->setIcon(0, QIcon(":/icons/folder.svg"));

			for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++) {
				QTreeWidgetItem* file = new QTreeWidgetItem();
				file->setText(0, it->c_str());
				fItem->insertChild(fItem->childCount(), file);
			}
			item->insertChild(item->childCount(), fItem);
		}
		item->setExpanded(true);
		items << item;
	}
	_filesTree->insertTopLevelItems(0, items);

}
