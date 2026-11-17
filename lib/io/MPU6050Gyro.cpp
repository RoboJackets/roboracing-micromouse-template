#include "MPU6050Gyro.h"
#include "Arduino.h"

void MPU6050Gyro::initializeGyro() {
    Wire.begin();
    Wire.setClock(400000);

    mpu.initialize();
    devStatus = mpu.dmpInitialize();
    if (devStatus == 0) {
        // to calibrate we need to wait before touching it
        mpu.CalibrateAccel();
        mpu.CalibrateGyro();
        //at some point we can find the exact calibration needed
        //and hardcode those offsets in

        mpu.setDMPEnabled(true);
        packetSize = mpu.dmpGetFIFOPacketSize();
        dmpReady = 1;
    } else {
        dmpReady = 0;
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

bool MPU6050Gyro::update() {
    if (!dmpReady) {
        return 0;
    }

    bool newPacket = mpu.dmpGetCurrentFIFOPacket(fifoBuffer);
    if (!newPacket) {
        return 0;
    }

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    return 1;
} 
