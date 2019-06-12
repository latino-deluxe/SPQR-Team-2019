#include "bluetooth.h"
#include "chat.h"
#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "pid.h"
#include "position.h"
#include "space_invaders.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>
#include <math.h>

int vel = 160;
int usDist = 70;

int defDir = 0;
int defSpeed = 0;
int defDistance = 2;

void space_invaders() {
  if(ball_degrees >= 270 && ball_degrees < 345)  preparePID(270, 255);
  if(ball_degrees >  15 && ball_degrees <= 90)   preparePID(90, 255);
  if(ball_degrees > 90 && ball_degrees < 270)    goalie();
  if(ball_degrees >= 345 || ball_degrees <= 15)  preparePID(0, 0);
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
    if (us_px >= 25)
      preparePID(180, vel);
    else
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
