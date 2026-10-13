#include <Arduino.h>

const int emitterPin = 33;
const int sensorPin = A14;  // Teensy pin 38

void setup() {
  pinMode(emitterPin, OUTPUT);
  digitalWrite(emitterPin, LOW);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(emitterPin, HIGH);
  delayMicroseconds(300);

  int sensorValue = analogRead(sensorPin);

  digitalWrite(emitterPin, LOW);
  Serial.println(sensorValue);
  delay(100);
}
