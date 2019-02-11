#include "imu.h"
#include "motors.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "space_invaders.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>

void space_invaders() {
  int vel = 200;

  if (zoneIndex < 6 || !ball_seen ){
    centerGoalPost();
  }else{
    preparePID(0, 0);
    if (ball_sensor >= 12 && ball_sensor <= 18) {
      preparePID(270, vel);
      return;
    }
    if (ball_sensor >= 1 && ball_sensor <= 8) {
      preparePID(90, vel);
      return;
    }
    centerGoalPost();
  }
}

void centerGoalPost(){

  int vel = 150;

  if(zoneIndex != 7) {
    if(zoneIndex < 6){
      preparePID(180, vel);
    }
    else if (zoneIndex == 8){
      preparePID(270, vel);
    }
    else if(zoneIndex == 6){
      preparePID(90, vel);
    }
  }
  else {
    if(imu_current_euler <= 345 || imu_current_euler >= 15) preparePID(0, 0);
  }
}

// void centerGoalPost() {
//     int larghezza = 0;
//     if (status_x == CENTRO) {
//       if (status_y == CENTRO) {
//         preparePID(180, 150);
//       }
//       else if (status_y == SUD) {
//         if (us_px > 20) preparePID(180, 110);
//         else if (us_px < 15) preparePID(0, 130);
//         else preparePID(0,0);
//       }
//       else goCenter();
//     }
//     else if (status_x == 255) {
//       if (us_px > 50) preparePID(180, 110);
//       else if (us_px < 30) preparePID(0, 130);
//       else preparePID(0,0);
//     }
//     else goCenter();
// }
