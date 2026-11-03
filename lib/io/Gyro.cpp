#include "Gyro.h"

void Gyro::initializeGyro(){
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
  bool Gyro::update(){
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