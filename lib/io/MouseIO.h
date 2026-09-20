#pragma once
#include <array>

struct MouseIO {
  virtual ~MouseIO() = default;

  virtual void init() = 0;

  virtual void poll() = 0;

  virtual void setMotorPwm(double left, double right) = 0;

  virtual double leftMeters() const = 0;
  virtual double rightMeters() const = 0;
  virtual double gyroYaw() const = 0;
  virtual const std::array<double, 4> &irMeters() const = 0;

  virtual bool buttonPressed() = 0;
  virtual double now() = 0;
};