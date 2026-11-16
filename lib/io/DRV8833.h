#pragma once
#include <Arduino.h>

class DRV8833Motor {
public:
    DRV8833Motor(uint8_t in1Pin, uint8_t in2Pin, uint8_t stbyPin);

    void begin();
    void drive(int speed);
    void drive(int speed, uint32_t durationMs);
    void brake();

private:
    uint8_t _in1;
    uint8_t _in2;
    uint8_t _stby;

    void setStandbyHigh_();
};