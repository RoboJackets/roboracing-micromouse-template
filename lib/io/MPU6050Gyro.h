#pragma once
#include "Gyro.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

struct MPU6050Gyro : Gyro {
    MPU6050 mpu;
    bool dmpReady = false;
    int devStatus = 0;
    uint16_t packetSize = 0;
    uint8_t fifoBuffer[64];

    Quaternion q;
    VectorFloat gravity;

    void initializeGyro() override;
    bool update() override;
};