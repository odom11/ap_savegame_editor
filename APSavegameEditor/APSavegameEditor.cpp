#include <iostream>

#include <QStyle>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>

#include "SavefileRepository.h"

#include "APSavegameEditor.h"
#include "Gadgets.h"

APSavegameEditor::APSavegameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initializeButtons();
    initializeTabs();
}

void APSavegameEditor::initializeButtons() {
    ui.actionopen->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    connect(ui.actionopen, &QAction::triggered, this, &APSavegameEditor::openNewSavefile);

    ui.actionsave->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    connect(ui.actionsave, &QAction::triggered, this, &APSavegameEditor::saveCurrentFile);

    ui.actionexit->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    connect(ui.actionexit, &QAction::triggered, this, &QApplication::quit);
}
	
	void APSavegameEditor::openNewSavefile() {
    qDebug() << "opening savefile";
    QString documents = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString apPath = documents + SAVEGAME_SUBDIRECTORY;
    QString filename = QFileDialog::getOpenFileName(this, "open save file", apPath, "save files (*.SAV) ;; all files (*.*)");
    bool success = false;
    if (!filename.isEmpty()) {
        SavefileRepository& repo = SavefileRepository::getInstance();
        success = repo.readdata(filename.toUtf8().constData());
    }
    if (!success) {
        qDebug() << "could not read any data";
        return;
    }
    stats->update();
    inventory->update();
    ammo->update();

    qDebug() << "opened filename: " << filename;
}

void APSavegameEditor::saveCurrentFile() {
    qDebug() << "saving file";
    stats->commit();
    inventory->commit();
    ammo->commit();
    SavefileRepository::getInstance().commit();
}

void APSavegameEditor::initializeTabs() {
    ui.tabWidget->clear();
    ui.tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    stats = std::make_unique<Stats>(this);
    ui.tabWidget->addTab(stats.get(), "stats");

    inventory = std::make_unique<Gadgets>(this);
    ui.tabWidget->addTab(inventory.get(), "gadgets");

    ammo = std::make_unique<AmmoTab>(this);
    ui.tabWidget->addTab(ammo.get(), "ammo");
}

void APSavegameEditor::resizeTab() {
    const QSize tabsize = ui.tabWidget->size();
    ui.tabWidget->setMinimumSize(tabsize);
    ui.tabWidget->resize(tabsize);
    qDebug() << "current tab size: " << tabsize;
    qDebug() << "hello world";
    qDebug() << "this is a resizer";
}

