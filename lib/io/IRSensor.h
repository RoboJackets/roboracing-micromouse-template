#pragma once
#include <cmath>
#include <cstdint>
#include <limits>

struct IRSensor {
  int emit;
  int recv;

  double a;
  double b;

  double metersFrom(int post) const {
    if (post > 20)
      return a / std::pow(post, b);
    return std::numeric_limits<double>::infinity();
  }
};