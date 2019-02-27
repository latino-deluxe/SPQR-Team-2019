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
  int dir = 0, vel = 215;

  if (zoneIndex >= 6) {
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (zoneIndex < 8) {
        preparePID(90, vel);
      } else {
        preparePID(0, 0);
      }
    } else if (ball_sensor >= 14 && ball_sensor <= 19) {
      if (zoneIndex > 6) {
        preparePID(270, vel);
      } else {
        preparePID(0, 0);
      }
    } else {
      preparePID(0, 0);
    }
  } else {
    centerGoalPost();
  }
  // if (ball_sensor >= 1 && ball_sensor <= 6) {
  //   // if it's not in the right zone (8), go right
  //   if (zoneIndex != 8) {
  //     dir = 90;
  //   } else {
  //     vel = 0;
  //   }
  // } else if (ball_sensor >= 14 && ball_sensor <= 19) {
  //   // if it's not in the left zone (6), go left
  //   if (zoneIndex != 6) {
  //     dir = 270;
  //   } else {
  //     vel = 0;
  //   }
  // } else if (ball_sensor > 6 && ball_sensor < 14) {
  //   goalie(); // ball behind: goalie
  // } else {
  //   vel = 0;
  //   dir = 0; // ball in front of the robot: stop
  // }
  // preparePID(dir, vel);
}

void centerGoalPost() {
  int vel = 200;

  if (zoneIndex < 6) {
    preparePID(180, vel);
  } else if (zoneIndex == 8) {
    preparePID(270, vel);
  } else if (zoneIndex == 6) {
    preparePID(90, vel);
  } else if (zoneIndex == 7) {
    preparePID(0, 0);
  }
}
