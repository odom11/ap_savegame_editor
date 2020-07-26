#include "DropdownDelegate.h"
#include <QComboBox>

DropdownDelegate::DropdownDelegate(QObject *parent, std::vector<std::string>&& item)
	: QItemDelegate(parent)
{
    options = item;
}

DropdownDelegate::~DropdownDelegate()
{
}

QWidget* DropdownDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem&/* option */,
    const QModelIndex& /*index*/) const
{
    QComboBox* editor = new QComboBox(parent);
    for (const auto& entry : options) {
        editor->addItem(QString::fromStdString(entry));
    }
    //editor->addItem("foo");
    //editor->addItem("bar");
    return editor;
}

void DropdownDelegate::setEditorData(QWidget* editor,
    const QModelIndex& index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QComboBox* spinBox = static_cast<QComboBox*>(editor);
    spinBox->setCurrentIndex(value);
    //spinBox->setValue(value);
}

void DropdownDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
    const QModelIndex& index) const
{
    QComboBox* spinBox = static_cast<QComboBox*>(editor);
    QString value = spinBox->currentText();

    model->setData(index, value, Qt::EditRole);
}

void DropdownDelegate::updateEditorGeometry(QWidget* editor,
    const QStyleOptionViewItem& option, const QModelIndex&/* index */) const
{
    editor->setGeometry(option.rect);
}
