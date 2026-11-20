#pragma once

#include <cstdint>

// Pins that aren't wired yet. Every driver skips a NO_PIN.
constexpr uint8_t NO_PIN = 255;

constexpr uint8_t EMIT_1 = 33;
constexpr uint8_t EMIT_2 = NO_PIN;
constexpr uint8_t EMIT_3 = NO_PIN;
constexpr uint8_t EMIT_4 = NO_PIN;

constexpr uint8_t RECV_1 = 38;
constexpr uint8_t RECV_2 = NO_PIN;
constexpr uint8_t RECV_3 = NO_PIN;
constexpr uint8_t RECV_4 = NO_PIN;

constexpr uint8_t AIN1 = 36;
constexpr uint8_t AIN2 = 37;

constexpr uint8_t BIN1 = NO_PIN;
constexpr uint8_t BIN2 = NO_PIN;

// The HW-627's EEP (sleep) pin is tied to 3.3V, so there's no standby pin.
constexpr uint8_t STBY = NO_PIN;

constexpr uint8_t B_FRONT = NO_PIN;
constexpr uint8_t B_BACK = NO_PIN;
