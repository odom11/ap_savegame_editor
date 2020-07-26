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

private:
	Ui::Stats ui;
};
