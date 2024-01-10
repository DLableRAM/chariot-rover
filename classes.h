#include "consts.h"
class vector {
    //Your purpose is to hold 3 floats. That's it.
    public:
        float x, y, z;
};

class quaternion {
    //holds 4 floats, amazing
    public:
        float q1, q2, q3, q4;
}

class pointmap {
    public:
        vector* map[LAYERCOUNT*LAYERRES];
        //should I malloc this? I'll consider it later
};

class IMUdata {
    public:
        float ax, ay, az;
        //NOTE: DO NOT PUT "RAW" GYRO DATA IN HERE
        //These are supposed to be euler parameters. INTEGRATE GYRO OUTPUT!
        float gx, gy, gz;
};

class IMUmanager {
    //INHERIT LSM6DSOX
    //When I remember to add that dependency, anyway!
    public:
        IMUdata IMUprocess() {
            //integrate gyro, return IMUdata
            //Also include alpha filter
            //uh, I wrote this code before, I'll go find it later
            IMUdata output;
        }
};

class layer {
    public:
        float* distance[LAYERRES];
        float* azimuth[LAYERRES];
        float* elevation[LAYERRES];
};

class lidardata {
    public:
        layer* scanlayers[LAYERCOUNT];
};

class lidarmanager {
    //inherit LW20
    public:
        lidardata scan() {
            //run scan, get distances and angles
        }

        pointmap lidarprocess(lidardata raw) {
            //turn raw lidar data into useful cartesian coordinates
        }

        pointmap rotate(pointmap raw, quaternion q) {
            //rotate pointmap about a quaternion
        }
};