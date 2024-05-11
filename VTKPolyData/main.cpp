#include "VTKPolyData.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VTKPolyData w;
    w.show();
    return a.exec();
}
