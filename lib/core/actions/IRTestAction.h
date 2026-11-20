#pragma once
#include "Action.h"

// Prints the IR distances and gyro yaw every printPeriod seconds. Never ends.
struct IRTestAction : Action {
  double printPeriod;
  double time = 0;

  explicit IRTestAction(double printPeriod);

  void run(Robot &r) override;
};
