#pragma once
#include <array>

#include "DRV8833.h"
#include "IRSensor.h"
#include "MPU6050Gyro.h"
#include "MouseIO.h"

struct TeensyIO : MouseIO {

  // 4 IR sensor format: {emitter_pin, reciever_pin, calibration1, calibration2}
  // I don't know what cal1 cal2 are
  std::array<IRSensor, 4> sensors{IRSensor{0, 0, 0, 0},
                                IRSensor{0, 0, 0, 0},
                                IRSensor{0, 0, 0,0},
                                IRSensor{0, 0, 0,0}};


  MPU6050Gyro gyro;
  double sampledYaw = 0;

  std::array<double, 4> sampledIr{}; // will have the 4 ir values

  // DRV8833Motor(uint8_t in1Pin, uint8_t in2Pin, uint8_t stbyPin)
  DRV8833Motor mLeft = DRV8833Motor(0, 0, 0);
  DRV8833Motor mRight = DRV8833Motor(0, 0, 0);

  void init() override;

  void poll() override;

  void setMotorPwm(double left, double right) override;

  double leftMeters() const override { return 0.0; }
  double rightMeters() const override { return 0.0; }
  double gyroYaw() const override { return sampledYaw; }
  
  std::array<double, 4> ir_{};
  const std::array<double, 4> &irMeters() const override {
    return ir_;
  }

  bool buttonPressed() override;
  double now() override;
};