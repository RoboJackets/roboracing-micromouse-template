#pragma once
#include <array>

#include "MouseIO.h"

struct TeensyIO : MouseIO {
  void init() override;

  void poll() override;

  void setMotorPwm(double left, double right) override;

  double leftMeters() const override { return 0.0; }
  double rightMeters() const override { return 0.0; }
  double gyroYaw() const override { return 0.0; }
  
  const std::array<double, 4> &irMeters() const override { 
    return {
        0.0, 0.0, 0.0, 0.0
    };
  }

  bool buttonPressed() override;
  double now() override;
};