# spatial_mapping
ZEDの空間マッピングのサンプルをJetsonTX1、Qtで実装する例。
[こちらのサンプル](https://github.com/stereolabs/zed-examples/tree/master/spatial%20mapping)を参考にしている。

# enableSpatialMappingの有効化について

JetsonTX1の場合、enableSpatialMapping()を1度コールしても有効にならなかった。
有効になるまで複数回呼び出す回避策をとっている。

```cpp
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
```
