#include "TeensyIO.h"

#include <Arduino.h>
#include <limits>

void TeensyIO::setMotorPwm(double left, double right) {
  if (left == 0.0 && right == 0.0) {
    mLeft.brake();
    mRight.brake();
  } else {
    mLeft.drive((int)(left * 255));
    mRight.drive((int)(right * 255));
  }
}

void TeensyIO::poll() {
  for (size_t i = 0; i < sensors.size(); i++) {
    IRSensor &sensor = sensors.at(i);
    if (sensor.EMIT == NO_PIN || sensor.RECV == NO_PIN) {
      sampledIr[i] = std::numeric_limits<double>::infinity();
      continue;
    }
    digitalWrite(sensor.EMIT, HIGH);
    delayMicroseconds(EMIT_RECV_DELAY_US);
    int post = analogRead(sensor.RECV);
    digitalWrite(sensor.EMIT, LOW);
    // Serial.printf("%d: %d     ", i, post);
    sampledIr[i] = sensor.metersFrom(post);
  }
  // Serial.println();

  gyro.update();
  sampledYaw = gyro.ypr[0];
}

bool TeensyIO::buttonPressed() {
  const bool front = B_FRONT != NO_PIN && !digitalRead(B_FRONT);
  const bool back = B_BACK != NO_PIN && !digitalRead(B_BACK);
  return front || back;
}

double TeensyIO::now() {
  const uint32_t m = micros();
  microsAccum += static_cast<uint32_t>(m - lastMicros);
  lastMicros = m;
  return microsAccum * 1e-6;
}

void TeensyIO::init() {
  Serial.begin(115200);

  lastMicros = micros();
  pinMode(LED_BUILTIN, OUTPUT);
  for (IRSensor &sensor : sensors) {
    if (sensor.EMIT == NO_PIN || sensor.RECV == NO_PIN)
      continue;
    pinMode(sensor.EMIT, OUTPUT);
    digitalWrite(sensor.EMIT, LOW);
    pinMode(sensor.RECV, INPUT);
  }
  analogReadResolution(10);

  if (B_FRONT != NO_PIN)
    pinMode(B_FRONT, INPUT);
  if (B_BACK != NO_PIN)
    pinMode(B_BACK, INPUT);

  gyro.initializeGyro();

  mLeft.begin();
  mRight.begin();
}

int TeensyIO::printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  char buf[256];
  int result = vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);
  if (result > 0)
    Serial.write(buf, result < (int)sizeof(buf) ? result : sizeof(buf) - 1);
  return result;
}
