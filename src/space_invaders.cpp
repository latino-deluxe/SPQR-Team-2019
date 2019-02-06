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
  int vel = 150;

  if (us_px >= 15)
    centerGoalPost();
  if (ball_seen) {
    preparePID(0, 0);
    if (ball_sensor >= 14 && ball_sensor <= 17) {
      preparePID(270, vel);
      return;
    }
    if (ball_sensor >= 3 && ball_sensor <= 6) {
      preparePID(90, vel);
      return;
    }
  }
}

void centerGoalPost() {
  int width = 0;
  if (status_x == CENTRO) {
    if (status_y == CENTRO) {
      preparePID(180, 150);
    } else if (status_y == SUD) {
      if (us_px > 20)
        preparePID(180, 110);
      else if (us_px < 15)
        preparePID(0, 130);
      else
        preparePID(0, 0);
    } else
      goCenter();
  } else if (status_x == 255) {
    if (us_px > 50)
      preparePID(180, 110);
    else if (us_px < 30)
      preparePID(0, 130);
    else
      preparePID(0, 0);
  } else
    goCenter();
}
