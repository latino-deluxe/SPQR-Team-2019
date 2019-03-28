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

int vel = 160;

void space_invaders_camera() {
  if (CAMERA.available() <= 0) {
    space_invaders_us();
  } else {
    if (portx == 0 || portx == 999) {
      centerGoalPost();
    } else {
      if (us_px > 35) {
        if (ball_sensor >= 1 && ball_sensor <= 6) {
          if (portx > keeperMin)
            preparePID(90, vel);
          else
            preparePID(0, 0);
        } else if (ball_sensor >= 14 && ball_sensor <= 19) {
          if (portx < keeperMax)
            preparePID(270, vel);
          else
            preparePID(0, 0);
        } else if (ball_sensor < 14 && ball_sensor > 6) {
          // goalie();
          // Testa questa roba qui e commenta il goalie() di sopra:
          if (ball_sensor >= 10 && ball_sensor < 14) {
            if (portx < keeperMax)
              goalie();
            else
              preparePID(0, 0);
          } else if (ball_sensor <= 10 && ball_sensor > 6) {
            if (portx > keeperMin)
              goalie();
            else
              preparePID(0, 0);
          }
        } else {
          preparePID(0, 0);
        }
      } else {
        centerGoalPostCamera();
      }
    }
  }
}
void space_invaders_us() {
  if (us_px > 35) {
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (us_dx > 60 || us_sx < 60)
        preparePID(90, vel);
      else
        preparePID(0, 0);
    } else if (ball_sensor >= 14 && ball_sensor <= 19) {
      if (us_sx > 60 || us_dx < 60)
        preparePID(270, vel);
      else
        preparePID(0, 0);
    } else if (ball_sensor < 14 && ball_sensor > 6) {
      // goalie();

      // Testa questa roba qui e commenta il goalie() di sopra:
      if (ball_sensor >= 10 && ball_sensor < 14) {
        if (us_sx > 60 || us_dx < 60)
          goalie();
        else
          preparePID(0, 0);
      } else if (ball_sensor <= 10 && ball_sensor > 6) {
        if (us_dx > 60 || us_sx < 60)
          goalie();
        else
          preparePID(0, 0);
      }
    } else {
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
  if (portx == 0 || portx == 999 || CAMERA.available() <= 0) {
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
