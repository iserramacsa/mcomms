#ifndef PRINTERS_LIST_MODEL_H
#define PRINTERS_LIST_MODEL_H

#include <QObject>
#include <QStringListModel>
#include "printersmanager.h"

class PrintersListModel : public QStringListModel
{
		Q_OBJECT
	public:
		explicit PrintersListModel(Macsa::MComms::PrintersManager& manager, QObject *parent = nullptr);
		virtual ~PrintersListModel();

		//Pure virtuals methods
		virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
		virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
//		virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

//		Macsa::MComms::PrintersManager::AddedPrinterCallback onPrinterAdded(const std::string& printer);
	private:
		Macsa::MComms::PrintersManager& _manager;
};

#endif
