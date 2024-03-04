#pragma once
#include <stdint.h>
#include <Arduino.h>
#include <inttypes.h>
#include "LW20.h"
//Class defs and global constants go here

//Addresses: I2C, important pins, etc
static const int ADDR_LIDAR = 0x66;
static const int lidar_azimuth = 0;
static const int lidar_elevation = 0;
static const int lidar_deploy = 0;
static const int steer_fr = 0;
static const int steer_fl = 0;
static const int steer_br = 0;
static const int steer_bl = 0;
static const int motor_F = 0;
static const int motor_B = 0;

//Angle parameters: Angle behaviors for LIDAR
static const int INITANGLE = 0;
static const int ENDANGLE = 90;
//retracted and deployed lidar arm angle
static const int RETANGLE = 0;
static const int DEPANGLE = 0;

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
  public:
    void move(int f, int b);
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
    void set_az(uint8_t val) {az = val;}
    void set_el(uint8_t val) {el = val;}
    void set_dp(uint8_t val) {dp = val;}
    void set_fr(uint8_t val) {fr = val;}
    void set_fl(uint8_t val) {fl = val;}
    void set_br(uint8_t val) {br = val;}
    void set_bl(uint8_t val) {bl = val;}
};

class lidarmanager {
  LW20& lidar;
  servocontrol& servos;
  public:
    lidarmanager(LW20& L, servocontrol& s) : lidar(L), servos(s) { }
    pointmap lidarprocess(lidardata raw);
    lidardata scan();
    float testscan();
};

class CMD {
  HardwareSerial& serial;
  lidarmanager& lidar;
  servocontrol& servos;
  motorcontrol& motors;
  //manage commands recieved through serial interface
  public:
    CMD(HardwareSerial& s, lidarmanager& l,
        servocontrol& sc, motorcontrol& m) : serial(s), lidar(l), servos(sc), motors(m) { }
    void run();
};
