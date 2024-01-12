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
};

class pointmap {
    public:
        vector map[LAYERCOUNT*LAYERRES];
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
            IMUdata IMUd;
            float gx, gy, gz;
            unsigned long curTime = millis();
            unsigned long dt = curTime - lastTime;
            if (IMU.gyroscopeAvailable() && IMU.accelerationAvailable()) {
                IMU.readGyroscope(gx, gy, gz);
                IMU.readAcceleration(IMUd.ax, IMUd.ay, IMUd.az);
            }

            float theta_gy = lastThetaY + gy*((float)dt/1000.0);
            float theta_ay = RAD_TO_DEG*atan2(IMUd.ax,IMUd.az);
            IMUd.gy = alpha*theta_gy + (1.0-alpha)*theta_ay;
            lastThetaY = IMUd.gy;

            float theta_gx = lastThetaX + gx*((float)dt/1000.0);
            float theta_ax = RAD_TO_DEG*atan2(IMUd.ay,IMUd.az);
            IMUd.gx = alpha*theta_gx + (1.0-alpha)*theta_ax;
            lastThetaX = IMUd.gx;

            float theta_gz = lastThetaZ + gz*((float)dt/1000.0);
            float theta_az = RAD_TO_DEG*atan2(IMUd.ay,IMUd.ax);
            IMUd.gz = alpha*theta_gz + (1.0-alpha)*theta_az;
            lastThetaZ = IMUd.gz;
            return IMUd;
        }
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