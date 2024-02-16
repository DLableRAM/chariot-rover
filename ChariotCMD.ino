#include <wire.h>
#include "lmanager.cpp"
#include "smanager.cpp"
#include "CMD.cpp"
#include "mmanager.cpp"

LW20 lw20(Serial1, 115200);

void setup() 
{
    //TODO: Better error checking on startup.
    // Start serial monitor port.
    Serial.begin(115200);
    while(!serial);

    // Setup LW20.
    lw20.init();

    // Basic Setup.
    lw20.setLaserParams(LWMS_48);
    servocontrol serv();
    lidarmanager lidar(lw20, serv);
    motorcontrol motors();

    CMD CMD(Serial, lidar, serv, motors);
}

void loop() 
{
  CMD.run();
}
