#include "APSavegameEditor.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationDomain("odom11.github");
    a.setApplicationName("APSavegameEditor");

    QFile File("StyleSheet.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    a.setStyleSheet(styleSheet);

    APSavegameEditor w;
    w.show();
    return a.exec();
}
