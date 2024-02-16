#include "defs.hpp"

void CMD::run() {
  int command = serial.parseInt("Enter your command: ");
  switch (command) {
    case 1:
      serial.println("Check command ran...");
      servos.set_az(0);
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
      break;
    default:
      serial.println("Command not recognized.");
  }
}
