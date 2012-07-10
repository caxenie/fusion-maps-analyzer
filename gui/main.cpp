#include <QtGui/QApplication>
#include "fusionmapsgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FusionMapsGui w;

    /* show the gui and start main loop */
    w.show();

    return a.exec();
}
