#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_APSavegameEditor.h"
#include "Gadgets.h"
#include "Stats.h"
#include "AmmoTab.h"

class APSavegameEditor : public QMainWindow
{
    Q_OBJECT

public:
    APSavegameEditor(QWidget *parent = Q_NULLPTR);
    const QString SAVEGAME_SUBDIRECTORY = "/Alpha Protocol/Checkpoints";

private:
    Ui::APSavegameEditorClass ui;
    void initializeButtons();
    void initializeTabs();
    void saveCurrentFile();
    void openNewSavefile();
    void resizeTab();
    void handleMissingKeys();


    std::unique_ptr<Gadgets> inventory;
    std::unique_ptr<Stats> stats;
    std::unique_ptr<AmmoTab> ammo;
};
