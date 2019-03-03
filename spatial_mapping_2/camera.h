#ifndef CAMERA_H
#define CAMERA_H

#include <sl/Camera.hpp>
#include <QOpenGLBuffer>

class Camera
{
public:
    Camera();
    ~Camera();
    int open();
    int startMapping();
    int stopMapping();
    int grab(bool *meshIsUpdated);
    std::string getTrackingState();
    std::string getSpatialMappingState();
    sl::Mesh mesh;      // sl::Mesh to hold the mesh generated during spatial mapping

private:
    // ZED camera
    sl::Camera zed;
    // State
    sl::TRACKING_STATE trackingState;
    sl::SPATIAL_MAPPING_STATE spatialMappingState;
    // Parameters
    sl::InitParameters initParameters;
    sl::SpatialMappingParameters spatialMappingParams;
    sl::MeshFilterParameters filterParams;
    bool mappingIsStarted;
    std::chrono::high_resolution_clock::time_point t_last;
};

#endif // CAMERA_H
