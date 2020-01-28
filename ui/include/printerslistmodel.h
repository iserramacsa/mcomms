#ifndef PRINTERS_LIST_MODEL_H
#define PRINTERS_LIST_MODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "printersmanager.h"

class PrintersListModel : public QAbstractListModel
{
		Q_OBJECT
	public:
		explicit PrintersListModel(Macsa::PrintersManager& manager, QObject *parent = nullptr):
			_manager(manager){}

		virtual ~PrintersListModel(){}

		//Required implemented functions
		virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
		void rowsAboutToBeInserted(const QModelIndex & parent, int start, int end)

		void updateList();

	private:
		Macsa::PrintersManager& _manager;
};

#endif
