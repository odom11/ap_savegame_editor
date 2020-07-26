#include "ComboDelegate.h"
#include "SpinBoxDelegate.h"
#include <stdexcept>

ComboDelegate::ComboDelegate(QObject *parent, std::vector<std::string>&& options)
	: QItemDelegate(parent)
{
    spinbox = std::make_unique<SpinBoxDelegate>(this);
    dropdown = std::make_unique<DropdownDelegate>(this, std::move(options));
}

ComboDelegate::~ComboDelegate()
{
}
QWidget* ComboDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if (index.column() == 0) {
        return dropdown->createEditor(parent, option, index);
    }
    else if (index.column() == 1) {
        return spinbox->createEditor(parent, option, index);
    }
    throw std::runtime_error("something went wrong");
}