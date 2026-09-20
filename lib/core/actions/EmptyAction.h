#pragma once
#include "Action.h"

struct EmptyAction : Action {
  void run(Robot &r) override {}
  bool completed() const override { return true; }
};
