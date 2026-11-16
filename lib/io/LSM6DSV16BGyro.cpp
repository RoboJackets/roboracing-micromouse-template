#include "LSM6DSV16BGyro.h"

#include <cmath>

constexpr uint8_t SFLP_GAME_ROTATION_TAG = 0x13;

void LSM6DSV16BGyro::initializeGyro() {
  Wire.begin();
  Wire.setClock(400000);

  uint8_t id = 0;
  if (imu.ReadID(&id) != LSM6DSV16BX_OK || id != LSM6DSV16BX_ID) {
    Serial.print(F("LSM6DSV16B not found (WHO_AM_I 0x"));
    Serial.print(id, HEX);
    Serial.println(F(")"));
    return;
  }

  int status = LSM6DSV16BX_OK;
  status |= imu.begin();
  status |= imu.Set_X_FS(4);
  status |= imu.Set_G_FS(2000);
  status |= imu.Set_X_ODR(120.0f);
  status |= imu.Set_G_ODR(120.0f);
  status |= imu.Enable_X();
  status |= imu.Enable_G();
  status |= imu.Set_SFLP_ODR(120.0f);
  status |= imu.Enable_Rotation_Vector();
  status |= imu.FIFO_Set_Mode(LSM6DSV16BX_STREAM_MODE);

  if (status != LSM6DSV16BX_OK) {
    Serial.println(F("LSM6DSV16B configuration failed"));
    return;
  }
  ready = true;
}

bool LSM6DSV16BGyro::update() {
  if (!ready)
    return false;

  uint16_t samples = 0;
  if (imu.FIFO_Get_Num_Samples(&samples) != LSM6DSV16BX_OK)
    return false;

  float quat[4];
  bool gotQuat = false;
  for (uint16_t i = 0; i < samples; i++) {
    uint8_t tag = 0;
    imu.FIFO_Get_Tag(&tag);
    if (tag == SFLP_GAME_ROTATION_TAG) {
      imu.FIFO_Get_Rotation_Vector(quat);
      gotQuat = true;
    } else {
      uint8_t discard[6];
      imu.FIFO_Get_Data(discard);
    }
  }

  if (!gotQuat)
    return false;

  const float x = quat[0];
  const float y = quat[1];
  const float z = quat[2];
  const float w = quat[3];

  const float gx = 2 * (x * z - w * y);
  const float gy = 2 * (w * x + y * z);
  const float gz = w * w - x * x - y * y + z * z;

  ypr[0] = atan2f(2 * x * y - 2 * w * z, 2 * w * w + 2 * x * x - 1);
  ypr[1] = atan2f(gx, sqrtf(gy * gy + gz * gz));
  ypr[2] = atan2f(gy, gz);
  return true;
}