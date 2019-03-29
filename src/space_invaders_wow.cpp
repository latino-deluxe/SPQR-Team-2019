#include "bluetooth.h"
#include "chat.h"
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

// VARIABILI PER IL PORTIERE
float bd = 0;
long ta;
bool atk_p = false;
int vel = 255;

void space_invaders_camera() {
  if (portx == 0 || portx == 999) {
    space_invaders_us();
  } else {
    if (us_px < 35) {
      if (ball_sensor >= 1 && ball_sensor <= 6) {
        if (portx > keeperMin)
          preparePID(90, 180);
        else
          // preparePID(0, 0);
          preparePID(270, 90);
      } else if (ball_sensor >= 14 && ball_sensor <= 19) {
        if (portx < keeperMax)
          preparePID(270, 180);
        else
          // preparePID(0, 0);
          preparePID(90, 90);
      } else if (ball_sensor < 14 && ball_sensor > 6) {
        goalie();
      } else {
        // menamoli approssimato :D
        // if (ball_distance <= 3)
        //   goalie();
        // else
        preparePID(0, 0);
      }

    } else {
      preparePID(180, 120);
    }
  }
}
void space_invaders_us() {
  if (us_px < 35) {
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (us_dx > 60 || us_sx < 60)
        preparePID(90, 180);
      else
        preparePID(0, 0);
    } else if (ball_sensor >= 14 && ball_sensor <= 19) {
      if (us_sx > 60 || us_dx < 60)
        preparePID(270, 180);
      else
        preparePID(0, 0);
    } else if (ball_sensor < 14 && ball_sensor > 6) {
      goalie();
      // preparePID(180, 180);
    } else {
      // spintina in avanti :D
      if (ball_distance <= 3)
        goalie();
      else
        preparePID(0, 0);
    }
  } else {
    centerGoalPost();
  }
}

void centerGoalPost() {
  int vel = 150;
  if ((zoneIndex >= 0 && zoneIndex <= 2) || zoneIndex == 4) {
    preparePID(180, vel);
  } else if (zoneIndex == 3 || zoneIndex == 6) {
    preparePID(90, vel);
  } else if (zoneIndex == 5 || zoneIndex == 8) {
    preparePID(270, vel);
  } else {
    stop_menamoli = false;
    preparePID(0, 0);
  }
}

void centerGoalPostCamera() {
  if (portx == 0 || portx == 999) {
    centerGoalPost();
  } else {
    int vel = 150;
    if (zoneIndex < 6) {
      centerGoalPost();
    } else {
      if (portx < keeperMin) {
        preparePID(90, 0);
      } else if (portx > keeperMax) {
        preparePID(270, 0);
      }
    }
  }
}
