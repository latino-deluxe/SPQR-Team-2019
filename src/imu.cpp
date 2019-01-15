#include "imu.h"
#include <Adafruit_BNO055.h>
#include <Arduino.h>

Adafruit_BNO055 bno = Adafruit_BNO055();

void initIMU() {
  bno.begin(bno.OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);
}

void readIMU() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  if (euler.x() != imu_current_euler) {
    /*Serial.print("X: ");
       Serial.println(euler.x());*/
    imu_current_euler = euler.x();
  }
  return;
}

void testIMU() {
  readIMU();
  Serial.println(imu_current_euler);
}
