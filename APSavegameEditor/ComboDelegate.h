#pragma once

#include <QItemDelegate>
#include <string>
#include <vector>
#include "SpinBoxDelegate.h"
#include "DropdownDelegate.h"

class ComboDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ComboDelegate(QObject *parent, std::vector<std::string>&& options);
	~ComboDelegate();
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
		const QModelIndex& index) const;
private:
	std::unique_ptr<SpinBoxDelegate> spinbox;
	std::unique_ptr<DropdownDelegate> dropdown;
};
