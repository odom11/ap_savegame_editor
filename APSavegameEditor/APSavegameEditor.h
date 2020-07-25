#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_APSavegameEditor.h"

class APSavegameEditor : public QMainWindow
{
    Q_OBJECT

public:
    APSavegameEditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::APSavegameEditorClass ui;
    void initializeButtons();
    void initializeTabs();
    void saveCurrentFile();
    void openNewSavefile();
private slots:



};
