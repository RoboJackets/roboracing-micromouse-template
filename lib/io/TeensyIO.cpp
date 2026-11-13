#include "TeensyIO.h"

#include <Arduino.h>

void TeensyIO::setMotorPwm(double left, double right) {
  if (left == 0.0 && right == 0.0) {
    leftMotor.brake();
    rightMotor.brake();
  } else {
    leftMotor.drive(static_cast<int>(left * 255));
    rightMotor.drive(static_cast<int>(right * 255));
  }
}

void TeensyIO::poll() {
  //Motor Checks
  for (int i = 0; i < irSensors.size(); ++i) {
    IRSensor &sensor = irSensors[i];
    digitalWrite(sensor.emit, HIGH);
    //Fix delay later cause IDK where the varaible is or what it means
    delayMicroseconds(EMIT_RECV_DELAY_US);
    int post = analogRead(sensor.recv);
    digitalWrite(sensor.emit, LOW);
    irDistances[i] = sensor.metersFrom(post);
  }

  gyro.update();
  sampYaw = gyro.ypr[0];
  leftDistance = leftEncoder.getPosition();
  rightDistance = rightEncoder.getPosition();
}

bool TeensyIO::buttonPressed() {
    return !digitalRead(b_front) || !digitalRead(b_back);
}

double TeensyIO::now() {
  const uint32_t m = micros();
  microsAccum += static_cast<uint32_t>(m - lastMicros);
  lastMicros = m;
  return microsAccum * 1e-6;
}

void TeensyIO::init() {
  Serial.begin(9600);
  
  lastMicros = micros();
  pinMode(emit1, OUTPUT);
  pinMode(emit2, OUTPUT);
  pinMode(emit3, OUTPUT);
  pinMode(emit4, OUTPUT);

  pinMode(recv1, INPUT);
  pinMode(recv2, INPUT);
  pinMode(recv3, INPUT);
  pinMode(recv4, INPUT);
  analogReadResolution(10);

  pinMode(b_front, INPUT);
  pinMode(b_back, INPUT);

  gyro.initializeGyro();

  leftMotor.start();
  rightMotor.start();
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