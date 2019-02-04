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
        preparePID(0,0);        
        if(ball_sensor >= 14 && ball_sensor <= 17){
          preparePID(270, vel);
          return;
        }

        if(ball_sensor >= 3 && ball_sensor <= 6){
          preparePID(90, vel);
          return;
        }
      }
  }


    // readUS();
    // if (us_px >= 15) centroporta();
    // if ((ball_sensor >= 1) && (ball_sensor <= 8)) preparePID(90, GOALIE_P);
    // if ((ball_sensor >= 12) && (ball_sensor <= 19)) preparePID(270, GOALIE_P);
    // if ((ball_sensor > 8) && (ball_sensor < 12)) palla_dietro();

  void centroporta() {
    int larghezza = 0;
    if (status_x == CENTRO) {
      if (status_y == CENTRO) {
        preparePID(180, 150);
      }
      else if (status_y == SUD) {
        if (us_px > 20) preparePID(180, 110);
        else if (us_px < 15) preparePID(0, 130);
        else preparePID(0,0);
      }
      else ritornacentro();
    }
    else if (status_x == 255) {
      if (us_px > 50) preparePID(180, 110);
      else if (us_px < 30) preparePID(0, 130);
      else preparePID(0,0);
    }
    else ritornacentro();
  }
