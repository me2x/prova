#include <QtGui/QApplication>
#include "provaGui.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    provaGui provagui;
    provagui.show();
    return app.exec();
}
