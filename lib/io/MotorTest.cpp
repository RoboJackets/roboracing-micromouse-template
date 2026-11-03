#include <Arduino.h>
#include "MotorTest.h"

void rampMotorStep(DRV8833Motor& motor) {
  static int speed = 0;
  static unsigned long last = 0;

  if (millis() - last >= 100) {
    last = millis();
    motor.drive(speed);
    Serial.printf("%d\n", speed);
    speed++;
    if (speed > 250) speed = 0;
  }

//   for(int i = 0; i < 255; i+=1) {
//     motor.drive(i);  //gradually increase speed
//     delay(100);
//     Serial.printf("%d %n", i);
//     if(i == 250) {
//       delay(1000);
//       i = 0;
//     }
//   }
}