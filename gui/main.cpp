/**
 * Distributed cognitive systems design demo - data analyzer GUI.
 * Simple recurrent network that converges to a stable state
 * in which each of the defined relationships are satisfied.
 * Entry point.
 */
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
