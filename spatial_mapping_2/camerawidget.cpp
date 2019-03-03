#include "camerawidget.h"

#include <QDebug>

CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{
    camera.open();
    camera.startMapping();
    timerIdGrab = startTimer(10);    // grabbing per 10 ms
    timerIdMesh = startTimer(500);   // mesh update per 500 ms
    meshIsUpdated = false;
}

void CameraWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == timerIdGrab)
    {
        camera.grab(&meshIsUpdated);
//        qDebug() << "tracking state: " << camera.getTrackingState().c_str() << "spatial mapping state: " << camera.getSpatialMappingState().c_str() \
                 << " triangles :" << camera.mesh.getNumberOfTriangles() ;
    }
    else if(e->timerId() == timerIdMesh)
    {
        if(meshIsUpdated){
            emit updateMesh(&camera.mesh.vertices, &camera.mesh.triangles, &camera.mesh.uv, camera.mesh.getNumberOfTriangles());
//            qDebug() << "[mesh update] " \
                     << "vert[0]:" << camera.mesh.vertices.data()->x  << camera.mesh.vertices.data()->y  << camera.mesh.vertices.data()->z \
                     << "index[0]:" << camera.mesh.triangles.data()->x  << camera.mesh.triangles.data()->y  << camera.mesh.triangles.data()->z \
                     << ": num of vertices = " << camera.mesh.vertices.size() \
                     << ": num of index = " << camera.mesh.triangles.size();
            meshIsUpdated = false;
        }
    }
}
