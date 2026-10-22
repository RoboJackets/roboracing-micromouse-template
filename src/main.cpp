#include <Arduino.h>

#include "StateMachine.h"
#include "robot/Robot.h"
#include "TeensyIO.h"

TeensyIO mouseIO{};
Robot robot{mouseIO};
StateMachine mouse{};
int pinEmitter = 5;
int pinReceiver = 41;

void setup() { 
  mouse.init(robot);
  pinMode(pinEmitter, OUTPUT);
  pinMode(pinReceiver, INPUT);
  }

void loop() {
  digitalWrite(pinEmitter, HIGH);
  int light = analogRead(pinReceiver);
  digitalWrite(pinEmitter, LOW);

  Serial.println(light);
  delay(100);
  mouse.tick(robot);

}
