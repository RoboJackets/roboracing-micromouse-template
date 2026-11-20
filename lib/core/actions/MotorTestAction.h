#pragma once
#include <cstddef>

#include "Action.h"

// Forward -> Stop -> Reverse -> Stop, stepTime seconds each, repeated cycles
// times. speed is a duty cycle from 0.0 to 1.0.
struct MotorTestAction : Action {
  double speed;
  double stepTime;
  int cycles;

  size_t step = 0;
  double time = 0;
  int cyclesDone = 0;

  MotorTestAction(double speed, double stepTime, int cycles);

  void run(Robot &r) override;
  void end(Robot &r) override;
};
