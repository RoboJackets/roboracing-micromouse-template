#pragma once
#include <Arduino.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

struct Gyro {
  MPU6050 mpu;
  bool dmpReady = false;
  uint8_t devStatus = 0;
  uint16_t packetSize = 0;
  uint8_t fifoBuffer[64];

  float ypr[3] = {0, 0, 0};
  Quaternion q;
  VectorFloat gravity;
  elapsedMicros timer;

  void initializeGyro();
  bool update();
};