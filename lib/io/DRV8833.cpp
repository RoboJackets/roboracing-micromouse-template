
#include "DRV8833.h"
#include <cmath>

DRV8833Motor::DRV8833Motor(uint8_t in1Pin, uint8_t in2Pin,
                           uint8_t stbyPin)
    : _in1(in1Pin), _in2(in2Pin), _stby(stbyPin) {
    begin();
}

void DRV8833Motor::begin() {
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_stby, OUTPUT);

    setStandbyHigh_();

    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
}

void DRV8833Motor::setStandbyHigh_() {
    digitalWrite(_stby, HIGH);
}

void DRV8833Motor::drive(int speed) {
    setStandbyHigh_();

    speed = constrain(speed, -255, 255);

    if (speed > 0) {
        analogWrite(_in1, speed);
        digitalWrite(_in2, LOW);
    } else if (speed < 0) {
        digitalWrite(_in1, LOW);
        analogWrite(_in2, abs(speed));
    } else {
        digitalWrite(_in1, LOW);
        digitalWrite(_in2, LOW);
    }
}

void DRV8833Motor::drive(int speed, uint32_t durationMs) {
    drive(speed);
    delay(durationMs);
}

void DRV8833Motor::brake() {
    setStandbyHigh_();
    analogWrite(_in1, 255);
    analogWrite(_in2, 255);
}
