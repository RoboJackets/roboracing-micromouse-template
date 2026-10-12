#include <Arduino.h>

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

    if (devStatus == 0) {
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.PrintActiveOffsets();

      mpu.setDMPEnabled(true);
      dmpReady = true;
      packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
      Serial.print("DMP Initialization failed (code ");
      Serial.print(devStatus);
      Serial.println(")");
    }
  }

  // returns true when new ypr was computed
  bool update(){
    if (!dmpReady) return false;
    //Serial.print("test1");

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      return true;
    }

    return false;
  }
};

//ch
Gyro gyro{};

void setup() { 
  pinMode(22, OUTPUT);

  //ch
  Serial.begin(115200);
  gyro.initializeGyro();
}

void loop() {
  // digitalWrite(22, HIGH);
  // delay(100);
  // digitalWrite(22, LOW);
  // delay(100);

  // Serial.printf("Accel X: %d ", gyro.mpu.getAccelerationX());
  // Serial.print(" ");
  // Serial.printf("Accel Y: %d ",gyro.mpu.getAccelerationY());
  // Serial.print(" ");
  // Serial.printf("Accel Z: %d ", gyro.mpu.getAccelerationZ());
  // Serial.print(" ");

//Serial.printf("Test\n");
  //Serial.printf("accel: %d %d %d\n", gyro.mpu.getAccelerationX(), gyro.mpu.getAccelerationY(), gyro.mpu.getAccelerationZ());
  //ch 
if (gyro.update()) {
    Serial.printf("ypr: %f %f %f\n", gyro.ypr[0] * (180.0 / M_PI), gyro.ypr[1] * (180.0 / M_PI), gyro.ypr[2] * (180.0 / M_PI));
  }

}

