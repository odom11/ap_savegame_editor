#pragma once
#include <vector>

#include <QWidget>

#include "ui_AmmoTab.h"
#include "WeaponAmmo.h"

class AmmoTab : public QWidget
{
	Q_OBJECT

public:
	AmmoTab(QWidget* parent = Q_NULLPTR);
	~AmmoTab();

	void update();
	void commit();

private:
	Ui::AmmoTab ui;
	void initializeWeapons();
	std::vector<std::unique_ptr<WeaponAmmo>> weapons{};
	//std::unique_ptr<WeaponAmmo> pistol;
};
