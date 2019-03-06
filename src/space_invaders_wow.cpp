#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "space_invaders.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>
#include <math.h>

unsigned long t = 0;
int c = 0;

void keeper() {
  // recenter(2.0);
  // if(ball_distance)
}

void space_invaders_3() {
  if (zoneIndex >= 6) {
    if (us_px <= 25) {
      preparePID(0, 125);
      return;
    }
    if (us_px >= 45) {
      preparePID(180, 125);
      return;
    }

    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (us_dx < 70) {
        preparePID(0, 0);
      } else {
        preparePID(90, 180);
      }
    } else if (ball_sensor >= 14 && ball_sensor <= 19) {
      if (us_sx < 70) {
        preparePID(0, 0);
      } else {
        preparePID(270, 180);
      }
    } else if (ball_sensor > 7 && ball_sensor < 14) {
      palla_dietro();
    } else {
      preparePID(0, 0);
    }
  } else {
    centerGoalPost();
  }
}

void centerGoalPost() {
  int vel = 200;

  if ((zoneIndex >= 0 && zoneIndex <= 2) || zoneIndex == 4)
    preparePID(180, vel);
  else if (zoneIndex == 3 || zoneIndex == 6)
    preparePID(90, vel);
  else if (zoneIndex == 5 || zoneIndex == 8)
    preparePID(270, vel);
  else
    preparePID(0, 0);

  // if (zoneIndex < 6) {
  //   preparePID(180, vel);
  // } else if (zoneIndex == 8) {
  //   preparePID(270, vel);
  // } else if (zoneIndex == 6) {
  //   preparePID(90, vel);
  // } else if (zoneIndex == 7) {
  //   preparePID(0, 0);
  // }
}
