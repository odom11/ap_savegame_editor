#include <QAbstractItemView>
#include <QDebug>

#include "Inventory.h"
#include "ItemModel.h"
#include "SpinBoxDelegate.h"
#include "ComboDelegate.h"
#include "DropdownDelegate.h"

Inventory::Inventory(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupTable();
}

Inventory::~Inventory()
{
}

void Inventory::setupTable() {
	itemModel = std::make_unique<ItemModel>(this);
	ui.tableView->setModel(itemModel.get());
	delegate = std::make_unique<ComboDelegate>(this);
	ui.tableView->setItemDelegate(delegate.get());
}

void Inventory::commit() {
	qDebug() << "committing inventory";
}