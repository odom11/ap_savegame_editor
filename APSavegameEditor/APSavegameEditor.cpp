#include "APSavegameEditor.h"
#include <qstyle.h>
#include <QDebug>
#include <QWidget>
#include <iostream>

APSavegameEditor::APSavegameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initializeButtons();
}

void APSavegameEditor::initializeButtons() {
    ui.closeButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    ui.openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui.saveButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));

    connect(ui.openButton, &QToolButton::clicked, this, &APSavegameEditor::openNewSavefile);
    connect(ui.saveButton, &QToolButton::clicked, this, &APSavegameEditor::saveCurrentFile);
    connect(ui.closeButton, &QToolButton::clicked, this, &QApplication::quit);
}

void APSavegameEditor::openNewSavefile() {
    qDebug() << "opening savefile";
    ui.openButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
}

void APSavegameEditor::saveCurrentFile() {
    qDebug() << "saving file";
}
