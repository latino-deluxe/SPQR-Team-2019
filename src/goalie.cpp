#include "goalie.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"
#include "imu.h"
#include "camera.h" 
#include "music.h"
#include <Arduino.h>

int SCY1 = 0;
int SCY2 = 0;

void goalie() {
  x = 1;
  y = 1;
  if(ball_degrees >= 345 || ball_degrees <= 15)  atk_direction = ball_degrees;

  if(ball_degrees >= 90 && ball_degrees < 145)   atk_direction = 170;
  if(ball_degrees >= 145&& ball_degrees <= 180)  atk_direction = 215;
  if(ball_degrees > 180 && ball_degrees <= 215)  atk_direction = 145;
  if(ball_degrees > 215 && ball_degrees <= 270)  atk_direction = 190;

  if(ball_distance > 180) {
    if(ball_degrees > 15  && ball_degrees < 30)    atk_direction = ball_degrees + 30;
    if(ball_degrees >= 30 && ball_degrees < 45)    atk_direction = ball_degrees + 35;
    if(ball_degrees >= 45 && ball_degrees < 90)    atk_direction = ball_degrees + 45;
    if(ball_degrees > 270 && ball_degrees <= 315)  atk_direction = ball_degrees - 45;
    if(ball_degrees > 315 && ball_degrees <= 330)  atk_direction = ball_degrees - 35;
    if(ball_degrees > 330 && ball_degrees < 345)   atk_direction = ball_degrees - 30;
  }
  else {
    if(ball_degrees > 15  && ball_degrees < 30)    atk_direction = ball_degrees + 40;
    if(ball_degrees >= 30 && ball_degrees < 45)    atk_direction = ball_degrees + 45;
    if(ball_degrees >= 45 && ball_degrees < 90)    atk_direction = ball_degrees + 55;
    if(ball_degrees > 270 && ball_degrees <= 315)  atk_direction = ball_degrees - 55;
    if(ball_degrees > 315 && ball_degrees <= 330)  atk_direction = ball_degrees - 45;
    if(ball_degrees > 330 && ball_degrees < 345)   atk_direction = ball_degrees - 40;
  }

  
  if((ball_degrees > 60 && ball_degrees < 120) || (ball_degrees > 230 && ball_degrees < 290)) atk_speed = 215;
  else atk_speed = 250;
  
  //presa più stabile
  if((ball_degrees >= 90 && ball_degrees <= 270) && ball_distance <= 180) atk_speed = 190;

  goalPosition();
  if((ball_degrees >= 330 || ball_degrees <= 30) && ball_distance > 140) preparePID(atk_direction, atk_speed, cstorc);
  else preparePID(atk_direction, atk_speed);
}

void leaveMeAlone() {
  if (zoneIndex >= 6) goCenter();
}

void storcimentoPorta() {
  if (pAtk > 20) cstorc+=7.5;
  else if (pAtk < -20) cstorc-=7.5;
  else {
    if (cstorc > 0) cstorc -= 4;
    else  cstorc += 4;
  }
  
  if (cstorc > 30) cstorc = 30;
  if (cstorc < -30) cstorc = -30;
}
