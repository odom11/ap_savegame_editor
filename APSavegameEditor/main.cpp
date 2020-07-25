#include "APSavegameEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    APSavegameEditor w;
    w.show();
    return a.exec();
}
