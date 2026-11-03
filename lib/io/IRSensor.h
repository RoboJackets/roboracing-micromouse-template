#pragma once
#include <Arduino.h>

class IRSensor {
public:
  IRSensor(uint8_t emitterPin, uint8_t receiverPin);
  void begin();
  int read();

private:
  uint8_t _emitter, _receiver;
};