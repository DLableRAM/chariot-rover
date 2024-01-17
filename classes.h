#include "consts.h"
#include "LW20-Api/lw20api.h"
#include "Arduino_LSM6DSOX/src/Arduino_LSM6DSOX.h"
class vector {
    //Your purpose is to hold 3 floats. That's it.
    public:
        float x, y, z;
};

class DCM {
    //holds 9 floats, amazing
    public:
        float c1, c2, c3, c4, c5, c6, c7, c8, c9;
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
            /*Originally I was going to include a sophisticated gyroscope integrator,
            until I realized we will not be taking constant readings, rendering it
            entirely useless. So, we'll just read from the accelerometer at standstill
            instead.*/
            //float gx, gy, gz;
            //unsigned long curTime = millis();
            //unsigned long dt = curTime - lastTime;
            if (IMU.gyroscopeAvailable() && IMU.accelerationAvailable()) {
                //IMU.readGyroscope(gx, gy, gz);
                IMU.readAcceleration(IMUd.ax, IMUd.ay, IMUd.az);
            }

            /*float theta_gy = lastThetaY + gy*(static_cast<float>(dt)/1000.0);
            float theta_ay = RAD_TO_DEG*atan2(IMUd.ax,IMUd.az);
            IMUd.gy = ALPHA*theta_gy + (1.0-ALPHA)*theta_ay;
            lastThetaY = IMUd.gy;

            float theta_gx = lastThetaX + gx*(static_cast<float>(dt)/1000.0);
            float theta_ax = RAD_TO_DEG*atan2(IMUd.ay,IMUd.az);
            IMUd.gx = ALPHA*theta_gx + (1.0-ALPHA)*theta_ax;
            lastThetaX = IMUd.gx;

            float theta_gz = lastThetaZ + gz*(static_cast<float>(dt)/1000.0);
            float theta_az = RAD_TO_DEG*atan2(IMUd.ay,IMUd.ax);
            IMUd.gz = ALPHA*theta_gz + (1.0-ALPHA)*theta_az;
            lastThetaZ = IMUd.gz;*/

            IMUd.gy = RAD_TO_DEG*atan2(IMUd.ax,IMUd.az);
            IMUd.gx = RAD_TO_DEG*atan2(IMUd.ay,IMUd.az);
            IMUd.gz = RAD_TO_DEG*atan2(IMUd.ay,IMUd.ax);

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

        pointmap rotate(pointmap raw, DCM d) {
            //rotate pointmap about a DCM
        }
};

class CMD {
    //manage commands recieved through serial interface
}