#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QTimerEvent>
#include <QVector3D>
#include <QVector2D>
#include "camera.h"

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    Camera camera;
    int timerIdGrab;
    int timerIdMesh;
    bool meshIsUpdated;

signals:
    void updateMesh(std::vector<sl::float3> *vertices, std::vector<sl::uint3> *triangles, std::vector<sl::float2> *uv, size_t numOfTriangles);
};

#endif // CAMERAWIDGET_H
