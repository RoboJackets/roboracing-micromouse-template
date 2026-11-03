#include "IRSensor.h"

IRSensor::IRSensor(uint8_t emitterPin, uint8_t receiverPin)
    : _emitter(emitterPin), _receiver(receiverPin) {}

void IRSensor::begin() {
  pinMode(_emitter, OUTPUT);
  pinMode(_receiver, INPUT);
}

int IRSensor::read() {
  digitalWrite(_emitter, HIGH);
  delayMicroseconds(300);
  int val = analogRead(_receiver);
  digitalWrite(_emitter, LOW);
  return val;
}