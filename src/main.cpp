#include <Arduino.h>

#define DEBUG

#define MOTOR_IN1 36
#define MOTOR_IN2 37

#define MOTOR_SPEED 128
#define FULL_DUTY 255
#define STATE_TIME_MS 2000

enum class MotorState : uint8_t {
  Coast = 'C',
  Forward = 'F',
  Brake = 'B',
  Reverse = 'R'
};

void motor_init();
void motor_forward(uint8_t speed);
void motor_reverse(uint8_t speed);
void motor_brake();
void motor_coast();

MotorState coast_task();
MotorState forward_task();
MotorState brake_task();
MotorState reverse_task();
bool state_time_up();

MotorState state = MotorState::Coast;
uint32_t state_start = 0;

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
    Serial.println("DRV8833 motor test");
  #endif

  motor_init();
  state_start = millis();
}

void loop() {
  #ifdef DEBUG
    MotorState last_state = state;
  #endif

  switch (state) {
    case MotorState::Forward:
      state = forward_task();
    break;
    case MotorState::Brake:
      state = brake_task();
    break;
    case MotorState::Reverse:
      state = reverse_task();
    break;
    default:
      state = coast_task();
    break;
  }

  #ifdef DEBUG
    if (state != last_state) {
      Serial.print("State: ");
      Serial.println((char) state);
    }
  #endif
}

void motor_init() {
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  motor_coast();
}

void motor_forward(uint8_t speed) {
  analogWrite(MOTOR_IN1, speed);
  analogWrite(MOTOR_IN2, 0);
}

void motor_reverse(uint8_t speed) {
  analogWrite(MOTOR_IN1, 0);
  analogWrite(MOTOR_IN2, speed);
}

void motor_brake() {
  analogWrite(MOTOR_IN1, FULL_DUTY);
  analogWrite(MOTOR_IN2, FULL_DUTY);
}

void motor_coast() {
  analogWrite(MOTOR_IN1, 0);
  analogWrite(MOTOR_IN2, 0);
}

bool state_time_up() {
  if (millis() - state_start < STATE_TIME_MS) {
    return false;
  }
  state_start = millis();
  return true;
}

MotorState coast_task() {
  motor_coast();
  return state_time_up() ? MotorState::Forward : MotorState::Coast;
}

MotorState forward_task() {
  motor_forward(MOTOR_SPEED);
  return state_time_up() ? MotorState::Brake : MotorState::Forward;
}

MotorState brake_task() {
  motor_brake();
  return state_time_up() ? MotorState::Reverse : MotorState::Brake;
}

MotorState reverse_task() {
  motor_reverse(MOTOR_SPEED);
  return state_time_up() ? MotorState::Coast : MotorState::Reverse;
} 