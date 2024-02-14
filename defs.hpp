#pragma once
#include "LW20-Api/Arduino/source/LW20.cpp"
//Class defs and global constants go here

//Addresses: I2C, important pins, etc
static const int ADDR_LIDAR = 0x66;
/*static const int lidar_azimuth;
static const int lidar_elevation;
static const int lidar_deploy;
static const int steer_fr;
static const int steer_fl;
static const int steer_br;
static const int steer_bl;*/

//Angle parameters: Angle behaviors for LIDAR
static const int INITANGLE = 0;
static const int ENDANGLE = 90;

static const int LAYERCOUNT = 255;
static const int LAYERRES = ENDANGLE-INITANGLE;

class vector {
    //Your purpose is to hold 3 floats. That's it.
    public:
      float x, y, z;
};

class pointmap {
    public:
      vector map[LAYERCOUNT*LAYERRES];
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

class motorcontrol {
  //mobility controller
};

class servocontrol {
  uint8_t az;
  uint8_t el;
  uint8_t dp;
  uint8_t fr;
  uint8_t fl;
  uint8_t br;
  uint8_t bl;
  //servo controller
  public:
    void activate_pins();
    void set_az(uint8_t val);
    void set_el(uint8_t val);
    void set_dp(uint8_t val);
    void set_fr(uint8_t val);
    void set_fl(uint8_t val);
    void set_br(uint8_t val);
    void set_bl(uint8_t val);
};

class lidarmanager {
  //LW20& lidar;

  public:
    //lidarmanager(LW20& L);
    pointmap lidarprocess(lidardata raw);
    lidardata scan(LW20& lidar, servocontrol& servos);
};

class CMD {
    //manage commands recieved through serial interface
};
