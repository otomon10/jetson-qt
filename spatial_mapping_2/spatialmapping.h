#ifndef SPATIALMAPPING_H
#define SPATIALMAPPING_H

#include <QObject>
#include "camerawidget.h"
#include "glwidget.h"

class SpatialMapping : public QObject
{
    Q_OBJECT

public:
    SpatialMapping();
    ~SpatialMapping();

private:
    GLWidget *glWidget;
    CameraWidget *cameraWidget;
};

#endif // SPATIALMAPPING_H
