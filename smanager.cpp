#include "defs.hpp"

void servocontrol::activate_pins() {
  analogWrite(lidar_azimuth, az);
  analogWrite(lidar_elevation, el);
  analogWrite(lidar_deploy, dp);
  analogWrite(steer_fr, fr);
  analogWrite(steer_fl, fl);
  analogWrite(steer_br, br);
  analogWrite(steer_bl, bl);
}
