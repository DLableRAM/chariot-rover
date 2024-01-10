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

# Classes 

Vector 

    Inherits 

    N/A 

    Public Methods 

    N/A 

    Public Variables 

    Float X, y, z 

    It’s just a nice way to store cartesian points. That’s its only purpose. 

Pointmap 

    Inherits 

    N/A 

    Public Methods 

    N/A 

    Public Variables 

    Vector* map[LAYERCOUNT*LAYERRES] 

    Pointmap postprocess might be offloaded, but it should have enough memory to handle it. Should be a LOT prettier to output than a layer-point matrix. 

IMUdata 

    Inherits 

    N/A 

    Public Methods 

    N/A 

    Public Variables 

    Float Ax, ay, az – 3D acceleration parameters 

    Float Gx, gy gz – 3D orientation parameters 

    NOTE: THIS SHOULD NOT BE USED FOR RAW GYRO OUTPUT, this class is supposed to be a “snapshot” of rover euler parameters 

IMUmanager 

    Inherits 

    lsm6dsoxSensor 

    Public Methods 

    IMUprocess 

    Arguments: N/A 

    Returns: IMUdata 

    Notes: Utilize gyro integration, alpha filter, etc. I’ve written this code before. 

Layer 

    Inherit 

    N/A 

    Public Methods 

    N/A 

    Public Variables 

    Float* distance[LAYERRES] 

LIDARdata 

    Inherit 

    N/A 

    Public Methods 

    N/A 

    Public Variables 

    Layer* scanlayers[LAYERCOUNT] 

LIDARmanager 

    Inherit 

    Lw20 

    Public Methods 

    Scan 

    Arguments: N/A 

    Returns: LIDARdata 

    Notes: Make sure it’s preprocessed, this function SHOULD return a heightmap, NOT a distancemap. Will include some trig. Maybe return layer radius delta? 

    Cartesianprocess 

    Arguments: LIDARdata 

    Returns: pointmap 

    Notes: Turns “raw” LIDAR data into a more useful array of XYZ points. 

    Public Variables 

    N/A 
