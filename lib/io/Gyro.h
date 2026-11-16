#pragma once

struct Gyro {
  float ypr[3] = {0, 0, 0};

  virtual ~Gyro() = default;

  virtual void initializeGyro() = 0;

  virtual bool update() = 0;
};