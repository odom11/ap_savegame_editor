#pragma once

#include <QItemDelegate>
#include <string>
#include <vector>

class DropdownDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	DropdownDelegate(QObject *parent, std::vector<std::string>&& items);
	~DropdownDelegate();
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
		const QModelIndex& index) const;
	void setEditorData(QWidget* editor, const QModelIndex& index) const;
	void setModelData(QWidget* editor, QAbstractItemModel* model,
		const QModelIndex& index) const;
	void updateEditorGeometry(QWidget* editor,
		const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
	std::vector<std::string> options;
};
