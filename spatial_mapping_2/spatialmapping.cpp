#include "spatialmapping.h"

SpatialMapping::SpatialMapping() :
    glWidget(new GLWidget),
    cameraWidget(new CameraWidget)
{
    glWidget->show();

    connect(cameraWidget, &CameraWidget::updateMesh, glWidget, &GLWidget::setGeometry);
}

SpatialMapping::~SpatialMapping()
{
    delete glWidget;
    delete cameraWidget;
}
