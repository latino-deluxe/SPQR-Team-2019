#include <Arduino.h>
#include "vars.h"
#include "position.h"
#include "pid.h"
#include "us.h"
#include "imu.h"
#include "space_invaders.h"
#include "myspi_old.h"
#include "motors.h"


  void space_invaders() {
    int vel = 150;

    if (us_px >= 15) centroporta();
      if(ball_seen){
        recenter(1.0);
        if(ball_sensor >= 14 && ball_sensor <= 17){
          drivePID(270, vel);
          brake();
          return;
        }

        if(ball_sensor >= 3 && ball_sensor <= 6){
          drivePID(90, vel);
          brake();
          return;
        }
      }
  }


    // readUS();
    // if (us_px >= 15) centroporta();
    // if ((ball_sensor >= 1) && (ball_sensor <= 8)) drivePID(90, GOALIE_P);
    // if ((ball_sensor >= 12) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    // if ((ball_sensor > 8) && (ball_sensor < 12)) palla_dietro();

  void centroporta() {
    int larghezza = 0;
    if (status_x == CENTRO) {
      if (status_y == CENTRO) {
        drivePID(180, 150);
      }
      else if (status_y == SUD) {
        if (us_px > 20) drivePID(180, 110);
        else if (us_px < 15) drivePID(0, 130);
        else recenter(1.0);
      }
      else ritornacentro();
    }
    else if (status_x == 255) {
      if (us_px > 50) drivePID(180, 110);
      else if (us_px < 30) drivePID(0, 130);
      else recenter(1.0);
    }
    else ritornacentro();
  }
