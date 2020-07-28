#pragma once

#include <QWidget>
#include "ui_Gadgets.h"
#include "ComboDelegate.h"
#include "ItemModel.h"

class Gadgets : public QWidget
{
	Q_OBJECT

public:
	Gadgets(QWidget *parent = Q_NULLPTR);
	~Gadgets();
	void commit();
	void update();
private:
	void setupTable();
	Ui::Inventory ui;
	std::unique_ptr<ComboDelegate> delegate;
	std::unique_ptr<ItemModel> itemModel;
};
