#include "ItemModel.h"
#include "SavefileRepository.h"

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
    for (int i = 0; i < ROWS; ++i) {
        std::string itemKey = GADGET_PREFIX + std::to_string(i + 1) + GADGET_TYPE_SUFFIX;
        std::byte itemId = SavefileRepository::getInstance().lookForValue(itemKey);

        std::string numKey = GADGET_PREFIX + std::to_string(i + 1) + GADGET_COUNT_SUFFIX;
        std::byte numItems = SavefileRepository::getInstance().lookForValue(numKey);

        if (idNameMapping.contains((int)itemId)) {
            m_gridData[i][0] = QString::fromStdString(idNameMapping[(int) itemId]);
        }
        else {
            m_gridData[i][0] = QString::fromStdString(std::to_string((int)itemId));
        }
        m_gridData[i][1] = QString::fromStdString(std::to_string((int) numItems));
    }

    QModelIndex index;
    QModelIndex topLeftIndex = index.sibling(0, 0);
    QModelIndex bottomRight = index.sibling(ROWS - 1, COLS - 1);
    emit QAbstractItemModel::dataChanged(topLeftIndex, bottomRight);
}

void ItemModel::commit() {
    for (int i = 0; i < ROWS; ++i) {
        std::string itemKey = GADGET_PREFIX + std::to_string(i + 1) + GADGET_TYPE_SUFFIX;
        std::string numKey = GADGET_PREFIX + std::to_string(i + 1) + GADGET_COUNT_SUFFIX;

        std::byte count = (std::byte) m_gridData[i][1].toInt();
        std::string gridItemId = m_gridData[i][0].toStdString();
        std::byte itemNumber = nameIdMapping.contains(gridItemId) ? (std::byte) nameIdMapping[gridItemId] : (std::byte) m_gridData[i][0].toInt();

        if (itemNumber == (std::byte) 0) {
            count = (std::byte) 0;
        }

        if (count == (std::byte) 0) {
            itemNumber = (std::byte) 0;
        }

        SavefileRepository::getInstance().alterValue(itemKey, itemNumber);
        SavefileRepository::getInstance().alterValue(numKey, count);
    }
}

std::vector<std::string> ItemModel::getItemNames() {
    std::vector<std::string> names;
    names.reserve(nameIdMapping.size());
    std::transform(nameIdMapping.begin(), nameIdMapping.end(), std::back_inserter(names), [&](const auto& it) {return it.first; });
    return names;
}

void ItemModel::initializeMappings() {

    auto enter = [&](const std::tuple<std::string, int> item) {
        nameIdMapping[std::get<0>(item)] = std::get<1>(item);
        idNameMapping[std::get<1>(item)] = std::get<0>(item);
    };

    auto tuple = std::make_tuple("", 0);
    enter(tuple);

    tuple = std::make_tuple("radio mimic", 24);
    enter(tuple);



    tuple = std::make_tuple("incendiary bomb", 7);
    enter(tuple);

    tuple = std::make_tuple("explosive grenade", 1);
    enter(tuple);

    tuple = std::make_tuple("emp grenade", 10);
    enter(tuple);

    tuple = std::make_tuple("first aid", 21);
    enter(tuple);
}