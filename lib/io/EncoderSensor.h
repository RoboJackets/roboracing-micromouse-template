#pragma once
#include <cmath>
#include <cstdint>

#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include "Constants.h"
#include "Types.h"

struct EncoderSensor {
  Encoder encoder;
  bool flipped;

  EncoderSensor(uint8_t pinA, uint8_t pinB, long initialCount, bool flipped)
      : encoder(pinA, pinB), flipped(flipped) {
    encoder.write(initialCount);
  }

  double getPosition() {
    long counts = flipped ? -encoder.read() : encoder.read();
    // Serial.println(encoder.read());
    return counts * (2.0 * M_PI * WHEEL_RADIUS_M / COUNTS_PER_WHEEL_REV);
  }
};