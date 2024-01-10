# chariot-rover
Chariot moon rover control system, for ERAU capstone project.

# Libraries 

The Chariot control system utilizes the following libraries: 

    LW20 API (LIDAR) 

    LSM6DSOX (Accelerometer/gyro) 

Components 

    Raspberry Pi Pico 

    Microcontroller board 

    LW20 LIDAR 

    Interface: I2C 

    Address: 0x66 

    LSM6DSOX 

    Interface: I2C 

    Address: 0x6A 

# Constants 

LAYERCOUNT 

    Int 

    Number of layers that the LIDAR will measure. 

LAYERRES 

    Int 

    Number of sample points per layer, aka layer resolution 

INITANGLE 

    Int (maybe implicit cast as float?) 

    Starting vertical angle for the LIDAR scan 

ENDANGLE 

    Int (also maybe cast as float) 

    Final vertical angle for LIDAR scan, should be tuned to avoid rover body shadow 

    Body shadow creates junk data