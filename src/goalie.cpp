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
int storc = 0;


void goalie() {
  x = 1;
  y = 1;
  if(ball_degrees >= 345 || ball_degrees <= 15)  atk_direction = ball_degrees;
  if(ball_degrees > 15  && ball_degrees < 30)    atk_direction = ball_degrees + 20;
  if(ball_degrees >= 30 && ball_degrees < 45)    atk_direction = ball_degrees + 40;
  if(ball_degrees >= 45 && ball_degrees < 90)    atk_direction = ball_degrees + 50;
  if(ball_degrees >= 90 && ball_degrees < 145)   atk_direction = 170;
  if(ball_degrees >= 145&& ball_degrees <= 180)  atk_direction = 215;
  if(ball_degrees > 180 && ball_degrees <= 215)  atk_direction = 145;
  if(ball_degrees > 215 && ball_degrees <= 270)  atk_direction = 190;
  if(ball_degrees > 270 && ball_degrees <= 315)  atk_direction = ball_degrees - 50;
  if(ball_degrees > 315 && ball_degrees <= 330)  atk_direction = ball_degrees - 40;
  if(ball_degrees > 330 && ball_degrees < 345)   atk_direction = ball_degrees - 20;

  
  atk_speed = 255;

  goalPosition();
  if((ball_degrees >= 330 || ball_degrees <= 30) && ball_distance > 140) {
    if(pAtk > 30) {
      storc = 45;
      digitalWrite(Y, HIGH);
      digitalWrite(R, LOW);
    }
    if(pAtk < -30) {
      storc = -45;
      digitalWrite(Y, LOW);
      digitalWrite(R, HIGH);
    }
    if(pAtk > -30 || pAtk < 30) {
      storc = 0;
      digitalWrite(Y, HIGH);
      digitalWrite(R, HIGH);
    }
    // if(storc > 45) storc = 45;
    // if(storc < -45) storc = -45;
    preparePID(atk_direction, atk_speed, pAtk);
  }
  else preparePID(atk_direction, atk_speed);
}


// int stport = 0;
// void storcimentoPorta() {
//   if(pAtk == 999) return;
//   stport = fixCamIMU(pAtk);
//   if(stport >= goalieCamMax) stincr = -30;
//   if(stport <= goalieCamMin) stincr = 30;
//   else stincr = 0;
// }

// void storcimentoPortaIncr() {
//   //if((ball_sensor == 15 || ball_sensor == 0 || ball_sensor == 1)){
//     // if(ball_seen){
//       if (pAtk == 999) { // non vedo porta
//         //digitalWrite(Y, LOW);
//         //digitalWrite(R, LOW);
//         //digitalWrite(BUZZER, 0);
//         return;
//       }

//       stport = fixCamIMU(pAtk);

//       // stport = pAtk;

//       if (stport == 0) {
//         stincr = stincr * 0.8;
//         // digitalWrite(BUZZER, 1);
//         return;
//       }else if (stport >= goalieCamMax) {
//         stincr -= 5; // la porta sta a destra
//         if (stincr < -45)
//           stincr = -45;
//         digitalWrite(Y, LOW);
//         digitalWrite(R, HIGH);
//         digitalWrite(BUZZER, 0);
//       } else if (stport <= goalieCamMin) {
//         stincr += 5;
//         if (stincr > 45)
//           stincr = 45; // la porta sta a sinistra
//         digitalWrite(Y, HIGH);
//         digitalWrite(R, LOW);
//         digitalWrite(BUZZER, 0);
//       } else { // robot centrato con porta
//         digitalWrite(Y, HIGH);
//         digitalWrite(R, HIGH);
//         digitalWrite(BUZZER, 0);
//       }
//     // }
//     // else stincr = 0;
//   }
// //}


void leaveMeAlone() {
  if (zoneIndex >= 6)
    goCenter();
}

