#ifndef MACSA_UI_JET_MESSAGE_MANAGER_H
#define MACSA_UI_JET_MESSAGE_MANAGER_H

#include <QWidget>
#include "viewers/jetviewercontroller.h"
#include "jet/jetcontroller.h"
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>

class JetMessageManager : public QWidget
{
		Q_OBJECT
	public:
		explicit JetMessageManager(QWidget* parent = 0);
//		~JetMessageManager();
		void setController(Macsa::MComms::JetController& controller);

	public slots:
		void refresh();

	private:
		QTableWidget* _messages;
		QListWidget*  _groups;
		QPushButton*  _butResetGroup;
		QPushButton*  _butCreateNewGroup;
		QPushButton*  _butDeleteGroup;

		JetViewerController* _controller;

//		virtual void resizeEvent(QResizeEvent *);

		void build();
		void printerDisconnected();

		void refreshGroups();
		void refreshCurrentGroup();

	private slots:
		void onCreateNewGroup();
		void onDeleteGroup();
		void onResetGroup();
		void onSelectCurrentMessage();
		void onSelectCurrentGroup();
};

#endif //MACSA_UI_JET_MESSAGE_MANAGER_H
