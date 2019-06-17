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

void space_invaders() {

  if(ball_degrees <= 90){
    if(pDef < keeperCamMax){
      preparePID(90, 0); 
    }else {
      preparePID(0, 0);
    }
  }else if(ball_degrees >= 270){
    if(pDef > keeperCamMin) {
      preparePID(270, 0); 
    }else {
      preparePID(0, 0);
    }
  }else if(ball_degrees < 270 && ball_degrees > 90){
    goalie();
  }else{
    preparePID(0, 0);
  }

}


