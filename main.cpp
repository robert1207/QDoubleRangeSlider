#include "qdoublerangesliderdemodialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDoubleRangeSliderDemoDialog w;
    w.show();
    return a.exec();
}
