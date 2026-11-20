#include "IRTestAction.h"

#include "robot/Robot.h"

IRTestAction::IRTestAction(double printPeriod) : printPeriod(printPeriod) {}

void IRTestAction::run(Robot &r) {
  time += r.getDt();
  if (time < printPeriod)
    return;
  time = 0;

  const auto &ir = r.io.irMeters();
  r.io.printf("[ir_test] IR: %0.3f %0.3f %0.3f %0.3f  YAW: %0.2f\n", ir[0],
              ir[1], ir[2], ir[3], r.io.gyroYaw());
}
