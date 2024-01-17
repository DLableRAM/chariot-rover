#include "consts.h"
#include "LW20-Api/Arduino/source/LW20.h"
class vector {
    //Your purpose is to hold 3 floats. That's it.
    public:
        float x, y, z;
};

class pointmap {
    public:
        vector map[LAYERCOUNT*LAYERRES];
        //should I malloc this? I'll consider it later
};

class layer {
    public:
        float distance[LAYERRES];
        float azimuth[LAYERRES];
        float elevation[LAYERRES];
};

class lidardata {
    public:
        layer scanlayers[LAYERCOUNT];
};

class lidarmanager : protected LW20 {
    //inherit LW20
    public:
        lidardata scan() {
            //run scan, get distances and angles
        }

        pointmap lidarprocess(lidardata raw) {
            //turn raw lidar data into useful cartesian coordinates
            pointmap output;
            int i;
            int j;
            for (i = 0; i < LAYERCOUNT; ++i) {
                for (j = 0; j < LAYERRES; ++j) {
                    output.map[j * (i + 1)].x = raw.scanlayers[i].distance[j] * cos(DEG_TO_RAD * raw.scanlayers[i].azimuth[j]);
                    output.map[j * (i + 1)].y = raw.scanlayers[i].distance[j] * sin(DEG_TO_RAD * raw.scanlayers[i].azimuth[j]);
                    output.map[j * (i + 1)].z = raw.scanlayers[i].distance[j] * sin(DEG_TO_RAD * raw.scanlayers[i].elevation[j]);
                } 
            }
            return output;
        }
};

class motorcontrol {
    //mobility controller
};

class CMD {
    //manage commands recieved through serial interface
};