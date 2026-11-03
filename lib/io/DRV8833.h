#pragma once
#include <Arduino.h>

class DRV8833Motor {
public:
  DRV8833Motor(uint8_t in1Pin, uint8_t in2Pin, int8_t offset, uint8_t stbyPin);

  void begin();

  void drive(int speed);

  void drive(int speed, uint32_t durationMs);
  void brake();

private:
  uint8_t _in1, _in2, _stby;
  int8_t _offset;

  void setStandbyHigh_();
};
