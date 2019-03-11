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

void space_invaders_m() {

  if (i = 0) {
    ball_array[0] = ball_distance;
    i++;
  } else if (i = 1) {
    ball_array[1] = ball_distance;
    i++;
  }
  if (i = 2) {
    ball_array[2] = ball_distance;
    i++;
  } else if (i = 3) {
    ball_array[3] = ball_distance;
    i++;
  } else if (i = 4) {
    ball_array[4] = ball_distance;
    i = 0;
  }

  comunicazione(1000);

  ball_distance_precise = (ball_array[0] + ball_array[1] + ball_array[2] +
                           ball_array[3] + ball_array[4]) /
                          5;
  ball_distance_precise = (ball_distance_precise * 100) / 100;

  if (comrade == true) {
    if (ball_sensor == 0) {
      brake();
      readIMU(); // reads the imu euler angle >imu_current_euler<
      recenter(1.0);
    }
    if ((ball_sensor >= 1) && (ball_sensor <= 6)) {
      drivePID(90, GOALIE_P);
    }
    if ((ball_sensor <= 19) && (ball_sensor >= 14)) {
      drivePID(270, GOALIE_P);
    }
    if ((ball_sensor < 14) && (ball_sensor > 6)) {
      // menamoli();
      goalie();
    }

    if (us_px > 35) {
      drivePID(180, 150);
    }
    if (us_px < 18) {
      drivePID(0, 150);
    }
    atk_p = false;
  }

  else {
    // if (ball_distance_precise < 3) {
    if ((((bd - ball_distance_precise) != 0) ||
         ((bd - ball_distance_precise) != -0.2) ||
         ((bd - ball_distance_precise) != 0.2))) {
      bd = ball_distance_precise;
    } else
      ta = millis();

    diff = millis() - ta;
    if ((diff > 4000) && (diff != millis())) {
      atk_p = true;
    }
    //}

    if (atk_p == false) {

      if (ball_sensor == 0) {
        brake();
        readIMU(); // reads the imu euler angle >imu_current_euler<
        recenter(1.0);
      }
      if ((ball_sensor >= 1) && (ball_sensor <= 6)) {
        drivePID(90, GOALIE_P);
      }
      if ((ball_sensor <= 19) && (ball_sensor >= 14)) {
        drivePID(270, GOALIE_P);
      }
      if ((ball_sensor < 14) && (ball_sensor > 6)) {
        //  menamoli();
        goalie();
      }

      if (us_px > 35) {
        drivePID(180, 150);
      }
      if (us_px < 18) {
        drivePID(0, 150);
      }
    }

    else if ((atk_p == true) && (ball_distance_precise < 0.7)) {
      // menamoli();
      goalie();
    } else if ((atk_p == true) && (ball_distance_precise >= 0.7)) {

      if (ball_sensor == 0) {
        brake();
        readIMU(); // reads the imu euler angle >imu_current_euler<
        recenter(1.0);
      }
      if ((ball_sensor >= 1) && (ball_sensor <= 6)) {
        drivePID(90, GOALIE_P);
      }
      if ((ball_sensor <= 19) && (ball_sensor >= 14)) {
        drivePID(270, GOALIE_P);
      }
      if ((ball_sensor < 14) && (ball_sensor > 6)) {
        // menamoli();
        goalie();
      }

      if (us_px > 37) {
        drivePID(180, 150);
      }
      if (us_px < 18) {
        drivePID(0, 150);
      }
    }
  }

  return;
}

void space_invaders_3() {
  st = 0;
  if (us_px > 50) {
    centerGoalPost();
  } else {
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (us_dx > 60)
        preparePID(90, 180);
      else
        preparePID(0, 0);
    } else if (ball_sensor >= 14 && ball_sensor <= 19) {
      if (us_sx > 60)
        preparePID(270, 180);
      else
        preparePID(0, 0);
    } else if (ball_sensor < 14 && ball_sensor > 6) {
      palla_dietroP();
    } else {
      preparePID(0, 0);
    }
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
}
