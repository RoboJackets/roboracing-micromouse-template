#include <Arduino.h>
#include "Gyro.h"
#include "DRV8833.h"
#include "MotorTest.h"
#include "IRSensor.h"

Gyro gyro;
DRV8833Motor motor(36, 37, 1, 4);   // in1, in2, offset, standby
IRSensor ir(33, 38);                // emitter pin, receiver pin (33 is a placeholder!)

void setup() {
  Serial.begin(115200);
  gyro.initializeGyro();
  motor.begin();
  ir.begin();
}

void loop() {
  if (gyro.update()) {
    Serial.printf("ypr: %f %f %f\n",
      gyro.ypr[0] * (180.0 / M_PI),
      gyro.ypr[1] * (180.0 / M_PI),
      gyro.ypr[2] * (180.0 / M_PI));
  }

  rampMotorStep(motor);

  Serial.println(ir.read());
}