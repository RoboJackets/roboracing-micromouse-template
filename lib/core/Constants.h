#pragma once

#include <cmath>
#include <cstdint>

constexpr uint32_t EMIT_RECV_DELAY_US = 300;

constexpr double WHEEL_RADIUS_M = (0.032 / 2);

constexpr double COUNTS_PER_WHEEL_REV = 617.3544;

constexpr double ROBOT_LENGTH = 0.13;

constexpr double CELL_SIZE_METERS = 0.18;
constexpr double MAX_SPEED_M_S = 1.5;
constexpr double MAX_ACCEL_M_S2 = 1;
constexpr double WHEEL_SEPARATION_M = 0.09134;
constexpr double MAX_ROT_SPEED_RAD_S = (2 * MAX_SPEED_M_S) / WHEEL_SEPARATION_M;
constexpr double MAX_ROT_SPEED_RAD_S2 =
    (2 * MAX_ACCEL_M_S2) / WHEEL_SEPARATION_M;
constexpr double COEF_FRICTION = 0.5;