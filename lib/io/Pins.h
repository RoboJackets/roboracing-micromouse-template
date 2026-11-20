#pragma once
#include <cstdint>

#define UNINITIALIZED -1

constexpr uint8_t EMIT_1 = UNINITIALIZED;
constexpr uint8_t EMIT_2 = UNINITIALIZED;
constexpr uint8_t EMIT_3 = UNINITIALIZED;
constexpr uint8_t EMIT_4 = UNINITIALIZED;

constexpr uint8_t RECV_1 = UNINITIALIZED;
constexpr uint8_t RECV_2 = UNINITIALIZED;
constexpr uint8_t RECV_3 = UNINITIALIZED;
constexpr uint8_t RECV_4 = UNINITIALIZED;

constexpr uint8_t AIN1 = UNINITIALIZED;
constexpr uint8_t AIN2 = UNINITIALIZED;

constexpr uint8_t BIN1 = UNINITIALIZED;
constexpr uint8_t BIN2 = UNINITIALIZED;

constexpr uint8_t STBY = UNINITIALIZED;

constexpr uint8_t ACODER_a = UNINITIALIZED;
constexpr uint8_t ACODER_b = UNINITIALIZED;

constexpr uint8_t BCODER_a = UNINITIALIZED;
constexpr uint8_t BCODER_b = UNINITIALIZED;

constexpr uint8_t B_FRONT = UNINITIALIZED;
constexpr uint8_t B_BACK = UNINITIALIZED;
constexpr uint8_t BUZZER_PIN = UNINITIALIZED;

#define GYRO_INT_1 A5