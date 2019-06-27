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
  if(ball_degrees >= 350 || ball_degrees <= 10)  {
    atk_direction = ball_degrees;
    atk_speed = 300;
  }

  if(ball_degrees >= 90 && ball_degrees <= 270) {
    ballBack();
    atk_speed = 200;
  }

  if(ball_degrees > 10   && ball_degrees <  30)   {
    atk_direction = ball_degrees + 35;
    atk_speed = 220;
  }
  if(ball_degrees >= 30 && ball_degrees <  45)    {
    atk_direction = ball_degrees + 40;
    atk_speed = 220;
  }
  if(ball_degrees >= 45 && ball_degrees <  90)    {
    atk_direction = ball_degrees + 45;
    atk_speed = 220;
  }
  if(ball_degrees > 270 && ball_degrees <= 315)   {
    atk_direction = ball_degrees - 55;
    atk_speed = 220;
  }
  if(ball_degrees > 315 && ball_degrees <= 330)   {
    atk_direction = ball_degrees - 50;
    atk_speed = 220;
  }
  if(ball_degrees > 330 && ball_degrees <  350)   {
    atk_direction = ball_degrees - 45;
    atk_speed = 220;
  }

  if((ball_degrees >= 330 || ball_degrees <= 30) && ball_distance > 190) {
    atk_speed = 330;                                                            //dove i gigahertz hanno fallito
    preparePID(atk_direction, atk_speed, cstorc);
  }
  else preparePID(atk_direction, atk_speed);
}

void leaveMeAlone() {
  if (zoneIndex >= 6) goCenter();
}

void storcimentoPorta() {
  if (pAtk > 20) cstorc+=9.5;
  else if (pAtk < -20) cstorc-=9.5;
  else {
    if (cstorc > 0) cstorc -= 2;
    else  cstorc += 2;
  }
  
  if (cstorc > 30) cstorc = 30;
  if (cstorc < -30) cstorc = -30;
}

void ballBack() {
  int ball_degrees2;
  int dir;
  
  if(ball_degrees > 180) ball_degrees2 = ball_degrees - 360;
  else ball_degrees2 = ball_degrees;
  if(ball_degrees2 > 0) dir = ball_degrees + 50;
  else dir = ball_degrees - 50;
  if(dir < 0) dir = dir + 360;
  else dir = dir;
  atk_direction = dir;
}
