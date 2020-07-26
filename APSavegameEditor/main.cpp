#include "APSavegameEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationDomain("odom11.github");
    a.setApplicationName("APSavegameEditor");
    APSavegameEditor w;
    w.show();
    return a.exec();
}
