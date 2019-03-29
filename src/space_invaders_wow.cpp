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

int vel = 160;

void space_invaders_camera() {
  if (us_px >= 35 || portx == 999) {
    centerGoalPost();
  } else {
    // dx
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (portx > keeperMin) {
        preparePID(90, vel);
      } else {
        preparePID(0, 0);
      }
    }
    // sx
    else if (ball_sensor <= 19 && ball_sensor >= 14) {
      if (portx < keeperMax) {
        preparePID(270, vel);
      } else {
        preparePID(0, 0);
      }
    }
    // behind
    else if (ball_sensor < 14 && ball_sensor > 6) {
      goalie();
    }
    // in front
    else {
      preparePID(0, 0);
      if (ball_distance <= 3) {
        goalie();
      }
    }
  }
}

void space_invaders_us() {
  if (us_px <= 35) {
    // dx
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (us_dx > 60 || us_sx < 60) {
        preparePID(90, vel);
      } else {
        preparePID(0, 0);
      }
    }
    // sx
    else if (ball_sensor <= 19 && ball_sensor >= 14) {
      if (us_sx > 60 || us_dx < 60) {
        preparePID(270, vel);
      } else {
        preparePID(0, 0);
      }
    }
    // behind
    else if (ball_sensor < 14 && ball_sensor > 6) {
      goalie();
    }
    // in front
    else {
      preparePID(0, 0);
      if (ball_distance <= 3) {
        goalie();
      }
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
    if (zoneIndex < 6) {
      centerGoalPost();
    } else {
      if (portx < keeperMin) {
        preparePID(270, vel);
      } else if (portx > keeperMax) {
        preparePID(90, vel);
      }
    }
  }
}
