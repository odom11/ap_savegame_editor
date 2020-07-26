#include <QDebug>
#include "Stats.h"

Stats::Stats(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Stats::~Stats()
{
}

void Stats::commit() {
	qDebug() << "committing stats";
}
