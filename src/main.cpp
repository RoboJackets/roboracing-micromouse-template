#include <Arduino.h>

#include "StateMachine.h"
#include "robot/Robot.h"
#include "TeensyIO.h"

TeensyIO mouseIO{};
Robot robot{mouseIO};
StateMachine mouse{};

void setup() { mouse.init(robot); }

void loop() {
  mouse.tick(robot);
}
