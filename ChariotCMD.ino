//#include <wire.h>
#include "defs.hpp"

//UART Serial1(tx, rx, 0, 0)
LW20 lw20(Serial1, 115200);

void setup() 
{
    //TODO: Better error checking on startup.
    // Start serial monitor port.
    Serial.begin(115200);
    while(!Serial);
    Serial1.begin(115200);
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
  //check emergency shutoff
  if (!Serial) {
    motors.move(0, 0);
    serv.set_dp(RETANGLE);
    serv.activate_pins();
    //possibly break from program? might be safer.
    //break;
    while(!Serial);
  }
  CMD.run();
}
