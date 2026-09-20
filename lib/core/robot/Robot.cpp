#include "Robot.h"

#include <algorithm>

void Robot::init() {
  io.init();
  lastNow = io.now();
}

void Robot::update() {
  const double n = io.now();
  cachedDt = std::max(n - lastNow, 1e-6);
  lastNow = n;

  io.poll();
}
