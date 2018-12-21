#include "libs.h"

Adafruit_BNO055 bno = Adafruit_BNO055();
float x = 0;                                // IMU angle

int imu_temp_euler = 0;
int imu_current_euler = 0;

void initIMU() {
  bno.begin(bno.OPERATION_MODE_NDOF);
  bno.setExtCrystalUse(true);
}

void readIMU(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      /*if (euler.x() != imu_current_euler){
       imu_current_euler = euler.x();
     }
    else imu_current_euler = euler.x();*/
      imu_temp_euler = euler.x();
      return imu_temp_euler;
}
