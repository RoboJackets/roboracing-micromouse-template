#pragma once
#include <LSM6DSV16BXSensor.h>

#include "Gyro.h"
#include "Wire.h"

struct LSM6DSV16BGyro : Gyro {
  LSM6DSV16BXSensor imu{&Wire, LSM6DSV16BX_I2C_ADD_L};
  bool ready = false;

  void initializeGyro() override;
  bool update() override;
};