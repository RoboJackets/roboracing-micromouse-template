#pragma once
#include <array>

#include "MouseIO.h"
#include "DRV8833.h"
#include "IRSensor.h"
#include "Pins.h"
#include "Constants.h"
#include "Gyro.h"
#include "EncoderSensor.h"

struct TeensyIO : MouseIO {

  std::array<IRSensor, 4> irSensors = {
      IRSensor{emit1, recv1, 0.0, 0.0},
      IRSensor{emit2, recv2, 0.0, 0.0},
      IRSensor{emit3, recv3, 0.0, 0.0},
      IRSensor{emit4, recv4, 0.0, 0.0}
  };

  EncoderSensor leftEncoder{aCoder_A, aCoder_B, 0, true};
  EncoderSensor rightEncoder{bCoder_A, bCoder_B, 0, false};

  Gyro gyro;

  uint32_t lastMicros = 0;
  uint64_t microsAccum = 0;

  DRV8833Motor leftMotor{ApinIn1, ApinIn2, 1, pinStandBy};
  DRV8833Motor rightMotor{BpinIn1, BpinIn2, 1, pinStandBy};

  double sampYaw = 0.0;
  double leftDistance = 0.0;
  double rightDistance = 0.0;
  std::array<double, 4> irDistances{};


  void init() override;

  void poll() override;

  void setMotorPwm(double left, double right) override;

  double leftMeters() const override { return 0.0; }
  double rightMeters() const override { return 0.0; }
  double gyroYaw() const override { return 0.0; }
  
  const std::array<double, 4> &irMeters() const override { 
    return irDistances;
  }

  bool buttonPressed() override;
  double now() override;
  int printf(const char *, ...);
};