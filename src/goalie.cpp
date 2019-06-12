#include "goalie.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"
#include "imu.h"
#include "camera.h" 
#include <Arduino.h>

#define OFFDEG1 35
#define OFFDEG2DX 90
#define OFFDEG2SX 60
int SCY1 = 0;
int SCY2 = 0;



void goalie() {
  if(ball_degrees >= 345 || ball_degrees < 15) atk_direction = ball_degrees;
  if(ball_degrees >= 15 && ball_degrees < 45)  atk_direction = ball_degrees + 40;
  if(ball_degrees >= 45 && ball_degrees < 90)  atk_direction = ball_degrees + 50;
  if(ball_degrees >= 90 && ball_degrees < 145) atk_direction = 170;
  if(ball_degrees >= 145 && ball_degrees < 180)atk_direction = 215;
  if(ball_degrees >= 180 && ball_degrees < 215)atk_direction = 145;
  if(ball_degrees >= 215 && ball_degrees < 270)atk_direction = 190;
  if(ball_degrees >= 270 && ball_degrees < 315)atk_direction = ball_degrees - 30;
  if(ball_degrees >= 315 && ball_degrees < 345)atk_direction = ball_degrees - 35;

  
  atk_speed = 255;



  if(ball_degrees >= 330 || ball_degrees <= 30) {
    if(SCY1 <= STRCYCL) {
      preparePID(atk_direction, atk_speed, stincr);
      SCY1++;
      SCY2 = 0;
    }
    else {
      if(SCY2 <= 200){
        preparePID(atk_direction, atk_speed);
        SCY2++;
      }else{
        SCY1 = 0;
      }
    }
  }
  else preparePID(atk_direction, atk_speed);
}




void goalieINT() {
  int bsens;
  bsens = ((ball_degrees * 2) / 45);
  int goaliedirection[16] = {AA0,  AA1,  AA2,  AA3,  AA4,  AA5,  AA6,
                             AA7,  AA8,  AA9,  AA10, AA11, AA12, AA13,
                             AA14, AA15};


  atk_direction = goaliedirection[bsens]; // going around the ball (inseguo la palla)

  atk_speed = 250;
  preparePID(atk_direction, atk_speed);
}

void goalieOLD() {
  // directions going around the ball
  int goaliedirection[16] = {AA0,  AA1,  AA2,  AA3,  AA4,  AA5,  AA6,
                             AA7,  AA8,  AA9,  AA10, AA11, AA12, AA13,
                             AA14, AA15};


  atk_direction = goaliedirection[ball_sensor]; // going around the ball (inseguo la palla)

  atk_speed = 250;
  preparePID(atk_direction, atk_speed, stincr);
}


int stport = 0;

void storcimentoPortaIncr() {
  //if((ball_sensor == 15 || ball_sensor == 0 || ball_sensor == 1)){
    // if(ball_seen){
      if (pAtk == 999) { // non vedo porta
        //digitalWrite(Y, LOW);
        //digitalWrite(R, LOW);
        //digitalWrite(BUZZER, 0);
        return;
      }

      stport = fixCamIMU();

      // stport = pAtk;

      if (stport == 0) {
        stincr = stincr * 0.8;
        // digitalWrite(BUZZER, 1);
        return;
      }else if (stport >= goalieCamMax) {
        stincr -= 3.5; // la porta sta a destra
        if (stincr < -45)
          stincr = -45;
        digitalWrite(Y, LOW);
        digitalWrite(R, HIGH);
        digitalWrite(BUZZER, 0);
      } else if (stport <= goalieCamMin) {
        stincr += 3.5;
        if (stincr > 45)
          stincr = 45; // la porta sta a sinistra
        digitalWrite(Y, HIGH);
        digitalWrite(R, LOW);
        digitalWrite(BUZZER, 0);
      } else { // robot centrato con porta
        digitalWrite(Y, HIGH);
        digitalWrite(R, HIGH);
        digitalWrite(BUZZER, 0);
      }
    // }
    // else stincr = 0;
  }
//}


void leaveMeAlone() {
  if (zoneIndex >= 6)
    goCenter();
}

