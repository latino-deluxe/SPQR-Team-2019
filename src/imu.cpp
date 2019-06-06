#include "imu.h"
#include "vars.h"
#include <Adafruit_BNO055.h>
#include <Arduino.h>

Adafruit_BNO055 bno = Adafruit_BNO055();

void initIMU() {
  bno.begin(bno.OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);
  bno.setAxisSign(bno.REMAP_SIGN_P6);
  bno.setAxisRemap(bno.REMAP_CONFIG_P6);

}

void readIMU() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  if (euler.x() != imu_current_euler) {
    imu_current_euler = euler.x();
  }
  return;
}

void testIMU() {
  readIMU();
  DEBUG_PRINT.print("IMU: ");
  DEBUG_PRINT.println(imu_current_euler);
}
