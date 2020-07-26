#pragma once

#include <QAbstractTableModel>
constexpr int COLS = 2;
constexpr int ROWS = 5;
class ItemModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	ItemModel(QObject *parent);
	~ItemModel();
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	void update();
	void commit();
	std::vector<std::string> getItemNames();
private:
	QString m_gridData[ROWS][COLS];
	void initializeMappings();
	std::unordered_map<unsigned int, std::string> idNameMapping;
	std::unordered_map<std::string, unsigned int> nameIdMapping;
};
