#include <Arduino.h>

#include "StateMachine.h"
#include "robot/Robot.h"
#include "TeensyIO.h"

#pragma once
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

struct Gyro {
  MPU6050 mpu;
  bool dmpReady = false;
  uint8_t devStatus = 0;
  uint16_t packetSize = 0;
  uint8_t fifoBuffer[64];

  float ypr[3] = {0, 0, 0};

  Quaternion q;
  VectorFloat gravity;

  void initializeGyro(){
    Wire.begin();
    Wire.setClock(400000);
    Wire.setTimeout(3000);

    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    // mpu.setXGyroOffset(220);
    // mpu.setYGyroOffset(76);
    // mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788);

    if (devStatus == 0) {
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.PrintActiveOffsets();

      mpu.setDMPEnabled(true);
      dmpReady = true;
      packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
    }
  }

  // returns true when new ypr was computed
  bool update() {
    if (!dmpReady)
      return false;

    // This call both checks FIFO and fills fifoBuffer with the latest complete
    // packet.
    if (!mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
      return false;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    return true;
  }
};

TeensyIO mouseIO{};
Robot robot{mouseIO};
StateMachine mouse{};
Gyro gyro{};

int emitterPin = 33;
int recieverPin = 41;
int val;
int _in1;
int _in2;
int _stby;
int _offset;

void setup() { 
  // Gyro Code
  gyro.initializeGyro();

  Serial.begin(9600);

  // IR stuff
  pinMode(emitterPin, INPUT);
  pinMode(recieverPin, OUTPUT);

  // H Bridge
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_stby, OUTPUT);
  digitalWrite(_stby, HIGH);
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);
}
void loop() {
  drive(120);
  delay(1000);
  drive(0);  
  delay(500);

  /* IR sensor code
  digitalWrite(emitterPin, HIGH);
  delayMicroseconds(300);

  val = analogRead(recieverPin);
  Serial.println(val);

  digitalWrite(emitterPin, HIGH);
  delay(200);
  */

  /* Gyro Code
  if (gyro.update())
  {
    Serial.printf("Yaw: %.02f", gyro.ypr[0]);
    Serial.printf("Yaw: %.02f", gyro.ypr[1]);
    Serial.printf("Yaw: %.02f", gyro.ypr[2]);
  }
  */
}

void drive(int speed) {
  digitalWrite(_stby, HIGH);

  analogWrite(_in1, 0);
  analogWrite(_in2, 0);
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);

  if (speed * _offset > 0) {
    digitalWrite(_in2, LOW);
    analogWrite(_in1, std::abs(speed));
  } else if (speed * _offset < 0) {
    digitalWrite(_in1, LOW);
    analogWrite(_in2, std::abs(speed));
  } else {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
  }
}

void brake() {
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, HIGH);
}
