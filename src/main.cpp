#include <Arduino.h>

#include "StateMachine.h"
#include "robot/Robot.h"
#include "TeensyIO.h"

TeensyIO mouseIO{};
Robot robot{mouseIO};
StateMachine mouse{};

const int mosfetPin = 33;
const int recieverPin = 19;

int ambientLight = 0;
int reflectedLight = 0;
int distanceValue = 0;

void setup() {
  pinMode(mosfetPin, OUTPUT);
  pinMode(recieverPin, INPUT);
}

void loop() {
  digitalWrite(mosfetPin, LOW);
  delayMicroseconds(50);
  ambientLight = analogRead(recieverPin);

  digitalWrite(mosfetPin, HIGH);
  delayMicroseconds(50);
  
  reflectedLight = analogRead(recieverPin);

  digitalWrite(mosfetPin, LOW);

  distanceValue = ambientLight - reflectedLight;

  Serial.print("Reflection Intensity: ");
  Serial.println(abs(distanceValue));
}