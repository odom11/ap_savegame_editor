#include "ItemModel.h"

const std::string GADGET_PREFIX = "SLOT_GADGET_";
const std::string GADGET_TYPE_SUFFIX = "_Value";
const std::string GADGET_COUNT_SUFFIX = "_Num";

ItemModel::ItemModel(QObject *parent)
	: QAbstractTableModel(parent)
{
    initializeMappings();
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

void ItemModel::update() {





    QModelIndex index;
    QModelIndex topLeftIndex = index.sibling(0, 0);
    QModelIndex bottomRight = index.sibling(ROWS - 1, COLS - 1);
    emit QAbstractItemModel::dataChanged(topLeftIndex, bottomRight);
}

void ItemModel::commit() {

}

std::vector<std::string> ItemModel::getItemNames() {
    std::vector<std::string> names;
    names.reserve(nameIdMapping.size());
    std::transform(nameIdMapping.begin(), nameIdMapping.end(), std::back_inserter(names), [&](const auto& it) {return it.first; });
    return names;
}

void ItemModel::initializeMappings() {
}