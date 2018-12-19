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
    digitalWrite(30, HIGH);
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      if (euler.x() != x){
       /*Serial.print("X: ");
       Serial.println(euler.x());*/
       x = euler.x();
     }
    else x = euler.x();
}
