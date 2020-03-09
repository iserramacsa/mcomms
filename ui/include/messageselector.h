#ifndef MACSA_MCOMMS_UI_MESSAGE_SELECTOR_DIALOG_H
#define MACSA_MCOMMS_UI_MESSAGE_SELECTOR_DIALOG_H

#include <QtGui>
#include <QDialog>
#include "ui_selectMessageDialog.h"

#include "tijviewer.h"


class MessageSelectorDialog : public QDialog, public Macsa::MComms::TijViewer
{
		Q_OBJECT
	public:
		explicit MessageSelectorDialog(Macsa::MComms::TijController& controller, QWidget * parent = nullptr);
		virtual ~MessageSelectorDialog();
		QString selectedMessage() const;

		virtual void filesListChanged() override;

	private slots:
		void onMessageSelected(QTreeWidgetItem *item, int column);

	private:
		Ui::MessageSelector ui;
		QString _selectedMessage;
		QTreeWidget* _filesTree;

		void fillTreeView();
};

#endif
