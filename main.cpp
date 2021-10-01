#include "GPSTools.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GPSTools w;
    w.show();
    return a.exec();
}
