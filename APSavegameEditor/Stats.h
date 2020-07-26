#pragma once

#include <QWidget>
#include "ui_Stats.h"

class Stats : public QWidget
{
	Q_OBJECT

public:
	Stats(QWidget *parent = Q_NULLPTR);
	~Stats();
	void commit();
	void update();

private:
	
	Ui::Stats ui;
	void initializeFreeStatpoints();
};
