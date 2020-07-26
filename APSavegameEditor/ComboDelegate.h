#pragma once

#include <QItemDelegate>
#include "SpinBoxDelegate.h"
#include "DropdownDelegate.h"

class ComboDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ComboDelegate(QObject *parent);
	~ComboDelegate();
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
		const QModelIndex& index) const;
private:
	std::unique_ptr<SpinBoxDelegate> spinbox;
	std::unique_ptr<DropdownDelegate> dropdown;
};
