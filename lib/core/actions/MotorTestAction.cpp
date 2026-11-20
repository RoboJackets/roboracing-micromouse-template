#include "MotorTestAction.h"

#include "robot/Robot.h"

enum class MotorStep : char { Forward = 'F', Stop = 'S', Reverse = 'R' };

constexpr MotorStep MOTOR_TEST_STEPS[] = {MotorStep::Forward, MotorStep::Stop,
                                          MotorStep::Reverse, MotorStep::Stop};
constexpr size_t MOTOR_TEST_STEP_COUNT =
    sizeof(MOTOR_TEST_STEPS) / sizeof(MOTOR_TEST_STEPS[0]);

MotorTestAction::MotorTestAction(double speed, double stepTime, int cycles)
    : speed(speed), stepTime(stepTime), cycles(cycles) {}

void MotorTestAction::run(Robot &r) {
  const MotorStep current = MOTOR_TEST_STEPS[step];

  if (time == 0) {
    r.io.printf("[motor_test] cycle %d step %c\n", cyclesDone + 1,
                static_cast<char>(current));
  }

  switch (current) {
  case MotorStep::Forward:
    r.io.setMotorPwm(speed, speed);
    break;
  case MotorStep::Reverse:
    r.io.setMotorPwm(-speed, -speed);
    break;
  case MotorStep::Stop:
    r.io.setMotorPwm(0, 0);
    break;
  }

  time += r.getDt();
  if (time < stepTime)
    return;

  time = 0;
  step++;
  if (step < MOTOR_TEST_STEP_COUNT)
    return;

  step = 0;
  cyclesDone++;
  if (cyclesDone >= cycles)
    cancel();
}

void MotorTestAction::end(Robot &r) { r.io.setMotorPwm(0, 0); }
