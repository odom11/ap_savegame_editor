#pragma once

#include <QModel>

class ItemsModel : public QModel
{
	Q_OBJECT

public:
	ItemsModel(QObject *parent);
	~ItemsModel();
};
