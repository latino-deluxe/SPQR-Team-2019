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
#include "camera.h"

int vel = 160;
int usDist = 70;

int defDir = 0;
int defSpeed = 0;
int defDistance = 2;

void space_invaders() {
  x = 0;
<<<<<<< HEAD
  goalie();
  // if(pDef <= 60)  preparePID(90, 250);
  // if(pDef >= 170) preparePID(270, 255);
=======
  if(ball_degrees >= 270 && ball_degrees < 345)  preparePID(270, 255);
  if(ball_degrees >  15 && ball_degrees <= 90)   preparePID(90, 255);
  if(ball_degrees > 90 && ball_degrees < 270)    goalie();
  if(ball_degrees >= 345 || ball_degrees <= 15)  preparePID(0, 0); 
  if(us_px > 55) centerGoalPost();
  if((fixCamIMU(pDef) < keeperCamMin && ball_degrees < 180) || (fixCamIMU(pDef) > keeperCamMax) && ball_degrees > 180) centerGoalPost();
  // || us_dx < 60 || us_sx < 60) centerGoalPost();
>>>>>>> fa31793ce0a52781cd36aaf920a70143335ac774
}


void centerGoalPost() {
  x = 1;
  y = 1;
  int vel = 255;
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
      if (portx < keeperCamMin) {
        preparePID(270, vel);
      } else if (portx > keeperCamMax) {
        preparePID(90, vel);
      }
    }
  }
}
