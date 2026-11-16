
#include "IRSensor.h"
#include <Arduino.h>

void IRSensor::begin() {
    pinMode(EMIT, OUTPUT);
    pinMode(RECV, INPUT);

    digitalWrite(EMIT, LOW);
}

int IRSensor::readPost() const {
    digitalWrite(EMIT, LOW);
    delayMicroseconds(200);
    int ambient = analogRead(RECV);

    digitalWrite(EMIT, HIGH);
    delayMicroseconds(200);
    int illuminated = analogRead(RECV);

    digitalWrite(EMIT, LOW);

    int signal = illuminated - ambient;

    return signal > 0 ? signal : 0;
}
