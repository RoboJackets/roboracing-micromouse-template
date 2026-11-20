#pragma once
#include <array>

#include "Constants.h"
#include "DRV8833.h"
#include "IRSensor.h"
#include "MPU6050Gyro.h"
#include "MouseIO.h"
#include "Pins.h"

struct TeensyIO : MouseIO {
  // Calibration (a, b) for sensor 1 is the example robot's. Recalibrate ours.
  std::array<IRSensor, 4> sensors{IRSensor{EMIT_1, RECV_1, 0.968202, 0.500721},
                                  IRSensor{EMIT_2, RECV_2, 0, 0},
                                  IRSensor{EMIT_3, RECV_3, 0, 0},
                                  IRSensor{EMIT_4, RECV_4, 0, 0}};

  MPU6050Gyro gyro{};

  uint32_t lastMicros = 0;
  uint64_t microsAccum = 0;

  double sampledYaw = 0;
  std::array<double, 4> sampledIr{};

  DRV8833Motor mLeft = DRV8833Motor(AIN1, AIN2, 1, STBY);
  DRV8833Motor mRight = DRV8833Motor(BIN1, BIN2, 1, STBY);

  void init() override;

  void poll() override;

  void setMotorPwm(double left, double right) override;

  // No encoders on our motors yet.
  double leftMeters() const override { return 0.0; }
  double rightMeters() const override { return 0.0; }
  double gyroYaw() const override { return sampledYaw; }
  const std::array<double, 4> &irMeters() const override { return sampledIr; }

  bool buttonPressed() override;
  double now() override;
  int printf(const char *, ...) override;
};
