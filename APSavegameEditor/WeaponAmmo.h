#pragma once
#include <string>
#include <vector>

#include <QWidget>
#include <QSpinBox>

#include "ui_WeaponAmmo.h"

class WeaponAmmo : public QWidget
{
	Q_OBJECT

public:
	WeaponAmmo(QWidget *parent, const std::string& title, std::vector<std::string>&& ammospecifier);
	~WeaponAmmo();
	void update();
	void commit();

private:
	Ui::WeaponAmmo ui;
	std::vector<std::string> ammospecifier;
	std::vector<QSpinBox*> controls;
	void setTexts(const std::string& title);
	std::string getAmmoSearchKey(const std::string& weapon);
	const std::string title;
};
