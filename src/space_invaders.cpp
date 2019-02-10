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

  if (us_px >= 20|| !ball_seen ) {
    centerGoalPost();
  } else {
    preparePID(0, 0);
    if (ball_sensor >= 14 && ball_sensor <= 18) {
      preparePID(270, vel);
      return;
    }
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      preparePID(90, vel);
      return;
    }
  }
}

void centerGoalPost() {
    int width = 0;  //ex larghezza
    if (status_x == CENTER) {
      if (status_y == CENTER) {
        preparePID(180, 150);
      } else if (status_y == SOUTH) {
          if (us_px > 20) preparePID(180, 110);
          else if (us_px < 15) preparePID(0, 130);
          else preparePID(0,0);
      }
      else goCenter();
      } else if (status_x == 255) {
          if (us_px > 50) preparePID(180, 110);
          else if (us_px < 30) preparePID(0, 130);
          else preparePID(0,0);
    } else goCenter();
}
