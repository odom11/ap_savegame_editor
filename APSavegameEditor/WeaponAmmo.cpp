#include <algorithm>
#include "WeaponAmmo.h"
#include "SavefileRepository.h";

const std::string AMMO_PREFIX = "AMMO_";
const std::string AMMO_SUFFIX = "_Reserve";

WeaponAmmo::WeaponAmmo(QWidget* parent, const std::string& title, std::vector<std::string>&& ammospecifier)
	: QWidget(parent), title(title)
{
	ui.setupUi(this);
	ui.frame->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	this->ammospecifier = std::move(ammospecifier);
	setTexts(title);
	ui.title->setStyleSheet("font-weight: bold");
	controls.push_back(ui.ammoControl1);
	controls.push_back(ui.ammoControl2);
	controls.push_back(ui.ammoControl3);
	for (auto& control : controls) {
		control->setMinimum(0);
		control->setMaximum(1000);
	}
}

WeaponAmmo::~WeaponAmmo()
{
}

void WeaponAmmo::setTexts(const std::string& title) {
	ui.title->setText(QString::fromStdString(title));
	ui.ammo1->setText(QString::fromStdString(ammospecifier[0]));
	ui.ammo2->setText(QString::fromStdString(ammospecifier[1]));
	ui.ammo3->setText(QString::fromStdString(ammospecifier[2]));
}

void WeaponAmmo::update() {
	for (int i = 0; i < 3; ++i) {
		std::string ammoSearchString = getAmmoSearchKey(ammospecifier[i]);
		int value = SavefileRepository::getInstance().lookForIntValue(ammoSearchString);
		controls[i]->setValue(value);
	}
}

void WeaponAmmo::commit() {
	for (int i = 0; i < 3; ++i) {
		std::string ammoSearchString = getAmmoSearchKey(ammospecifier[i]);
		int value = controls[i]->value();
		SavefileRepository::getInstance().alterIntValue(ammoSearchString, value);
	}
}

std::string WeaponAmmo::getAmmoSearchKey(const std::string& weapon) {
	std::string key;
	if (weapon.length() == 0) {
		key += AMMO_PREFIX + title;
	} else {
		key = AMMO_PREFIX + title + "_";
	}
	key += weapon + AMMO_SUFFIX;
	return key;
}