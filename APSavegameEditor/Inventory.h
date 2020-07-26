#pragma once

#include <QWidget>
#include "ui_Inventory.h"
#include "ComboDelegate.h"
#include "ItemModel.h"

class Inventory : public QWidget
{
	Q_OBJECT

public:
	Inventory(QWidget *parent = Q_NULLPTR);
	~Inventory();
	void commit();
	void update();
private:
	void setupTable();
	Ui::Inventory ui;
	std::unique_ptr<ComboDelegate> delegate;
	std::unique_ptr<ItemModel> itemModel;
};
