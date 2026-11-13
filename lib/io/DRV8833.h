#pragma once
#include <Arduino.h>

class DRV8833Motor {
    public:
        DRV8833Motor(int pinIn1, int pinIn2, int offset, int pinStandBy);

        void start();

        void drive(int speed);

        void drive(int speed, uint32_t durationMs);

        void brake();

    private:
        int _pinIn1;
        int _pinIn2;
        int _offset;
        int _pinStandBy;

        void setStandByHigh();
};