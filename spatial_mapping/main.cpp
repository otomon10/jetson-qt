#include "camera.h"

int main(int argc, char** argv) {

    Camera camera;

    camera.open();
    camera.startMapping();

    int loop = 0;
    while(loop < 500){
        camera.grab();
        std::cout << loop \
                  << " : tracking state : " << camera.getTrackingState() \
                  << " : spatial mapping state : " << camera.getSpatialMappingState() \
                  << std::endl;
        loop++;
    }

    camera.stopMapping();

    return 0;
}
