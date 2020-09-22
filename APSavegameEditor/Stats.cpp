#include <QDebug>
#include "SavefileRepository.h"
#include "Stats.h"

const std::string REMAINING_STATPOINTS_KEY = "AdvancementPoints";
const std::string SUAVE_CHOSEN_KEY = "TotalTimesSuaveChosen";
const std::string AGGR_CHOSEN_KEY = "TotalTimesAgressiveChosen";
const std::string PROF_CHOSEN_KEY = "TotalTimesProfessionalChosen";
const std::string MONEY = "Money";
const int BOX_STYLE = QFrame::WinPanel | QFrame::Raised;

Stats::Stats(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initializeGeneral();
	initializeDialog();
}

Stats::~Stats()
{
}

void Stats::commit() {
	auto remainingStatpoints = ui.freeStatpointsValue->value();
	SavefileRepository::getInstance().alterValue(REMAINING_STATPOINTS_KEY, static_cast<std::byte>(remainingStatpoints));

	auto money = ui.moneyValue->value();
	SavefileRepository::getInstance().alterIntValue(MONEY, money);

	auto suaveChosen = ui.suaveChosenValue->value();
	SavefileRepository::getInstance().alterIntValue(SUAVE_CHOSEN_KEY, suaveChosen);

	auto aggressive = ui.aggrChosenValue->value();
	SavefileRepository::getInstance().alterIntValue(AGGR_CHOSEN_KEY, aggressive);

	auto profChosen = ui.profChosenValue->value();
	SavefileRepository::getInstance().alterIntValue(PROF_CHOSEN_KEY, profChosen);

	qDebug() << "committing stats: " << remainingStatpoints;
}

void Stats::update() {
	std::byte remainingStatpoints = SavefileRepository::getInstance().lookForValue(REMAINING_STATPOINTS_KEY);
	ui.freeStatpointsValue->setValue(static_cast<unsigned int>(remainingStatpoints));

	int money = SavefileRepository::getInstance().lookForIntValue(MONEY);
	ui.moneyValue->setValue(money);
	qDebug() << "setting value";

	int suaveChosen = SavefileRepository::getInstance().lookForIntValue(SUAVE_CHOSEN_KEY);
	ui.suaveChosenValue->setValue(suaveChosen);

	int professionalChosen = SavefileRepository::getInstance().lookForIntValue(PROF_CHOSEN_KEY);
	ui.profChosenValue->setValue(professionalChosen);

	int aggressiveChosen = SavefileRepository::getInstance().lookForIntValue(AGGR_CHOSEN_KEY);
	ui.aggrChosenValue->setValue(aggressiveChosen);
}

void Stats::initializeGeneral() {
	ui.generalFrame->setFrameStyle(BOX_STYLE);
	ui.generalLabel->setText("general");
	ui.generalLabel->setStyleSheet("font-weight: bold");
	ui.freeStatpointsLabel->setText("unused statpoints");
	ui.freeStatpointsValue->setValue(0);
	ui.freeStatpointsValue->setMaximum(255);
	ui.freeStatpointsValue->setMinimum(0);
	ui.freeStatpointsLabel->resize(ui.freeStatpointsLabel->minimumSizeHint());

	ui.moneyLabel->setText("money");
	ui.moneyValue->setValue(0);
	ui.moneyValue->setMaximum(100000000);
}

void Stats::initializeDialog()
{
	ui.dialogFrame->setFrameStyle(BOX_STYLE);
	ui.dialogLabel->setText("dialog options \n(suave > other\nrequired to kill Marburg\nin Rome)");
	ui.dialogLabel->setStyleSheet("font-weight: bold");
	ui.suaveChosenLabel->setText("suave chosen");

	ui.suaveChosenValue->setMinimum(0);
	ui.suaveChosenValue->setMaximum(10000);

	ui.aggrChosenLabel->setText("aggressive chosen");
	ui.aggrChosenValue->setMinimum(0);
	ui.aggrChosenValue->setMaximum(10000);

	ui.profChosenLabel->setText("professional chosen");
	ui.profChosenValue->setMinimum(0);
	ui.profChosenValue->setMaximum(10000);
}
