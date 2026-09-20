#pragma once
#include <array>

#include "MouseIO.h"

struct Robot {
  MouseIO &io;

  double lastNow = 0;
  double cachedDt = 0;

  explicit Robot(MouseIO &io) : io(io) {}

  void init();
  void update();

  double getDt() const { return cachedDt; }

  void observe() {
  }
};
