#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_APSavegameEditor.h"
#include "Inventory.h"
#include "Stats.h"

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


    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Stats> stats;
};
