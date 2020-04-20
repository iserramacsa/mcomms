#ifndef MACSA_MCOMMS_UI_TIJ_MESSAGE_SELECTOR_DIALOG_H
#define MACSA_MCOMMS_UI_TIJ_MESSAGE_SELECTOR_DIALOG_H

#include <QtGui>
#include <QDialog>
#include "ui_selectMessageDialog.h"

#include "tij/tijviewer.h"


class TijMessageSelectorDialog : public QDialog, public Macsa::MComms::TijViewer
{
		Q_OBJECT
	public:
		explicit TijMessageSelectorDialog(Macsa::MComms::TijController& controller, QWidget * parent = nullptr);
		virtual ~TijMessageSelectorDialog();
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
