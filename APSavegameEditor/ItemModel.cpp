#include "ItemModel.h"

ItemModel::ItemModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

ItemModel::~ItemModel()
{
}

int ItemModel::rowCount(const QModelIndex&/*parent*/) const {
	return ROWS;
}

int ItemModel::columnCount(const QModelIndex&/*parent*/) const {
	return COLS;
}

QVariant ItemModel::data(const QModelIndex& index, int role) const {
    
	if (role == Qt::DisplayRole)
        return m_gridData[index.row()][index.column()];
		/*return QString("Row%1, Column%2")
		.arg(index.row() + 1)
		.arg(index.column() + 1);*/
	return QVariant();
}

bool ItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emit a joined string
        return true;
    }
    return false;
}

Qt::ItemFlags ItemModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}