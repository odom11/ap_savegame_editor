#include <QDebug>
#include "SavefileRepository.h"
#include "Stats.h"

const std::string REMAINING_STATPOINTS_KEY = "AdvancementPoints";
const std::string MONEY = "Money";

Stats::Stats(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initializeFreeStatpoints();
}

Stats::~Stats()
{
}

void Stats::commit() {
	auto remainingStatpoints = ui.freeStatpointsValue->value();
	SavefileRepository::getInstance().alterValue(REMAINING_STATPOINTS_KEY, static_cast<std::byte>(remainingStatpoints));

	auto money = ui.moneyValue->value();
	SavefileRepository::getInstance().alterIntValue(MONEY, money);


	qDebug() << "committing stats: " << remainingStatpoints;
}

void Stats::update() {
	std::byte remainingStatpoints = SavefileRepository::getInstance().lookForValue(REMAINING_STATPOINTS_KEY);
	ui.freeStatpointsValue->setValue(static_cast<unsigned int>(remainingStatpoints));

	int money = SavefileRepository::getInstance().lookForIntValue(MONEY);
	ui.moneyValue->setValue(money);
	qDebug() << "setting value";
}

void Stats::initializeFreeStatpoints() {
	ui.freeStatpointsLabel->setText("unusedStatpoints");
	ui.freeStatpointsValue->setValue(0);
	ui.freeStatpointsValue->setMaximum(255);
	ui.freeStatpointsValue->setMinimum(0);

	ui.moneyLabel->setText("money");
	ui.moneyValue->setValue(0);
	ui.moneyValue->setMaximum(10000000);
}