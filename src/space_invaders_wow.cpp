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

byte ball_array[5];
short i;
byte vel_por = 255;
long diff;
float ball_distance_precise;

void space_invaders_camera() {
  if (ball_sensor >= 1 && ball_sensor <= 6) {
    if (portx < 130)
      preparePID(90, 180);
    else
      preparePID(0, 0);
  } else if (ball_sensor >= 14 && ball_sensor <= 19) {
    if (portx > 60)
      preparePID(270, 180);
    else
      preparePID(0, 0);
  } else if (ball_sensor < 14 && ball_sensor > 6) {
    goalie();
    // preparePID(180, 180);
  } else {
    preparePID(0, 0);
  }

  // menamoli approssimato :D
  if (ball_distance <= 2)
    goalie();
}

void space_invaders_us() {
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
    preparePID(0, 0);
  }

  // menamoli approssimato :D
  if (ball_distance <= 2)
    goalie();
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
    preparePID(0, 0);
  }
}

void centerGoalPostCamera() {
  int vel = 150;
  if(portx <= 85)  preparePID(90, vel);
  if(portx >= 125) preparePID(270, vel);
  if(portx <= 0) centerGoalPost();
  if(zoneIndex <= 5) centerGoalPost();
}
