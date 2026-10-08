#include <Arduino.h>

// #include "StateMachine.h"
// #include "robot/Robot.h"
// #include "TeensyIO.h"

//#include "TeensyIO.h"

#include <Wire.h>
#include <MPU6050.h>

// TeensyIO mouseIO{};
// Robot robot{mouseIO};
// StateMachine mouse{};

MPU6050 accelgyro;

void setup() {
    Serial.begin(9600);
    delay(1000);
    Wire.begin();
    accelgyro.initialize();

    if (accelgyro.testConnection()) {
        Serial.println("MPU6050 connection successful!");
    } else {
        Serial.println("MPU6050 connection failed. Check wiring!");
    }
}

void loop() {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    Serial.printf("Accel: %6d %6d %6d | Gyro: %6d %6d %6d\n", ax, ay, az, gx, gy, gz);

    delay(100);
}
    
