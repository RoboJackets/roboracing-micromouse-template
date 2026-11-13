
#include "DRV8833.h"
#include "cmath"

DRV8833Motor::DRV8833Motor(int pinIn1, int pinIn2, int offset, int pinStandBy)
    : _pinIn1(pinIn1), _pinIn2(pinIn2), _offset(offset >= 0 ? 1 : -1), _pinStandBy(pinStandBy) {
        start();
}

void DRV8833Motor::start() {
    pinMode(_pinIn1, OUTPUT);
    pinMode(_pinIn2, OUTPUT);
    pinMode(_pinStandBy, OUTPUT);
    setStandByHigh();
    digitalWrite(_pinIn1, LOW);
    digitalWrite(_pinIn2, LOW);
}

void DRV8833Motor::setStandByHigh() {
    digitalWrite(_pinStandBy, HIGH);
}

void DRV8833Motor::drive(int speed) {
    speed *= _offset;
    setStandByHigh();

    analogWrite(_pinIn1, 0);
    analogWrite(_pinIn2, 0);
    digitalWrite(_pinIn1, LOW);
    digitalWrite(_pinIn2, LOW);

    if (speed > 0) {
        analogWrite(_pinIn1, std::abs(speed));
        digitalWrite(_pinIn2, LOW);
    } else if (speed < 0) {
        analogWrite(_pinIn2, std::abs(speed));
        digitalWrite(_pinIn1, LOW);
    } else {
        digitalWrite(_pinIn1, LOW);
        digitalWrite(_pinIn2, LOW);
    }
}

void DRV8833Motor::drive(int speed, uint32_t durationMs) {
    drive(speed);
    delay(durationMs);
}

void DRV8833Motor::brake() {
    setStandByHigh();
    analogWrite(_pinIn1, 255);
    analogWrite(_pinIn2, 255);
}