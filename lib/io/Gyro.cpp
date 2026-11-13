#include "Gyro.h"

void Gyro::initializeGyro() {
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

bool Gyro::update() {
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