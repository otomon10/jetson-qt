#include "camera.h"

Camera::Camera()
{
    // Init parameters
    initParameters.depth_mode = sl::DEPTH_MODE_PERFORMANCE; // Use QUALITY depth mode to improve mapping results
    initParameters.coordinate_units = sl::UNIT_METER;
    initParameters.coordinate_system = sl::COORDINATE_SYSTEM_RIGHT_HANDED_Y_UP; // OpenGL coordinates system

    // Spatial mapping parameters
    spatialMappingParams.range_meter = sl::SpatialMappingParameters::get(sl::SpatialMappingParameters::MAPPING_RANGE_FAR);
    spatialMappingParams.resolution_meter = sl::SpatialMappingParameters::get(sl::SpatialMappingParameters::MAPPING_RESOLUTION_LOW);
    spatialMappingParams.save_texture = false;
    spatialMappingParams.max_memory_usage = 2048;

    // Filter parameters
    filterParams.set(sl::MeshFilterParameters::MESH_FILTER_LOW);
}

Camera::~Camera()
{
    zed.close();
}

int Camera::open()
{
    sl::ERROR_CODE err = zed.open(initParameters);
    if (err != sl::ERROR_CODE::SUCCESS) {
        return -1;
    }
    return 0;
}

int Camera::startMapping()
{
    if(!zed.isOpened()) return -1;

    zed.enableTracking();
    zed.enableSpatialMapping(spatialMappingParams);

    /*****************************************************************************************************/
    /* [WORKAROUND]                                                                                      */
    /* In the case of JetsonTX1, Spatial mapping cannot be enabled unless it is called multiple times.   */
    /*****************************************************************************************************/
    spatialMappingState = zed.getSpatialMappingState();
    int retly = 0;
    while(spatialMappingState == sl::SPATIAL_MAPPING_STATE_NOT_ENABLED){
        std::cout << "enabling spatial mapping... " << sl::toString(spatialMappingState) << std::endl;
        zed.enableSpatialMapping(spatialMappingParams);
        zed.grab();
        usleep(1000);
        spatialMappingState = zed.getSpatialMappingState();
        retly++;
        if(50 < retly){
            return -1;
        }
    }
    retly = 0;
    while(spatialMappingState == sl::SPATIAL_MAPPING_STATE_INITIALIZING){
        std::cout << "initializing spatial mapping... " << sl::toString(spatialMappingState) << std::endl;
        zed.grab();
        usleep(1000);
        spatialMappingState = zed.getSpatialMappingState();
        retly++;
        if(50 < retly){
            return -1;
        }
    }
    return 0;
}

int Camera::stopMapping()
{
    if(!zed.isOpened()) return -1;

    sl::Mesh wholeMesh;
    zed.extractWholeMesh(wholeMesh);

    wholeMesh.filter(filterParams);

    if (spatialMappingParams.save_texture) {
        wholeMesh.applyTexture(sl::MESH_TEXTURE_RGB);
    }

    std::string saveName = + "mesh_gen.obj";
    bool t = wholeMesh.save(saveName.c_str());
    if (t) std::cout << ">> Mesh has been saved under " << saveName << std::endl;
    else std::cout << ">> Failed to save the mesh under  " << saveName << std::endl;

    return 0;
}

int Camera::grab()
{
    if(!zed.isOpened()) return -1;

    sl::ERROR_CODE err = zed.grab();
    if (err != sl::ERROR_CODE::SUCCESS) {
        return -1;
    }
    return 0;
}

std::string Camera::getTrackingState()
{
    if(!zed.isOpened()) return nullptr;

    sl::Pose pose;
    trackingState = zed.getPosition(pose);
    return sl::toString(trackingState).c_str();
}

std::string Camera::getSpatialMappingState()
{
    if(!zed.isOpened()) return nullptr;

    spatialMappingState = zed.getSpatialMappingState();
    return sl::toString(spatialMappingState).c_str();
}

