#include "TeensyIO.h"

#include <Arduino.h>


void TeensyIO::setMotorPwm(double left, double right) {
  if (left == 0.0 && right == 0.0) {
    mLeft.brake();
    mRight.brake();
  } else {
    // we need to scale up since we will have left,right in [0,1)
    mLeft.drive((int)(left*255));
    mRight.drive((int)(right*255));
  }
}

void TeensyIO::poll() {
  // get IR sensors
  for (size_t i = 0; i < sensors.size(); i++) {
    IRSensor &sensor = sensors[i];
    digitalWrite(sensor.EMIT, HIGH);
    delay(1000);
    int post = sensor.readPost();
    digitalWrite(sensor.EMIT, LOW);
    sampledIr[i] = sensor.metersFrom(post);


  }
  gyro.update();
  sampledYaw = gyro.ypr[0];

}

bool TeensyIO::buttonPressed() {
    return ;
}

double TeensyIO::now() {
  const uint32_t m = micros();
  microsAccum += static_cast<uint32_t>(m - lastMicros);
  lastMicros = m;
  return microsAccum * 1e-6;
}

void TeensyIO::init() {

}