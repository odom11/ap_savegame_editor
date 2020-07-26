#include <iostream>

#include <QStyle>
#include <QDebug>
#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>

#include "APSavegameEditor.h"
#include "Inventory.h"

APSavegameEditor::APSavegameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initializeButtons();
    initializeTabs();
}

void APSavegameEditor::initializeButtons() {
    ui.closeButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    ui.closeButton->setToolTip(tr("close application"));
    ui.openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui.openButton->setToolTip(tr("load a save file"));
    ui.saveButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui.saveButton->setToolTip(tr("save changes to savefile (creates a backup file)"));

    connect(ui.openButton, &QToolButton::clicked, this, &APSavegameEditor::openNewSavefile);
    connect(ui.saveButton, &QToolButton::clicked, this, &APSavegameEditor::saveCurrentFile);
    connect(ui.closeButton, &QToolButton::clicked, this, &QApplication::quit);
}

void APSavegameEditor::openNewSavefile() {
    qDebug() << "opening savefile";
    QString documents = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString apPath = documents + SAVEGAME_SUBDIRECTORY;
    QString filename = QFileDialog::getOpenFileName(this, "open save file", apPath, "save files (*.SAV) ;; all files (*.*)");
    qDebug() << "opened filename: " << filename;
}

void APSavegameEditor::saveCurrentFile() {
    qDebug() << "saving file";
    stats->commit();
    inventory->commit();
}

void APSavegameEditor::initializeTabs() {
    ui.tabWidget->clear();
    ui.tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    stats = std::make_unique<Stats>(this);
    ui.tabWidget->addTab(stats.get(), "stats");

    inventory = std::make_unique<Inventory>(this);
    ui.tabWidget->addTab(inventory.get(), "inventory");
    //ui.tabWidget->resize(inventory->minimumSize());
    //connect(ui.tabWidget, &QTabWidget::tabBarClicked, this, &APSavegameEditor::resizeTab);
    //resizeTab();
}

void APSavegameEditor::resizeTab() {
    const QSize tabsize = ui.tabWidget->size();
    ui.tabWidget->setMinimumSize(tabsize);
    ui.tabWidget->resize(tabsize);
    qDebug() << "current tab size: " << tabsize;
    qDebug() << "hello world";
    qDebug() << "this is a resizer";
}