#ifndef CAMERA_H
#define CAMERA_H

#include <sl/Camera.hpp>

class Camera
{
public:
    Camera();
    ~Camera();
    int open();
    int startMapping();
    int stopMapping();
    int grab();
    std::string getTrackingState();
    std::string getSpatialMappingState();

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

    bool enabled;
};

#endif // CAMERA_H
