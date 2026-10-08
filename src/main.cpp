#include <Arduino.h>

#include "StateMachine.h"
#include "TeensyIO.h"
#include "robot/Robot.h"


TeensyIO mouseIO{};
Robot robot{mouseIO};
StateMachine mouse{};

void setup() {
  mouse.init(robot);
  Serial.print("hi");
}

void loop() { mouse.tick(robot); }
