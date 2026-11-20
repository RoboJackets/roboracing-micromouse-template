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
    // TODO

  }
  // get gyros
}

bool TeensyIO::buttonPressed() {
    return ;
}

double TeensyIO::now() {
  return 0.0;
}

void TeensyIO::init() {

}