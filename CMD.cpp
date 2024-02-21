#include "defs.hpp"

void CMD::run() {
  int command = serial.parseInt("Enter your command: ");
  int speed;
  const int scancount = 10;
  int i;
  int steer_test[] = {0, 50, 100, 150, 200, 255};
  int speed_test = 0;
  lidardata ldata;
  pointmap pmap;
  switch (command) {
    case 1:
      serial.println("System test command ran...");
      servos.set_dp(DEPANGLE);
      servos.set_az(0);
      servos.activate_pins();
      delay(1000);

      serial.println("Test initial angle...");
      servos.set_el(INITANGLE);
      servos.activate_pins();
      delay(5000);

      serial.println("Test final angle...");
      servos.set_el(ENDANGLE);
      servos.activate_pins();
      delay(5000);

      serial.println("Test LiDAR scan...");
      serial.println(lidar.testscan());
      delay(500);

      serial.println("Test steering...");
      for (i = 0; i < 6; ++i) {
        servos.set_fl(steer_test[i]);
        servos.set_fr(steer_test[i]);
        servos.set_bl(steer_test[i]);
        servos.set_br(steer_test[i]);
        servos.activate_pins();
        delay(500);
      }

      serial.println("Test movement...");
      motors.move(speed_test, 0);
      delay(500);
      motors.move(0, speed_test);
      delay(500);
      motors.move(0, 0);
      serial.println("Test compelte!");
      break;
    case 2:
      serial.println("Performing simple LiDAR test...");
      for (i = 0; i < scancount; ++i) {
        serial.println(lidar.testscan());
      }
      break;
    case 3:
      serial.println("Entering move mode...");
      speed = serial.parseInt("How fast (255 max speed, -255 max reverse): ");
      if (speed >= 0) {
        motors.move(speed, 0);
      } else {
        //abs? set negative? might do the same thing.
        //speed = abs(speed);
        speed = -speed;
        motors.move(0, speed);
      }
      break;
    case 4:
      //steer command, it's going to depend heavily on servo orientation
      //fun!
      break;
    case 5:
      serial.println("Performing scan, please wait.");
      ldata = lidar.scan();
      pmap = lidar.lidarprocess(ldata);
      serial.println("Scan complete!");
      //export options
      break;
    default:
      serial.println("Command not recognized.");
  }
}
