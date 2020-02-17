#include "printerslistmodel.h"
#include <QDebug>

PrintersListModel::PrintersListModel(Macsa::PrintersManager &manager, QObject *parent) :
	QStringListModel(parent),
	_manager(manager)
{
//	_manager.connect(std::bind(&PrintersListModel::onPrinterAdded, this, std::placeholders::_1));
}

PrintersListModel::~PrintersListModel()
{}

int PrintersListModel::rowCount(const QModelIndex &/*parent*/) const
{
	qDebug() << __func__ << " printers count: " << _manager.size();
	return static_cast<int>(_manager.size());
}

QVariant PrintersListModel::data(const QModelIndex &index, int role) const
{
	switch (role) {
		case Qt::DisplayRole:
		case Qt::UserRole:
			if (index.row() >= 0){
				Macsa::PrinterController * tij = _manager.getPrinter(index.row());
				if (tij !=  nullptr){
					qDebug() << __func__ << " printer: " << tij->id().c_str();
					return QString(tij->id().c_str());
				}
			}
			break;
		default:
			break;
	}

	return QVariant();
}

//QModelIndex PrintersListModel::index(int row, int column, const QModelIndex &parent) const
//{
//	QModelIndex index = QModelIndex();
//	if (column == 0) {
//		if (row < rowCount()){
//			qDebug() << __func__;
//			 index = createIndex(row, column, _manager.getPrinter(row));
//		}
//	}

//	return index;
//}

//Macsa::PrintersManager::AddedPrinterCallback PrintersListModel::onPrinterAdded(const std::string &printer)
//{
//	qDebug() << __func__ << " printers count: " << _manager.size();
//	emit dataChanged(QModelIndex(), QModelIndex());
//	return nullptr;
//}
