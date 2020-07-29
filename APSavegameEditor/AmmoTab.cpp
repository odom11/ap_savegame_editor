
#include <QDebug>

#include "AmmoTab.h"

AmmoTab::AmmoTab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initializeWeapons();
}

AmmoTab::~AmmoTab()
{
}

void AmmoTab::initializeWeapons() {
	//auto pistol = std::make_unique<WeaponAmmo>(this, "Pistol", std::vector<std::string>{"foo", "bar", "spam"});
	weapons.push_back(std::make_unique<WeaponAmmo>(this, "PISTOL", std::vector<std::string>{"AUTO", "TRANQUILIZER", "STEEL_CORE"}));
	weapons.push_back(std::make_unique<WeaponAmmo>(this, "SMG", std::vector<std::string>{"", "HOLLOW_POINT", "HIGH_VELOCITY"}));
	weapons.push_back(std::make_unique<WeaponAmmo>(this, "SHOTGUN", std::vector<std::string>{"", "FLECHETTE", "PHOSPHOR"}));
	weapons.push_back(std::make_unique<WeaponAmmo>(this, "ASSAULT_RIFLE", std::vector<std::string>{"", "APDS", "SUBSONIC"}));
	for (int row = 0; row < 2; ++row) {
		for (int col = 0; col < 2; ++col) {
			ui.gridLayout->addWidget(weapons[2*row + col].get(), row, col);
		}
	}
}

void AmmoTab::update() {
	for (auto& ptr : weapons) {
		ptr->update();
	}
}

void AmmoTab::commit() {
	for (auto& ptr : weapons) {
		ptr->commit();
	}
}