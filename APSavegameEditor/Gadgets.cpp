#include <QAbstractItemView>
#include <QDebug>

#include "Gadgets.h"
#include "ItemModel.h"
#include "SpinBoxDelegate.h"
#include "ComboDelegate.h"
#include "DropdownDelegate.h"

Gadgets::Gadgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupTable();
}

Gadgets::~Gadgets()
{
}

void Gadgets::setupTable() {
	itemModel = std::make_unique<ItemModel>(this);
	ui.tableView->setModel(itemModel.get());
	//ui.tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);

	delegate = std::make_unique<ComboDelegate>(this, itemModel->getItemNames());
	ui.tableView->setItemDelegate(delegate.get());
}

void Gadgets::commit() {
	itemModel->commit();
	qDebug() << "committing inventory";
}

void Gadgets::update() {
	itemModel->update();
}