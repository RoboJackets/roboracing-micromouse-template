#pragma once
#include "actions/EmptyAction.h"
#include "actions/IRTestAction.h"
#include "actions/MotorTestAction.h"
#include "actions/SequentialAction.h"

struct StateMachine {
  SequentialAction startup = makeStartup();
  EmptyAction empty{};
  Action *a = &startup;

  static SequentialAction makeStartup() {
    return SequentialAction::make(MotorTestAction(0.5, 2.0, 3),
                                  IRTestAction(0.25));
  }

  void init(Robot &r);
  void tick(Robot &r);
};
