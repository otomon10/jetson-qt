#include <QApplication>
#include "spatialmapping.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SpatialMapping spatialMapping;
    return app.exec();
}
