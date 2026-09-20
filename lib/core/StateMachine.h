#pragma once
#include "actions/EmptyAction.h"
#include "actions/SequentialAction.h"

struct StateMachine {
  SequentialAction startup = makeStartup();
  EmptyAction empty{};
  Action *a = &startup;

  static SequentialAction makeStartup() {
    return SequentialAction::make(EmptyAction{});
  }

  void init(Robot &r);
  void tick(Robot &r);
};
