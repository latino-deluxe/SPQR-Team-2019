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
int vel = 255;

void super_duper_space_invaders(){
  if(portx == 0 || portx == 999){
    //check for the camera to work, if it doesn't use us
    defGoRight = (us_dx > 60 || us_sx < 60);
    defGoLeft = (us_sx > 60 || us_dx < 60);
  }else{
    //camera works, us it
    defGoRight = portx > keeperMin;
    defGoLeft = portx < keeperMax;
  }

  //now go space_invaders
  if (us_px > 35 && stop_menamoli) {
    centerGoalPostCamera();
  } else {
    if (ball_sensor >= 1 && ball_sensor <= 6) {
      if (defGoRight)
        preparePID(90, vel);
      else
        preparePID(0, 0);
    } else if (ball_sensor >= 14 && ball_sensor <= 19) {
      if (defGoLeft)
        preparePID(270, vel);
      else
        preparePID(0, 0);
    } else if (ball_sensor < 14 && ball_sensor > 6) {
      goalie();
      // preparePID(180, 180);
    } else {
      // menamoli approssimato :D
      //MENAMOLI DA FIXARE PER BENE
      if (ball_distance <= 3 && !stop_menamoli)
      goalie();     //menamoli();
      else
      preparePID(0, 0);
    }
  }
}

// void space_invaders_camera() {
//   if (portx == 0 || portx == 999) {
//     space_invaders_us();
//   } else {
//     if (us_px < 35) {
//       if (ball_sensor >= 1 && ball_sensor <= 6) {
//         if (portx > keeperMin)
//           preparePID(90, 180);
//         else
//           preparePID(0, 0);
//       } else if (ball_sensor >= 14 && ball_sensor <= 19) {
//         if (portx < keeperMax)
//           preparePID(270, 180);
//         else
//           preparePID(0, 0);
//       } else if (ball_sensor < 14 && ball_sensor > 6) {
//         goalie();
//       } else {
//         // menamoli approssimato :D
//         if (ball_distance <= 3)
//           goalie();
//         else
//           preparePID(0, 0);
//       }
//
//     } else {
//       preparePID(180, 120);
//     }
//   }
// }
// void space_invaders_us() {
//   if (us_px < 35) {
//     if (ball_sensor >= 1 && ball_sensor <= 6) {
//       if (us_dx > 60 || us_sx < 60)
//         preparePID(90, 180);
//       else
//         preparePID(0, 0);
//     } else if (ball_sensor >= 14 && ball_sensor <= 19) {
//       if (us_sx > 60 || us_dx < 60)
//         preparePID(270, 180);
//       else
//         preparePID(0, 0);
//     } else if (ball_sensor < 14 && ball_sensor > 6) {
//       goalie();
//       // preparePID(180, 180);
//     } else {
//       // menamoli approssimato :D
//       if (ball_distance <= 3)
//         goalie();
//       else
//         preparePID(0, 0);
//     }
//   } else {
//     preparePID(180, 120);
//   }
// }

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
  if (portx == 0 || portx == 999) {
    centerGoalPost();
  } else {
    int vel = 150;
    if (zoneIndex < 6) {
      centerGoalPost();
    } else {
      if (portx < keeperMin) {
        preparePID(90, 0);
      } else if (portx > keeperMax) {
        preparePID(270, 0);
      }
    }
  }
}


void menamoli() {
  // directions going around the ball
  int goaliedirection[20] = {AA0,  AA1,  AA2,  AA3,  AA4,  AA5,  AA6,
                             AA7,  AA8,  AA9,  AA10, AA11, AA12, AA13,
                             AA14, AA15, AA16, AA17, AA18, AA19};

  // PALLA DIETRO
  palla_dietro();

  atk_direction = goaliedirection[ball_sensor]; // going around the ball (inseguo la palla)

  if(role){
    if ((ball_sensor == 19 || ball_sensor == 0 || ball_sensor == 1) && (ball_distance <= 2)) storcimentoPortaIncr();
  }else{
    storcimentoZone();
    atk_direction = atk_direction + atk_offset;
    atk_direction = (atk_direction + 360) % 360;
  }


  atk_speed = 250;
  preparePID(atk_direction, atk_speed, stincr);
}
