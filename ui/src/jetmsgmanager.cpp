#include "jetmsgmanager.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidgetItem>
#include <QList>

JetMessageManager::JetMessageManager(QWidget *parent) :
	QWidget(parent)
{
	_controller = nullptr;
	build();
}
//JetMessageManager::~JetMessageManager()
//{}

void JetMessageManager::setController(Macsa::MComms::JetController &controller)
{
	if (_controller != nullptr) {
		delete _controller;
	}
	_controller = new JetViewerController(controller);
	connect(_controller, SIGNAL(printerFilesListChanged()), SLOT(refresh()));
	connect(_controller, SIGNAL(printerFileGroupChanged(QString)), SLOT(refresh()));
	refresh();
}

void JetMessageManager::refresh()
{
	setEnabled(_controller != nullptr);
	if (_controller != nullptr) {
		refreshGroups();
		refreshCurrentGroup();
	}
	else {
		printerDisconnected();
	}
}

//void JetMessageManager::resizeEvent(QResizeEvent *ev)
//{
//	QWidget::resizeEvent(ev);
//}

void JetMessageManager::build()
{
	//Groups
	_groups = new QListWidget(this);
	QStringList gHeaders;
	gHeaders << "Group";
	_groups->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(_groups, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onSelectCurrentGroup()));

	//ButtonsBar
	QWidget* buttons = new QWidget(this);
	QVBoxLayout* lButts = new QVBoxLayout(buttons);
	_butCreateNewGroup = new QPushButton("Create Group", buttons);
	_butResetGroup = new QPushButton("Reset Group", buttons);
	_butDeleteGroup = new QPushButton("Delete Group", buttons);
	lButts->addStretch();
	lButts->addWidget(_butCreateNewGroup);
	lButts->addWidget(_butResetGroup);
	lButts->addWidget(_butDeleteGroup);
	lButts->addStretch();
	connect(_butCreateNewGroup, SIGNAL(clicked()), SLOT(onCreateNewGroup()));
	connect(_butResetGroup, SIGNAL(clicked()), SLOT(onResetGroup()));
	connect(_butDeleteGroup, SIGNAL(clicked()), SLOT(onDeleteGroup()));

	// Messages
	QStringList mHeaders;
	mHeaders << "Id" << "Message" << "Counter";
	_messages = new QTableWidget(this);
	_messages->setColumnCount(mHeaders.count());
	_messages->setHorizontalHeaderLabels(mHeaders);


	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(_groups);
	layout->addWidget(buttons);
	layout->addWidget(_messages);
}

void JetMessageManager::printerDisconnected()
{
	_groups->clear();
	_messages->clear();
	setEnabled(false);
}

void JetMessageManager::refreshGroups()
{
	if (_controller) {
		_groups->clear();
		std::vector<std::string> groups = _controller->messageGroups();
		for (unsigned int i = 0; i  < groups.size(); i++) {
			_groups->addItem(groups.at(i).c_str());
		}
	}
}

void JetMessageManager::refreshCurrentGroup()
{
	if (_controller) {
		_messages->clear();
		std::string currentGroup = _controller->currentMessageGroup();
		std::vector<Macsa::Printers::Message> messages = _controller->messages(currentGroup);

		const int rows = static_cast<int>(messages.size());
		_messages->setRowCount(static_cast<int>(rows));
		for (int i = 0; i < rows; i++) {
			_messages->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(messages.at(static_cast<unsigned>(i)).number())));
			_messages->setItem(i, 1, new QTableWidgetItem(messages.at(static_cast<unsigned>(i)).name().c_str()));
			_messages->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(messages.at(static_cast<unsigned>(i)).counter())));
		}
	}
}

void JetMessageManager::onCreateNewGroup()
{

}

void JetMessageManager::onDeleteGroup()
{
	if (_controller){
		QList<QListWidgetItem*> items =_groups->selectedItems();
		for (int i = 0; i < items.count(); i++) {
			_controller->deleteMessageGroup(items.at(i)->text());
		}
	}
}

void JetMessageManager::onResetGroup()
{
	if (_controller) {
		_controller->resetMessagesGroup();
	}
}

void JetMessageManager::onSelectCurrentMessage(){}
#include <QMessageBox>
void JetMessageManager::onSelectCurrentGroup()
{
	QMessageBox msgbox(this);
	msgbox.setText("Select current group is a not implemented action.");
	msgbox.setModal(true);
}
